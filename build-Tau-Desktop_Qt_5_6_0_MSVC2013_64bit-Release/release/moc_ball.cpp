/****************************************************************************
** Meta object code from reading C++ file 'ball.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Tau/ball.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ball.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Ball_t {
    QByteArrayData data[6];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ball_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ball_t qt_meta_stringdata_Ball = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Ball"
QT_MOC_LITERAL(1, 5, 9), // "updatePos"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 6), // "sizeUp"
QT_MOC_LITERAL(4, 23, 8), // "sizeDown"
QT_MOC_LITERAL(5, 32, 18) // "setBouncingToFalse"

    },
    "Ball\0updatePos\0\0sizeUp\0sizeDown\0"
    "setBouncingToFalse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ball[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Ball::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Ball *_t = static_cast<Ball *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updatePos(); break;
        case 1: _t->sizeUp(); break;
        case 2: _t->sizeDown(); break;
        case 3: _t->setBouncingToFalse(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Ball::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Ball.data,
      qt_meta_data_Ball,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Ball::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ball::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Ball.stringdata0))
        return static_cast<void*>(const_cast< Ball*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Ball*>(this));
    if (!strcmp(_clname, "org.qt-project.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Ball*>(this));
    return QObject::qt_metacast(_clname);
}

int Ball::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
