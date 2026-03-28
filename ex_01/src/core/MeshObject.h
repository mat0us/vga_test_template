#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include "GameObject.h"

class MeshObject : public GameObject
{
public:
    MeshObject(ShaderProgram* shaderProgram, VertexBuffer* vertexBuffer);

    void draw(const QMatrix4x4& viewProj) override;
};

#endif // MESHOBJECT_H
