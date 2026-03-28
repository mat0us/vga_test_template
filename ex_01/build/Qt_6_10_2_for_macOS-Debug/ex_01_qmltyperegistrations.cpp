/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<OpenGLScene.h>)
#  include <OpenGLScene.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_OpenGLUnderQML()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<OpenGLScene>("OpenGLUnderQML", 1);
    QT_WARNING_POP
    qmlRegisterModule("OpenGLUnderQML", 1, 0);
}

static const QQmlModuleRegistration openGLUnderQMLRegistration("OpenGLUnderQML", qml_register_types_OpenGLUnderQML);
