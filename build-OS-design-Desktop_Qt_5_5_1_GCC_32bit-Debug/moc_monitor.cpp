/****************************************************************************
** Meta object code from reading C++ file 'monitor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../OS-design/monitor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'monitor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WorkerThread_monitor_t {
    QByteArrayData data[4];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkerThread_monitor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkerThread_monitor_t qt_meta_stringdata_WorkerThread_monitor = {
    {
QT_MOC_LITERAL(0, 0, 20), // "WorkerThread_monitor"
QT_MOC_LITERAL(1, 21, 11), // "resultReady"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5) // "p_num"

    },
    "WorkerThread_monitor\0resultReady\0\0"
    "p_num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkerThread_monitor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void WorkerThread_monitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WorkerThread_monitor *_t = static_cast<WorkerThread_monitor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WorkerThread_monitor::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkerThread_monitor::resultReady)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject WorkerThread_monitor::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_WorkerThread_monitor.data,
      qt_meta_data_WorkerThread_monitor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WorkerThread_monitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkerThread_monitor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WorkerThread_monitor.stringdata0))
        return static_cast<void*>(const_cast< WorkerThread_monitor*>(this));
    return QThread::qt_metacast(_clname);
}

int WorkerThread_monitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void WorkerThread_monitor::resultReady(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_WorkerThread_cpu_t {
    QByteArrayData data[3];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkerThread_cpu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkerThread_cpu_t qt_meta_stringdata_WorkerThread_cpu = {
    {
QT_MOC_LITERAL(0, 0, 16), // "WorkerThread_cpu"
QT_MOC_LITERAL(1, 17, 11), // "resultReady"
QT_MOC_LITERAL(2, 29, 0) // ""

    },
    "WorkerThread_cpu\0resultReady\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkerThread_cpu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void WorkerThread_cpu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WorkerThread_cpu *_t = static_cast<WorkerThread_cpu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WorkerThread_cpu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkerThread_cpu::resultReady)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject WorkerThread_cpu::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_WorkerThread_cpu.data,
      qt_meta_data_WorkerThread_cpu,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WorkerThread_cpu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkerThread_cpu::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WorkerThread_cpu.stringdata0))
        return static_cast<void*>(const_cast< WorkerThread_cpu*>(this));
    return QThread::qt_metacast(_clname);
}

int WorkerThread_cpu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void WorkerThread_cpu::resultReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
