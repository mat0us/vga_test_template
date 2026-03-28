#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QMatrix4x4>
#include <QOpenGLFunctions>

#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "Transform.h"

class GameObject
{
protected:
    ShaderProgram* m_shaderProgram;
    VertexBuffer*  m_vertexBuffer;
    GLenum         m_drawMode = GL_TRIANGLES;

public:
    Transform transform;

    GameObject(ShaderProgram* shaderProgram, VertexBuffer* vertexBuffer);
    virtual ~GameObject() = default;

    // ── Draw Mode Control (Important Extension Point) ───────────────────────
    // Use this to switch per-object primitive mode (triangles/lines/strip...).
    void setDrawMode(GLenum drawMode) { m_drawMode = drawMode; }
    GLenum drawMode() const { return m_drawMode; }

    // ── Render/Animation Hooks (Important Extension Point) ─────────────────
    // Override these methods in derived objects when adding custom behavior.
    virtual void syncAnimations() {}
    virtual void draw(const QMatrix4x4& viewProj) = 0;
};

#endif // GAMEOBJECT_H
