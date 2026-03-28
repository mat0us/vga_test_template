/****************************************************************************
** Meta object code from reading C++ file 'OpenGLScene.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/graphics/OpenGLScene.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OpenGLScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN19OpenGLSceneRendererE_t {};
} // unnamed namespace

template <> constexpr inline auto OpenGLSceneRenderer::qt_create_metaobjectdata<qt_meta_tag_ZN19OpenGLSceneRendererE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "OpenGLSceneRenderer",
        "init",
        "",
        "paint"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'init'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'paint'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<OpenGLSceneRenderer, qt_meta_tag_ZN19OpenGLSceneRendererE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject OpenGLSceneRenderer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19OpenGLSceneRendererE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19OpenGLSceneRendererE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN19OpenGLSceneRendererE_t>.metaTypes,
    nullptr
} };

void OpenGLSceneRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<OpenGLSceneRenderer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->paint(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *OpenGLSceneRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenGLSceneRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19OpenGLSceneRendererE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QObject::qt_metacast(_clname);
}

int OpenGLSceneRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN11OpenGLSceneE_t {};
} // unnamed namespace

template <> constexpr inline auto OpenGLScene::qt_create_metaobjectdata<qt_meta_tag_ZN11OpenGLSceneE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "OpenGLScene",
        "QML.Element",
        "auto",
        "obj0AnimationChanged",
        "",
        "obj0RotXChanged",
        "obj0RotZChanged",
        "objScaleChanged",
        "objMoveXChanged",
        "objMoveYChanged",
        "objMoveZChanged",
        "objLinearXChanged",
        "cameraZoomChanged",
        "cameraViewChanged",
        "sync",
        "cleanup",
        "handleWindowChanged",
        "QQuickWindow*",
        "win",
        "obj0Animation",
        "obj0RotX",
        "obj0RotZ",
        "objScale",
        "objMoveX",
        "objMoveY",
        "objMoveZ",
        "objLinearX",
        "cameraZoom",
        "cameraView"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'obj0AnimationChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'obj0RotXChanged'
        QtMocHelpers::SignalData<void()>(5, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'obj0RotZChanged'
        QtMocHelpers::SignalData<void()>(6, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'objScaleChanged'
        QtMocHelpers::SignalData<void()>(7, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'objMoveXChanged'
        QtMocHelpers::SignalData<void()>(8, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'objMoveYChanged'
        QtMocHelpers::SignalData<void()>(9, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'objMoveZChanged'
        QtMocHelpers::SignalData<void()>(10, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'objLinearXChanged'
        QtMocHelpers::SignalData<void()>(11, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cameraZoomChanged'
        QtMocHelpers::SignalData<void()>(12, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cameraViewChanged'
        QtMocHelpers::SignalData<void()>(13, 4, QMC::AccessPublic, QMetaType::Void),
        // Slot 'sync'
        QtMocHelpers::SlotData<void()>(14, 4, QMC::AccessPublic, QMetaType::Void),
        // Slot 'cleanup'
        QtMocHelpers::SlotData<void()>(15, 4, QMC::AccessPublic, QMetaType::Void),
        // Slot 'handleWindowChanged'
        QtMocHelpers::SlotData<void(QQuickWindow *)>(16, 4, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 17, 18 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'obj0Animation'
        QtMocHelpers::PropertyData<qreal>(19, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'obj0RotX'
        QtMocHelpers::PropertyData<qreal>(20, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'obj0RotZ'
        QtMocHelpers::PropertyData<qreal>(21, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'objScale'
        QtMocHelpers::PropertyData<qreal>(22, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'objMoveX'
        QtMocHelpers::PropertyData<qreal>(23, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'objMoveY'
        QtMocHelpers::PropertyData<qreal>(24, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'objMoveZ'
        QtMocHelpers::PropertyData<qreal>(25, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'objLinearX'
        QtMocHelpers::PropertyData<qreal>(26, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
        // property 'cameraZoom'
        QtMocHelpers::PropertyData<qreal>(27, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'cameraView'
        QtMocHelpers::PropertyData<int>(28, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<OpenGLScene, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject OpenGLScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11OpenGLSceneE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11OpenGLSceneE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11OpenGLSceneE_t>.metaTypes,
    nullptr
} };

void OpenGLScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<OpenGLScene *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->obj0AnimationChanged(); break;
        case 1: _t->obj0RotXChanged(); break;
        case 2: _t->obj0RotZChanged(); break;
        case 3: _t->objScaleChanged(); break;
        case 4: _t->objMoveXChanged(); break;
        case 5: _t->objMoveYChanged(); break;
        case 6: _t->objMoveZChanged(); break;
        case 7: _t->objLinearXChanged(); break;
        case 8: _t->cameraZoomChanged(); break;
        case 9: _t->cameraViewChanged(); break;
        case 10: _t->sync(); break;
        case 11: _t->cleanup(); break;
        case 12: _t->handleWindowChanged((*reinterpret_cast<std::add_pointer_t<QQuickWindow*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QQuickWindow* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (OpenGLScene::*)()>(_a, &OpenGLScene::obj0AnimationChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (OpenGLScene::*)()>(_a, &OpenGLScene::obj0RotXChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (OpenGLScene::*)()>(_a, &OpenGLScene::obj0RotZChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (OpenGLScene::*)()>(_a, &OpenGLScene::objScaleChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (OpenGLScene::*)()>(_a, &OpenGLScene::objMoveXChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (OpenGLScene::*)()>(_a, &OpenGLScene::objMoveYChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (OpenGLScene::*)()>(_a, &OpenGLScene::objMoveZChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (OpenGLScene::*)()>(_a, &OpenGLScene::objLinearXChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (OpenGLScene::*)()>(_a, &OpenGLScene::cameraZoomChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (OpenGLScene::*)()>(_a, &OpenGLScene::cameraViewChanged, 9))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<qreal*>(_v) = _t->obj0Animation(); break;
        case 1: *reinterpret_cast<qreal*>(_v) = _t->obj0RotX(); break;
        case 2: *reinterpret_cast<qreal*>(_v) = _t->obj0RotZ(); break;
        case 3: *reinterpret_cast<qreal*>(_v) = _t->objScale(); break;
        case 4: *reinterpret_cast<qreal*>(_v) = _t->objMoveX(); break;
        case 5: *reinterpret_cast<qreal*>(_v) = _t->objMoveY(); break;
        case 6: *reinterpret_cast<qreal*>(_v) = _t->objMoveZ(); break;
        case 7: *reinterpret_cast<qreal*>(_v) = _t->objLinearX(); break;
        case 8: *reinterpret_cast<qreal*>(_v) = _t->cameraZoom(); break;
        case 9: *reinterpret_cast<int*>(_v) = _t->cameraView(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setObj0Animation(*reinterpret_cast<qreal*>(_v)); break;
        case 1: _t->setObj0RotX(*reinterpret_cast<qreal*>(_v)); break;
        case 2: _t->setObj0RotZ(*reinterpret_cast<qreal*>(_v)); break;
        case 3: _t->setObjScale(*reinterpret_cast<qreal*>(_v)); break;
        case 4: _t->setObjMoveX(*reinterpret_cast<qreal*>(_v)); break;
        case 5: _t->setObjMoveY(*reinterpret_cast<qreal*>(_v)); break;
        case 6: _t->setObjMoveZ(*reinterpret_cast<qreal*>(_v)); break;
        case 7: _t->setObjLinearX(*reinterpret_cast<qreal*>(_v)); break;
        case 8: _t->setCameraZoom(*reinterpret_cast<qreal*>(_v)); break;
        case 9: _t->setCameraView(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *OpenGLScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenGLScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11OpenGLSceneE_t>.strings))
        return static_cast<void*>(this);
    return QQuickItem::qt_metacast(_clname);
}

int OpenGLScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void OpenGLScene::obj0AnimationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void OpenGLScene::obj0RotXChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void OpenGLScene::obj0RotZChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void OpenGLScene::objScaleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void OpenGLScene::objMoveXChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void OpenGLScene::objMoveYChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void OpenGLScene::objMoveZChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void OpenGLScene::objLinearXChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void OpenGLScene::cameraZoomChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void OpenGLScene::cameraViewChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
