#include "MeshObject.h"
#include "Vertex.h"
#include <QOpenGLContext>

MeshObject::MeshObject(ShaderProgram* shaderProgram, VertexBuffer* vertexBuffer)
    : GameObject(shaderProgram, vertexBuffer)
{}

void MeshObject::draw(const QMatrix4x4& viewProj)
{
    QOpenGLShaderProgram* program = m_shaderProgram->getProgram();
    GLuint posAttr = m_shaderProgram->getPositionAttribute();
    GLuint colAttr = m_shaderProgram->getColorAttribute();
    GLuint matUnif = m_shaderProgram->getMatrixUniform();

    program->bind();

    // MVP = projection * view * model  — model pochází z transform objektu
    program->setUniformValue(matUnif, viewProj * transform.toMatrix());

    program->enableAttributeArray(posAttr);
    program->enableAttributeArray(colAttr);

    m_vertexBuffer->bind();

    // ── Vertex Attribute Layout (Important Extension Point) ────────────────
    // Update offsets/component counts here when Vertex struct changes.
    program->setAttributeBuffer(posAttr, GL_FLOAT, 0, 3, sizeof(Vertex));
    program->setAttributeBuffer(colAttr, GL_FLOAT, sizeof(Vertex::position), 3, sizeof(Vertex));

    // ── Draw Call (Important Extension Point) ───────────────────────────────
    // Primitive type comes from GameObject::setDrawMode().
    QOpenGLContext::currentContext()->functions()->glDrawArrays(
        m_drawMode, 0, m_vertexBuffer->vertexCount());

    program->disableAttributeArray(posAttr);
    program->disableAttributeArray(colAttr);
    program->release();
}
