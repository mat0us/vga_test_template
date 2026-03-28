#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QMatrix4x4>
#include <QVector3D>

struct Transform {
    QVector3D position = {0.0f, 0.0f, 0.0f};
    QVector3D rotation = {0.0f, 0.0f, 0.0f}; // degrees: x, y, z
    QVector3D scale = {1.0f, 1.0f, 1.0f};

    QMatrix4x4 toMatrix() const {
        QMatrix4x4 m;
        m.translate(position);
        m.rotate(rotation.x(), 1.0f, 0.0f, 0.0f);
        m.rotate(rotation.y(), 0.0f, 1.0f, 0.0f);
        m.rotate(rotation.z(), 0.0f, 0.0f, 1.0f);
        m.scale(scale);
        return m;
    }
};

#endif // TRANSFORM_H
