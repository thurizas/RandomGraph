/****************************************************************************
** Meta object code from reading C++ file 'preferences.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../preferences.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'preferences.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CDlgPreferences_t {
    QByteArrayData data[9];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CDlgPreferences_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CDlgPreferences_t qt_meta_stringdata_CDlgPreferences = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CDlgPreferences"
QT_MOC_LITERAL(1, 16, 7), // "onApply"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "onAccept"
QT_MOC_LITERAL(4, 34, 8), // "onReject"
QT_MOC_LITERAL(5, 43, 9), // "OnGetFont"
QT_MOC_LITERAL(6, 53, 10), // "OnGetColor"
QT_MOC_LITERAL(7, 64, 13), // "OnGetBkgColor"
QT_MOC_LITERAL(8, 78, 18) // "OnChangeEdgeWeight"

    },
    "CDlgPreferences\0onApply\0\0onAccept\0"
    "onReject\0OnGetFont\0OnGetColor\0"
    "OnGetBkgColor\0OnChangeEdgeWeight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDlgPreferences[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    1,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void CDlgPreferences::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CDlgPreferences *_t = static_cast<CDlgPreferences *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onApply(); break;
        case 1: _t->onAccept(); break;
        case 2: _t->onReject(); break;
        case 3: _t->OnGetFont(); break;
        case 4: _t->OnGetColor(); break;
        case 5: _t->OnGetBkgColor(); break;
        case 6: _t->OnChangeEdgeWeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CDlgPreferences::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CDlgPreferences.data,
      qt_meta_data_CDlgPreferences,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CDlgPreferences::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDlgPreferences::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CDlgPreferences.stringdata0))
        return static_cast<void*>(const_cast< CDlgPreferences*>(this));
    return QDialog::qt_metacast(_clname);
}

int CDlgPreferences::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
