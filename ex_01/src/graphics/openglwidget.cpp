#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , m_shaderProgram(nullptr)
{
}

OpenGLWidget::~OpenGLWidget()
{
    // OpenGL zdroje je nutne uvolnovat s aktivnim kontextem.
    makeCurrent();
    delete m_shaderProgram;
    for (GameObject* obj : m_objects)
        delete obj;
    doneCurrent();
}

void OpenGLWidget::initializeGL()
{
    // Zpristupni OpenGL helper funkce v teto tride.
    initializeOpenGLFunctions();

    // Nastaveni clear barvy.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Vytvoreni shader programu.
    m_shaderProgram = new ShaderProgram(":/shader.vert", ":/shader.frag");

    // Priprava geometrie.
    std::vector<Vertex> pyramidVertices = buildPyramidVertices();

    // Nahrani geometrie na GPU.
    MeshBuffer* pyramidBuffer = new MeshBuffer(pyramidVertices);

    // Dva objekty sdili mesh/shader a lisi se transformaci.
    m_objects.push_back(new MeshObject(m_shaderProgram, pyramidBuffer,
                                       Position{0.0f,  0.0f, -1.0f},
                                       Rotation{0.0f, {0.0f, 1.0f, 0.0f}}));
    m_objects.push_back(new MeshObject(m_shaderProgram, pyramidBuffer,
                                       Position{2.0f,  0.0f,  0.0f},
                                       Rotation{0.0f, {0.0f, 1.0f, 0.0f}}));
}

void OpenGLWidget::paintGL()
{
    // Kresleni do celeho okna.
    glViewport(0, 0, width(), height());

    // Spravne 3D prekryvani.
    glEnable(GL_DEPTH_TEST);

    // Alpha blending.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Vymaze predchozi snimek.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Projekcni matice.
    QMatrix4x4 projectionMatrix;
    projectionMatrix.setToIdentity();
    float aspect = (height() > 0) ? static_cast<float>(width()) / height() : 1.0f;
    projectionMatrix.perspective(60.0f, aspect, 0.1f, 100.0f);

    // View matice.
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.lookAt(
        QVector3D(2.0f, 4.0f, -5.0f),
        QVector3D(0.0f, 0.0f,  0.0f),
        QVector3D(0.0f, 1.0f,  0.0f)
    );

    // Obnovi view matici pro kazdy objekt.
    QMatrix4x4 originalViewMatrix = viewMatrix;

    for (GameObject* object : m_objects) {
        Position pos = object->getPosition();
        Rotation rot = object->getRotation();

        // Aplikuje transformaci objektu.
        viewMatrix.translate(pos.dx, pos.dy, pos.dz);
        viewMatrix.rotate(rot.angle, rot.axis[0], rot.axis[1], rot.axis[2]);

        // Vykresli pomoci MVP matice.
        object->draw(projectionMatrix * viewMatrix);

        // Obnovi matici pro dalsi objekt.
        viewMatrix = originalViewMatrix;
    }
}

void OpenGLWidget::resizeGL(int width, int height)
{
    // Neni potreba dalsi resize logika.
    Q_UNUSED(width);
    Q_UNUSED(height);
}

std::vector<Vertex> OpenGLWidget::buildPyramidVertices()
{
    // Ctyri trojuhelnikove steny jehlanu.
    return {
        // Predni stena
        Vertex{ {-1.0f, 0.0f, -1.0f}, {0.5f, 1.0f, 0.5f} },
        Vertex{ { 0.0f, 2.0f,  0.0f}, {0.5f, 1.0f, 0.5f} },
        Vertex{ { 1.0f, 0.0f, -1.0f}, {0.5f, 1.0f, 0.5f} },

        // Prava stena
        Vertex{ { 1.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 0.5f} },
        Vertex{ { 0.0f, 2.0f,  0.0f}, {1.0f, 1.0f, 0.5f} },
        Vertex{ { 1.0f, 0.0f,  1.0f}, {1.0f, 1.0f, 0.5f} },

        // Zadni stena
        Vertex{ { 1.0f, 0.0f,  1.0f}, {0.5f, 1.0f, 0.5f} },
        Vertex{ { 0.0f, 2.0f,  0.0f}, {0.5f, 1.0f, 0.5f} },
        Vertex{ {-1.0f, 0.0f,  1.0f}, {0.5f, 1.0f, 0.5f} },

        // Leva stena
        Vertex{ {-1.0f, 0.0f,  1.0f}, {1.0f, 1.0f, 0.5f} },
        Vertex{ { 0.0f, 2.0f,  0.0f}, {1.0f, 1.0f, 0.5f} },
        Vertex{ {-1.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 0.5f} },
    };
}
