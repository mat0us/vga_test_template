#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlEngine>
#include "OpenGLScene.h"

int main(int argc, char* argv[])
{
    // QGuiApplication staci, protoze aplikace bezi nad Qt Quick/QML.
    QGuiApplication app(argc, argv);

    // Vynutime OpenGL backend, aby slo kreslit vlastnim OpenGL kodem pod QML.
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    // Nacte root QML soubor z resource systemu.
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    // Handle Qt.quit() emitted from QML by terminating the app cleanly.
    QObject::connect(view.engine(), &QQmlEngine::quit, &app, &QCoreApplication::quit);

    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return app.exec();
}
