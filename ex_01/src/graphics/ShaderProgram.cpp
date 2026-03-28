#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const QString& vertexShaderPath, const QString& fragmentShaderPath)
    : m_program(nullptr)
{
    init(vertexShaderPath, fragmentShaderPath);
}

ShaderProgram::~ShaderProgram()
{
    delete m_program;
}

void ShaderProgram::init(const QString& vertexShaderPath, const QString& fragmentShaderPath)
{
    m_program = new QOpenGLShaderProgram();

    // Kompilace vertex a fragment shaderu.
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderPath);
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderPath);

    // Link do jednoho GPU programu.
    m_program->link();

    // Cachovani lokaci pouzivanych pri draw.
    m_positionAttribute = m_program->attributeLocation("posAttr");
    m_colorAttribute = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
}

GLuint ShaderProgram::getPositionAttribute() const { return m_positionAttribute; }
GLuint ShaderProgram::getColorAttribute() const { return m_colorAttribute; }
GLuint ShaderProgram::getMatrixUniform() const { return m_matrixUniform; }
QOpenGLShaderProgram* ShaderProgram::getProgram() const { return m_program; }
