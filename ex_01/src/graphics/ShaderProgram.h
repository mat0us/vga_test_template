#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLShaderProgram>
#include <QString>

class ShaderProgram
{
    QOpenGLShaderProgram* m_program;

    GLuint m_positionAttribute;
    GLuint m_colorAttribute;
    GLuint m_matrixUniform;

public:
    ShaderProgram(const QString& vertexShaderPath, const QString& fragmentShaderPath);
    ~ShaderProgram();

    void init(const QString& vertexShaderPath, const QString& fragmentShaderPath);

    GLuint getPositionAttribute() const;
    GLuint getColorAttribute() const;
    GLuint getMatrixUniform() const;
    QOpenGLShaderProgram* getProgram() const;
};

#endif // SHADERPROGRAM_H
