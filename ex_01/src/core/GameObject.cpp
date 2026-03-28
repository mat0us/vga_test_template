#include "GameObject.h"

GameObject::GameObject(ShaderProgram* shaderProgram, VertexBuffer* vertexBuffer)
    : m_shaderProgram(shaderProgram)
    , m_vertexBuffer(vertexBuffer)
{}
