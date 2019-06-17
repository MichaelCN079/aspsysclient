/****************************************************************************
** Meta object code from reading C++ file 'playworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/aspsysclient/playworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlayWorker_t {
    QByteArrayData data[21];
    char stringdata[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayWorker_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayWorker_t qt_meta_stringdata_PlayWorker = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PlayWorker"
QT_MOC_LITERAL(1, 11, 15), // "signalReadyPlay"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "duration"
QT_MOC_LITERAL(4, 37, 16), // "signalFinishPaly"
QT_MOC_LITERAL(5, 54, 12), // "NvcLiveErr_e"
QT_MOC_LITERAL(6, 67, 7), // "errCode"
QT_MOC_LITERAL(7, 75, 12), // "playGetReady"
QT_MOC_LITERAL(8, 88, 3), // "pix"
QT_MOC_LITERAL(9, 92, 18), // "signalPlayProgress"
QT_MOC_LITERAL(10, 111, 3), // "ntp"
QT_MOC_LITERAL(11, 115, 16), // "signalTimerstart"
QT_MOC_LITERAL(12, 132, 18), // "signalChnPlayState"
QT_MOC_LITERAL(13, 151, 3), // "chn"
QT_MOC_LITERAL(14, 155, 5), // "state"
QT_MOC_LITERAL(15, 161, 17), // "signalPlayTimeOut"
QT_MOC_LITERAL(16, 179, 20), // "signalPrepareConnect"
QT_MOC_LITERAL(17, 200, 5), // "coach"
QT_MOC_LITERAL(18, 206, 21), // "signalChnStateChanged"
QT_MOC_LITERAL(19, 228, 14), // "slotTimerstart"
QT_MOC_LITERAL(20, 243, 12) // "slotTimerout"

    },
    "PlayWorker\0signalReadyPlay\0\0duration\0"
    "signalFinishPaly\0NvcLiveErr_e\0errCode\0"
    "playGetReady\0pix\0signalPlayProgress\0"
    "ntp\0signalTimerstart\0signalChnPlayState\0"
    "chn\0state\0signalPlayTimeOut\0"
    "signalPrepareConnect\0coach\0"
    "signalChnStateChanged\0slotTimerstart\0"
    "slotTimerout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       7,    2,   75,    2, 0x06 /* Public */,
       9,    1,   80,    2, 0x06 /* Public */,
      11,    0,   83,    2, 0x06 /* Public */,
      12,    2,   84,    2, 0x06 /* Public */,
      15,    0,   89,    2, 0x06 /* Public */,
      16,    1,   90,    2, 0x06 /* Public */,
      18,    2,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    0,   98,    2, 0x0a /* Public */,
      20,    0,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int,    8,    2,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   13,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlayWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayWorker *_t = static_cast<PlayWorker *>(_o);
        switch (_id) {
        case 0: _t->signalReadyPlay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalFinishPaly((*reinterpret_cast< NvcLiveErr_e(*)>(_a[1]))); break;
        case 2: _t->playGetReady((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->signalPlayProgress((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->signalTimerstart(); break;
        case 5: _t->signalChnPlayState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->signalPlayTimeOut(); break;
        case 7: _t->signalPrepareConnect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->signalChnStateChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->slotTimerstart(); break;
        case 10: _t->slotTimerout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PlayWorker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayWorker::signalReadyPlay)) {
                *result = 0;
            }
        }
        {
            typedef void (PlayWorker::*_t)(NvcLiveErr_e );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayWorker::signalFinishPaly)) {
                *result = 1;
            }
        }
        {
            typedef void (PlayWorker::*_t)(const QPixmap & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayWorker::playGetReady)) {
                *result = 2;
            }
        }
        {
            typedef void (PlayWorker::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayWorker::signalPlayProgress)) {
                *result = 3;
            }
        }
        {
            typedef void (PlayWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayWorker::signalTimerstart)) {
                *result = 4;
            }
        }
        {
            typedef void (PlayWorker::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayWorker::signalChnPlayState)) {
                *result = 5;
            }
        }
        {
            typedef void (PlayWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayWorker::signalPlayTimeOut)) {
                *result = 6;
            }
        }
        {
            typedef void (PlayWorker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayWorker::signalPrepareConnect)) {
                *result = 7;
            }
        }
        {
            typedef void (PlayWorker::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayWorker::signalChnStateChanged)) {
                *result = 8;
            }
        }
    }
}

const QMetaObject PlayWorker::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_PlayWorker.data,
      qt_meta_data_PlayWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlayWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlayWorker.stringdata))
        return static_cast<void*>(const_cast< PlayWorker*>(this));
    return QThread::qt_metacast(_clname);
}

int PlayWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void PlayWorker::signalReadyPlay(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayWorker::signalFinishPaly(NvcLiveErr_e _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayWorker::playGetReady(const QPixmap & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlayWorker::signalPlayProgress(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlayWorker::signalTimerstart()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void PlayWorker::signalChnPlayState(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PlayWorker::signalPlayTimeOut()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void PlayWorker::signalPrepareConnect(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PlayWorker::signalChnStateChanged(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
