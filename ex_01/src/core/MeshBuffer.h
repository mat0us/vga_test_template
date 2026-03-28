#ifndef MESHBUFFER_H
#define MESHBUFFER_H

#include <vector>
#include "VertexBuffer.h"
#include "Vertex.h"

class MeshBuffer : public VertexBuffer
{
    std::vector<Vertex> m_vertices;

public:
    explicit MeshBuffer(const std::vector<Vertex>& vertices);
    void init() override;
    int vertexCount() const override;
};

#endif // MESHBUFFER_H
