/****************************************************************************
** Meta object code from reading C++ file 'QtDicomVtk.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../QtDicomVtk.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtDicomVtk.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtDicomVtk_t {
    const uint offsetsAndSize[18];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QtDicomVtk_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QtDicomVtk_t qt_meta_stringdata_QtDicomVtk = {
    {
QT_MOC_LITERAL(0, 10), // "QtDicomVtk"
QT_MOC_LITERAL(11, 19), // "onDrawSphereClicked"
QT_MOC_LITERAL(31, 0), // ""
QT_MOC_LITERAL(32, 22), // "onDisplaySeriesClicked"
QT_MOC_LITERAL(55, 13), // "onChangeLevel"
QT_MOC_LITERAL(69, 14), // "onChangeWindow"
QT_MOC_LITERAL(84, 17), // "onChangeZRotation"
QT_MOC_LITERAL(102, 17), // "onChangeZPosition"
QT_MOC_LITERAL(120, 23) // "onIncreaseSliceNoChange"

    },
    "QtDicomVtk\0onDrawSphereClicked\0\0"
    "onDisplaySeriesClicked\0onChangeLevel\0"
    "onChangeWindow\0onChangeZRotation\0"
    "onChangeZPosition\0onIncreaseSliceNoChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtDicomVtk[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x0a,    0 /* Public */,
       3,    0,   57,    2, 0x0a,    1 /* Public */,
       4,    0,   58,    2, 0x0a,    2 /* Public */,
       5,    0,   59,    2, 0x0a,    3 /* Public */,
       6,    0,   60,    2, 0x0a,    4 /* Public */,
       7,    0,   61,    2, 0x0a,    5 /* Public */,
       8,    0,   62,    2, 0x0a,    6 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtDicomVtk::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtDicomVtk *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onDrawSphereClicked(); break;
        case 1: _t->onDisplaySeriesClicked(); break;
        case 2: _t->onChangeLevel(); break;
        case 3: _t->onChangeWindow(); break;
        case 4: _t->onChangeZRotation(); break;
        case 5: _t->onChangeZPosition(); break;
        case 6: _t->onIncreaseSliceNoChange(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject QtDicomVtk::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_QtDicomVtk.offsetsAndSize,
    qt_meta_data_QtDicomVtk,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QtDicomVtk_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *QtDicomVtk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtDicomVtk::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtDicomVtk.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QtDicomVtk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
