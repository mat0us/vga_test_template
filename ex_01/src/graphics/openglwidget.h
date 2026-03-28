#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <vector>

#include "gameobject.h"
#include "shaderprogram.h"
#include "meshbuffer.h"
#include "meshobject.h"
#include "vertex.h"
#include "Position.h"
#include "Rotation.h"

// OpenGL renderer nad QWidget (legacy alternativa k QML rendereru).
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();

protected:
    // Vytvori OpenGL zdroje.
    void initializeGL() override;

    // Vykresli jeden snimek.
    void paintGL() override;

    // Reakce na zmenu velikosti okna.
    void resizeGL(int width, int height) override;

private:
    ShaderProgram*           m_shaderProgram;
    std::vector<GameObject*> m_objects;

    // Pomocna funkce pro geometrii.
    std::vector<Vertex> buildPyramidVertices();
};

#endif // OPENGLWIDGET_H
