#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <QOpenGLBuffer>

class VertexBuffer
{
protected:
    QOpenGLBuffer m_buffer;

public:
    VertexBuffer();

    void bind();
    virtual void init() = 0;

    virtual int vertexCount() const = 0;
};

#endif // VERTEXBUFFER_H
