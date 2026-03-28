#include "OpenGLScene.h"
#include "SceneObjects.h"
#include <QRunnable>
#include <algorithm>

// ── OpenGLScene (UI thread) ──────────────────────────────────────────────────

OpenGLScene::OpenGLScene() : m_renderer(nullptr)
{
    connect(this, &QQuickItem::windowChanged, this, &OpenGLScene::handleWindowChanged);
}

void OpenGLScene::handleWindowChanged(QQuickWindow* win)
{
    if (!win)
        return;
    connect(win, &QQuickWindow::beforeSynchronizing, this, &OpenGLScene::sync, Qt::DirectConnection);
    connect(win, &QQuickWindow::sceneGraphInvalidated, this, &OpenGLScene::cleanup, Qt::DirectConnection);
    win->setColor(Qt::black);
}

void OpenGLScene::cleanup()
{
    delete m_renderer;
    m_renderer = nullptr;
}

void OpenGLScene::sync()
{
    if (!m_renderer) {
        m_renderer = new OpenGLSceneRenderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &OpenGLSceneRenderer::init, Qt::DirectConnection);
        connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &OpenGLSceneRenderer::paint, Qt::DirectConnection);
    }

    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setWindow(window());
    m_renderer->setCameraView(m_cameraView);

    // ── Animation Channels: UI -> Render ───────────────────────────────────
    // Add new channel setters here when you introduce new animated properties.
    m_renderer->setObj0Animation(m_obj0Animation);
    m_renderer->setObj0RotX(m_obj0RotX);
    m_renderer->setObj0RotZ(m_obj0RotZ);
    m_renderer->setObjScale(m_objScale);
    m_renderer->setObjMoveX(m_objMoveX);
    m_renderer->setObjMoveY(m_objMoveY);
    m_renderer->setObjMoveZ(m_objMoveZ);
    m_renderer->setObjLinearX(m_objLinearX);
    m_renderer->setCameraZoom(m_cameraZoom);
}

// ── QQuickItem Property Setters ────────────────────────────────────────────
// Each setter emits a signal and requests redraw.
void OpenGLScene::setObj0Animation(qreal t)
{
    if (m_obj0Animation == t) return;
    m_obj0Animation = t;
    emit obj0AnimationChanged();
    if (window()) window()->update();
}

void OpenGLScene::setObjMoveX(qreal t)
{
    if (m_objMoveX == t) return;
    m_objMoveX = t;
    emit objMoveXChanged();
    if (window()) window()->update();
}

void OpenGLScene::setObj0RotX(qreal t)
{
    if (m_obj0RotX == t) return;
    m_obj0RotX = t;
    emit obj0RotXChanged();
    if (window()) window()->update();
}

void OpenGLScene::setObj0RotZ(qreal t)
{
    if (m_obj0RotZ == t) return;
    m_obj0RotZ = t;
    emit obj0RotZChanged();
    if (window()) window()->update();
}

void OpenGLScene::setObjScale(qreal t)
{
    if (m_objScale == t) return;
    m_objScale = t;
    emit objScaleChanged();
    if (window()) window()->update();
}

void OpenGLScene::setObjMoveY(qreal t)
{
    if (m_objMoveY == t) return;
    m_objMoveY = t;
    emit objMoveYChanged();
    if (window()) window()->update();
}

void OpenGLScene::setObjMoveZ(qreal t)
{
    if (m_objMoveZ == t) return;
    m_objMoveZ = t;
    emit objMoveZChanged();
    if (window()) window()->update();
}

void OpenGLScene::setObjLinearX(qreal t)
{
    if (m_objLinearX == t) return;
    m_objLinearX = t;
    emit objLinearXChanged();
    if (window()) window()->update();
}

void OpenGLScene::setCameraZoom(qreal t)
{
    const qreal clamped = std::max<qreal>(0.4, std::min<qreal>(3.0, t));
    if (m_cameraZoom == clamped) return;
    m_cameraZoom = clamped;
    emit cameraZoomChanged();
    if (window()) window()->update();
}

void OpenGLScene::setCameraView(int v)
{
    if (m_cameraView == v) return;
    m_cameraView = v;
    emit cameraViewChanged();
    if (window()) window()->update();
}

class CleanupJob : public QRunnable
{
public:
    explicit CleanupJob(OpenGLSceneRenderer* r) : m_renderer(r) {}
    void run() override { delete m_renderer; }
private:
    OpenGLSceneRenderer* m_renderer;
};

void OpenGLScene::releaseResources()
{
    window()->scheduleRenderJob(
        new CleanupJob(m_renderer), QQuickWindow::BeforeSynchronizingStage);
    m_renderer = nullptr;
}

// ── OpenGLSceneRenderer (render thread) ─────────────────────────────────────

