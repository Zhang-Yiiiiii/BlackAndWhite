/****************************************************************************
** Meta object code from reading C++ file 'mainscene.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainscene.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
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
struct qt_meta_tag_ZN9MainSceneE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN9MainSceneE = QtMocHelpers::stringData(
    "MainScene",
    "sceneShow",
    "",
    "onHexagonClicked",
    "gameLevel",
    "onGameSceneChangeBack",
    "onLoginClicked",
    "onUserConfirmLogin",
    "onUserConfirmRegister",
    "onMapingInfoReceived",
    "BuildWay",
    "buildWay",
    "onSaveButtonClicked",
    "gameStep",
    "bugX",
    "bugY",
    "bugDirection",
    "onOnlineTriggerd",
    "onDisconnectTriggerd"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN9MainSceneE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   75,    2, 0x08,    2 /* Private */,
       5,    0,   78,    2, 0x08,    4 /* Private */,
       6,    0,   79,    2, 0x08,    5 /* Private */,
       7,    0,   80,    2, 0x08,    6 /* Private */,
       8,    0,   81,    2, 0x08,    7 /* Private */,
       9,    1,   82,    2, 0x08,    8 /* Private */,
      12,    5,   85,    2, 0x08,   10 /* Private */,
      17,    0,   96,    2, 0x08,   16 /* Private */,
      18,    0,   97,    2, 0x08,   17 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   11,   13,   14,   15,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainScene::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN9MainSceneE.offsetsAndSizes,
    qt_meta_data_ZN9MainSceneE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN9MainSceneE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainScene, std::true_type>,
        // method 'sceneShow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onHexagonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onGameSceneChangeBack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLoginClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onUserConfirmLogin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onUserConfirmRegister'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMapingInfoReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<BuildWay, std::false_type>,
        // method 'onSaveButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<BuildWay, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onOnlineTriggerd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDisconnectTriggerd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainScene *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sceneShow(); break;
        case 1: _t->onHexagonClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->onGameSceneChangeBack(); break;
        case 3: _t->onLoginClicked(); break;
        case 4: _t->onUserConfirmLogin(); break;
        case 5: _t->onUserConfirmRegister(); break;
        case 6: _t->onMapingInfoReceived((*reinterpret_cast< std::add_pointer_t<BuildWay>>(_a[1]))); break;
        case 7: _t->onSaveButtonClicked((*reinterpret_cast< std::add_pointer_t<BuildWay>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 8: _t->onOnlineTriggerd(); break;
        case 9: _t->onDisconnectTriggerd(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (MainScene::*)();
            if (_q_method_type _q_method = &MainScene::sceneShow; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *MainScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN9MainSceneE.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int MainScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MainScene::sceneShow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
