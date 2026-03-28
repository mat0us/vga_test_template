QT += qml quick

CONFIG += c++17
CONFIG += qmltypes

QML_IMPORT_NAME = OpenGLUnderQML
QML_IMPORT_MAJOR_VERSION = 1

INCLUDEPATH += \
    src \
    src/core \
    src/graphics \
    src/data \
    src/objects

SOURCES += \
    src/core/AnimatedMeshObject.cpp \
    src/objects/SceneObjects.cpp \
    src/core/GameObject.cpp \
    src/core/MeshBuffer.cpp \
    src/core/MeshObject.cpp \
    src/core/VertexBuffer.cpp \
    src/graphics/OpenGLScene.cpp \
    src/graphics/ShaderProgram.cpp \
    src/main.cpp

HEADERS += \
    src/core/AnimatedMeshObject.h \
    src/objects/SceneObjects.h \
    src/core/GameObject.h \
    src/core/MeshBuffer.h \
    src/core/MeshObject.h \
    src/core/VertexBuffer.h \
    src/data/Transform.h \
    src/data/Vertex.h \
    src/graphics/OpenGLScene.h \
    src/graphics/ShaderProgram.h

RESOURCES += resources/resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
