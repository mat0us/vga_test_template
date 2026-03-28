#include "MeshBuffer.h"

MeshBuffer::MeshBuffer(const std::vector<Vertex>& vertices) : m_vertices(vertices) {
    init();
}

void MeshBuffer::init() {
    m_buffer.create();

    m_buffer.setUsagePattern(QOpenGLBuffer::StreamDraw);

    m_buffer.bind();

    m_buffer.allocate(m_vertices.data(), static_cast<int>(m_vertices.size() * sizeof(Vertex)));
}

int MeshBuffer::vertexCount() const {
    return static_cast<int>(m_vertices.size());
}
