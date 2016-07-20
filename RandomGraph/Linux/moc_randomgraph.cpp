/****************************************************************************
** Meta object code from reading C++ file 'randomgraph.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../randomgraph.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'randomgraph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RandomGraph_t {
    QByteArrayData data[18];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RandomGraph_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RandomGraph_t qt_meta_stringdata_RandomGraph = {
    {
QT_MOC_LITERAL(0, 0, 11), // "RandomGraph"
QT_MOC_LITERAL(1, 12, 9), // "onFileNew"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "onFileOpen"
QT_MOC_LITERAL(4, 34, 10), // "onFileSave"
QT_MOC_LITERAL(5, 45, 12), // "onFileImport"
QT_MOC_LITERAL(6, 58, 10), // "onFileExit"
QT_MOC_LITERAL(7, 69, 13), // "onViewSummary"
QT_MOC_LITERAL(8, 83, 13), // "onViewDMatrix"
QT_MOC_LITERAL(9, 97, 13), // "onViewAMatrix"
QT_MOC_LITERAL(10, 111, 13), // "onViewConsole"
QT_MOC_LITERAL(11, 125, 15), // "onViewStatusBar"
QT_MOC_LITERAL(12, 141, 13), // "onViewToolbar"
QT_MOC_LITERAL(13, 155, 12), // "onViewLabels"
QT_MOC_LITERAL(14, 168, 13), // "onViewOptions"
QT_MOC_LITERAL(15, 182, 11), // "onHelpAbout"
QT_MOC_LITERAL(16, 194, 10), // "onHelpHelp"
QT_MOC_LITERAL(17, 205, 10) // "onGenGraph"

    },
    "RandomGraph\0onFileNew\0\0onFileOpen\0"
    "onFileSave\0onFileImport\0onFileExit\0"
    "onViewSummary\0onViewDMatrix\0onViewAMatrix\0"
    "onViewConsole\0onViewStatusBar\0"
    "onViewToolbar\0onViewLabels\0onViewOptions\0"
    "onHelpAbout\0onHelpHelp\0onGenGraph"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RandomGraph[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    1,  102,    2, 0x08 /* Private */,
      11,    0,  105,    2, 0x08 /* Private */,
      12,    0,  106,    2, 0x08 /* Private */,
      13,    0,  107,    2, 0x08 /* Private */,
      14,    0,  108,    2, 0x08 /* Private */,
      15,    0,  109,    2, 0x08 /* Private */,
      16,    0,  110,    2, 0x08 /* Private */,
      17,    0,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RandomGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RandomGraph *_t = static_cast<RandomGraph *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onFileNew(); break;
        case 1: _t->onFileOpen(); break;
        case 2: _t->onFileSave(); break;
        case 3: _t->onFileImport(); break;
        case 4: _t->onFileExit(); break;
        case 5: _t->onViewSummary(); break;
        case 6: _t->onViewDMatrix(); break;
        case 7: _t->onViewAMatrix(); break;
        case 8: _t->onViewConsole((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->onViewStatusBar(); break;
        case 10: _t->onViewToolbar(); break;
        case 11: _t->onViewLabels(); break;
        case 12: _t->onViewOptions(); break;
        case 13: _t->onHelpAbout(); break;
        case 14: _t->onHelpHelp(); break;
        case 15: _t->onGenGraph(); break;
        default: ;
        }
    }
}

const QMetaObject RandomGraph::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RandomGraph.data,
      qt_meta_data_RandomGraph,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RandomGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RandomGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RandomGraph.stringdata0))
        return static_cast<void*>(const_cast< RandomGraph*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RandomGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
