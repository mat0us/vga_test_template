#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickWindow>
#include <QOpenGLFunctions>
#include <vector>

#include "ShaderProgram.h"
#include "MeshBuffer.h"
#include "MeshObject.h"
#include "AnimatedMeshObject.h"

// ── Renderer (render thread) ─────────────────────────────────────────────────

class OpenGLSceneRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLSceneRenderer() = default;
    ~OpenGLSceneRenderer();

    // ── Renderer Setters (Important Extension Point) ───────────────────────
    // Add new renderer-side setters here when you introduce new channels.
    void setViewportSize(const QSize& size) { m_viewportSize = size; }
    void setWindow(QQuickWindow* window) { m_window = window; }
    void setCameraView(int v) { m_cameraView = v; }

    // Animační kanály — hodnoty sem kopíruje sync() z UI threadu
    void setObj0Animation(qreal t) { m_obj0Animation = t; } // legacy: mapped to Y rotation
    void setObj0RotX(qreal t) { m_obj0RotX = t; }
    void setObj0RotZ(qreal t) { m_obj0RotZ = t; }
    void setObjScale(qreal t) { m_objScale = t; }
    void setObjMoveX(qreal t) { m_objMoveX = t; }
    void setObjMoveY(qreal t) { m_objMoveY = t; }
    void setObjMoveZ(qreal t) { m_objMoveZ = t; }
    void setObjLinearX(qreal t) { m_objLinearX = t; }
    void setCameraZoom(qreal t) { m_cameraZoom = t; }

public slots:
    void init();
    void paint();

private:
    QSize m_viewportSize;
    QQuickWindow* m_window = nullptr;
    ShaderProgram* m_shader = nullptr;
    int m_cameraView = 0;

    // Animační kanály — na tyto proměnné se bindují AnimatedMeshObjecty v init()
    qreal m_obj0Animation = 0;
    qreal m_obj0RotX = 0;
    qreal m_obj0RotZ = 0;
    qreal m_objScale = 0;
    qreal m_objMoveX = 0;
    qreal m_objMoveY = 0;
    qreal m_objMoveZ = 0;
    qreal m_objLinearX = 0;
    qreal m_cameraZoom = 1.0;

    std::vector<GameObject*> m_objects;     // vlastní objekty
    std::vector<VertexBuffer*> m_buffers;   // vlastní buffery (sdílené mezi objekty)

    void clear();
    QMatrix4x4 buildProjection() const;
    QMatrix4x4 buildView() const;
};

// ── QQuickItem (UI thread) ───────────────────────────────────────────────────

class OpenGLScene : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT

    // 4 místa pro každou animaci: Q_PROPERTY, getter, setter, signal
    Q_PROPERTY(qreal obj0Animation READ obj0Animation WRITE setObj0Animation NOTIFY obj0AnimationChanged)
    Q_PROPERTY(qreal obj0RotX      READ obj0RotX      WRITE setObj0RotX      NOTIFY obj0RotXChanged)
    Q_PROPERTY(qreal obj0RotZ      READ obj0RotZ      WRITE setObj0RotZ      NOTIFY obj0RotZChanged)
    Q_PROPERTY(qreal objScale      READ objScale      WRITE setObjScale      NOTIFY objScaleChanged)
    Q_PROPERTY(qreal objMoveX      READ objMoveX      WRITE setObjMoveX      NOTIFY objMoveXChanged)
    Q_PROPERTY(qreal objMoveY      READ objMoveY      WRITE setObjMoveY      NOTIFY objMoveYChanged)
    Q_PROPERTY(qreal objMoveZ      READ objMoveZ      WRITE setObjMoveZ      NOTIFY objMoveZChanged)
    Q_PROPERTY(qreal objLinearX    READ objLinearX    WRITE setObjLinearX    NOTIFY objLinearXChanged)
    Q_PROPERTY(qreal cameraZoom    READ cameraZoom    WRITE setCameraZoom    NOTIFY cameraZoomChanged)
    Q_PROPERTY(int   cameraView    READ cameraView    WRITE setCameraView    NOTIFY cameraViewChanged)

public:
    OpenGLScene();

    // ── QQuickItem Getters (Important Extension Point) ─────────────────────
    // Add getter for every new Q_PROPERTY you expose to QML.
    qreal obj0Animation() const { return m_obj0Animation; }
    qreal obj0RotX() const { return m_obj0RotX; }
    qreal obj0RotZ() const { return m_obj0RotZ; }
    qreal objScale() const { return m_objScale; }
    qreal objMoveX() const { return m_objMoveX; }
    qreal objMoveY() const { return m_objMoveY; }
    qreal objMoveZ() const { return m_objMoveZ; }
    qreal objLinearX() const { return m_objLinearX; }
    qreal cameraZoom() const { return m_cameraZoom; }
    int   cameraView() const { return m_cameraView; }

    // ── QQuickItem Setters (Important Extension Point) ─────────────────────
    // Add setter for every new Q_PROPERTY and emit the matching change signal.
    void setObj0Animation(qreal t);
    void setObj0RotX(qreal t);
    void setObj0RotZ(qreal t);
    void setObjScale(qreal t);
    void setObjMoveX(qreal t);
    void setObjMoveY(qreal t);
    void setObjMoveZ(qreal t);
    void setObjLinearX(qreal t);
    void setCameraZoom(qreal t);
    void setCameraView(int v);

signals:
    void obj0AnimationChanged();
    void obj0RotXChanged();
    void obj0RotZChanged();
    void objScaleChanged();
    void objMoveXChanged();
    void objMoveYChanged();
    void objMoveZChanged();
    void objLinearXChanged();
    void cameraZoomChanged();
    void cameraViewChanged();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow* win);

private:
    void releaseResources() override;

    qreal m_obj0Animation = 0;
    qreal m_obj0RotX = 0;
    qreal m_obj0RotZ = 0;
    qreal m_objScale = 0;
    qreal m_objMoveX = 0;
    qreal m_objMoveY = 0;
    qreal m_objMoveZ = 0;
    qreal m_objLinearX = 0;
    qreal m_cameraZoom = 1.0;
    int m_cameraView = 0;

    OpenGLSceneRenderer* m_renderer = nullptr;
};

#endif // OPENGLSCENE_H
