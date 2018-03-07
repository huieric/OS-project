/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../OS-design/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "readCPU"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "readSum"
QT_MOC_LITERAL(4, 28, 8), // "readTime"
QT_MOC_LITERAL(5, 37, 11), // "showProcess"
QT_MOC_LITERAL(6, 49, 5), // "p_num"
QT_MOC_LITERAL(7, 55, 7), // "showCPU"
QT_MOC_LITERAL(8, 63, 8), // "showMenu"
QT_MOC_LITERAL(9, 72, 3), // "pos"
QT_MOC_LITERAL(10, 76, 13), // "showTableMenu"
QT_MOC_LITERAL(11, 90, 6), // "newDir"
QT_MOC_LITERAL(12, 97, 7), // "newFile"
QT_MOC_LITERAL(13, 105, 12), // "newDir_table"
QT_MOC_LITERAL(14, 118, 13), // "newFile_table"
QT_MOC_LITERAL(15, 132, 23), // "tableDoubleClickedSlots"
QT_MOC_LITERAL(16, 156, 5), // "index"
QT_MOC_LITERAL(17, 162, 10), // "deleteFile"
QT_MOC_LITERAL(18, 173, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(19, 195, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(20, 217, 23), // "on_lineEdit_textChanged"
QT_MOC_LITERAL(21, 241, 4) // "arg1"

    },
    "MainWindow\0readCPU\0\0readSum\0readTime\0"
    "showProcess\0p_num\0showCPU\0showMenu\0"
    "pos\0showTableMenu\0newDir\0newFile\0"
    "newDir_table\0newFile_table\0"
    "tableDoubleClickedSlots\0index\0deleteFile\0"
    "on_buttonBox_accepted\0on_buttonBox_rejected\0"
    "on_lineEdit_textChanged\0arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

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
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    1,   97,    2, 0x0a /* Public */,
       7,    0,  100,    2, 0x0a /* Public */,
       8,    1,  101,    2, 0x0a /* Public */,
      10,    1,  104,    2, 0x0a /* Public */,
      11,    0,  107,    2, 0x0a /* Public */,
      12,    0,  108,    2, 0x0a /* Public */,
      13,    0,  109,    2, 0x0a /* Public */,
      14,    0,  110,    2, 0x0a /* Public */,
      15,    1,  111,    2, 0x0a /* Public */,
      17,    0,  114,    2, 0x0a /* Public */,
      18,    0,  115,    2, 0x08 /* Private */,
      19,    0,  116,    2, 0x08 /* Private */,
      20,    1,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readCPU(); break;
        case 1: _t->readSum(); break;
        case 2: _t->readTime(); break;
        case 3: _t->showProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->showCPU(); break;
        case 5: _t->showMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: _t->showTableMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 7: _t->newDir(); break;
        case 8: _t->newFile(); break;
        case 9: _t->newDir_table(); break;
        case 10: _t->newFile_table(); break;
        case 11: _t->tableDoubleClickedSlots((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 12: _t->deleteFile(); break;
        case 13: _t->on_buttonBox_accepted(); break;
        case 14: _t->on_buttonBox_rejected(); break;
        case 15: _t->on_lineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