OpenGLSceneRenderer::~OpenGLSceneRenderer()
{
    delete m_shader;
    for (GameObject*   obj : m_objects) delete obj;
    for (VertexBuffer* buf : m_buffers) delete buf;
}

void OpenGLSceneRenderer::init()
{
    if (m_shader)
        return;

    QSGRendererInterface* rif = m_window->rendererInterface();
    Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL);

    initializeOpenGLFunctions();

    m_shader = new ShaderProgram(":/shader.vert", ":/shader.frag");

    // ── Geometry Sources / Shared Buffers ──────────────────────────────────
    // Add new mesh buffers here. One buffer can be shared by many objects.
    MeshBuffer* sphereBuffer = new MeshBuffer(buildSphereVertices());
    m_buffers.push_back(sphereBuffer);

    MeshBuffer* cubeBuffer = new MeshBuffer(buildCubeVertices());
    m_buffers.push_back(cubeBuffer);

    MeshBuffer* moverBuffer = new MeshBuffer(buildMoverVertices());
    m_buffers.push_back(moverBuffer);

    // ── Scene Objects (Add Instances Here) ─────────────────────────────────

    // Object A: movement in X/Y/Z.
    auto* moveXYZ = new AnimatedMeshObject(m_shader, moverBuffer);
    moveXYZ->transform.position = {-4.5f, 0.0f, -2.0f};
    moveXYZ->bindTranslationX(&m_objMoveX, -4.5f);
    moveXYZ->bindTranslationY(&m_objMoveY, 0.0f);
    moveXYZ->bindTranslationZ(&m_objMoveZ, -2.0f);
    moveXYZ->setDrawMode(GL_TRIANGLES);
    m_objects.push_back(moveXYZ);

    // Object B: chained rotations X -> Y -> Z.
    auto* chainedRotation = new AnimatedMeshObject(m_shader, cubeBuffer);
    chainedRotation->transform.position = {-1.5f, 0.0f, -2.0f};
    chainedRotation->bindRotationX(&m_obj0RotX);
    chainedRotation->bindRotationY(&m_obj0Animation);
    chainedRotation->bindRotationZ(&m_obj0RotZ);
    chainedRotation->setDrawMode(GL_TRIANGLES);
    m_objects.push_back(chainedRotation);

    // Object C: scale in/out.
    auto* pulseScale = new AnimatedMeshObject(m_shader, sphereBuffer);
    pulseScale->transform.position = {1.5f, 0.0f, -2.0f};
    pulseScale->bindScaleUniform(&m_objScale, 1.0f);
    pulseScale->setDrawMode(GL_TRIANGLES);
    m_objects.push_back(pulseScale);

    // Object D: linear movement.
    auto* linearMove = new AnimatedMeshObject(m_shader, cubeBuffer);
    linearMove->transform.position = {4.5f, 0.0f, -2.0f};
    linearMove->bindTranslationX(&m_objLinearX, 4.5f);
    linearMove->setDrawMode(GL_TRIANGLES);
    m_objects.push_back(linearMove);

    // ── End Scene Objects ───────────────────────────────────────────────────
}

void OpenGLSceneRenderer::clear()
{
    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
}

QMatrix4x4 OpenGLSceneRenderer::buildProjection() const
{
    float aspect = m_viewportSize.width() / (float)m_viewportSize.height();
    QMatrix4x4 m;
    m.perspective(60.0f, aspect, 0.1f, 100.0f);
    return m;
}

QMatrix4x4 OpenGLSceneRenderer::buildView() const
{
    // ── Camera Presets ──────────────────────────────────────────────────────
    // Add new view presets by extending this branch with a new cameraView id.
    QVector3D eye    = {2.0f, 4.0f, -5.0f};
    QVector3D center = {0.0f, 0.0f,  0.0f};
    QVector3D up     = {0.0f, 1.0f,  0.0f};

    if(m_cameraView == 1) { eye = {0.0f, 1.5f, 6.0f}; }
    else if (m_cameraView == 2) { eye = {6.0f, 1.5f, 0.0f}; }
    else if (m_cameraView == 3) { eye = {0.0f, 8.0f, 0.01f}; up = {0.0f, 0.0f, -1.0f}; }

    const QVector3D viewDir = eye - center;
    eye = center + viewDir * (float)m_cameraZoom;

    QMatrix4x4 m;
    m.lookAt(eye, center, up);
    return m;
}

void OpenGLSceneRenderer::paint()
{
    m_window->beginExternalCommands();
    clear();

    QMatrix4x4 VP = buildProjection() * buildView();

    for (GameObject* obj : m_objects) {
        obj->syncAnimations();  // animated: čte z bindnutých ukazatelů; static: nic
        obj->draw(VP);          // MVP = VP * transform.toMatrix()
    }

    m_window->endExternalCommands();
}

