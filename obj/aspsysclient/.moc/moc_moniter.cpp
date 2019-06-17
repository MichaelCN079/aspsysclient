/****************************************************************************
** Meta object code from reading C++ file 'moniter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/aspsysclient/moniter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moniter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MoniterClient_t {
    QByteArrayData data[24];
    char stringdata[391];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MoniterClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MoniterClient_t qt_meta_stringdata_MoniterClient = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MoniterClient"
QT_MOC_LITERAL(1, 14, 19), // "signalSearchRecords"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 21), // "signalDevicesInfosNVR"
QT_MOC_LITERAL(4, 57, 11), // "QByteArray&"
QT_MOC_LITERAL(5, 69, 21), // "signalDevicesInfosIPC"
QT_MOC_LITERAL(6, 91, 12), // "signalNVRLog"
QT_MOC_LITERAL(7, 104, 12), // "signalIPCLog"
QT_MOC_LITERAL(8, 117, 22), // "signalDeviceNeedUpdate"
QT_MOC_LITERAL(9, 140, 15), // "signalImportCfg"
QT_MOC_LITERAL(10, 156, 14), // "signalDownload"
QT_MOC_LITERAL(11, 171, 21), // "signalGetIPCColorPara"
QT_MOC_LITERAL(12, 193, 22), // "signalGetIPCStreamPara"
QT_MOC_LITERAL(13, 216, 17), // "signalAlarmPushed"
QT_MOC_LITERAL(14, 234, 15), // "signalNtpResult"
QT_MOC_LITERAL(15, 250, 14), // "signalIPCYstNo"
QT_MOC_LITERAL(16, 265, 18), // "signalSetOsdResult"
QT_MOC_LITERAL(17, 284, 14), // "signalNewAlarm"
QT_MOC_LITERAL(18, 299, 4), // "int&"
QT_MOC_LITERAL(19, 304, 14), // "slotReadSocket"
QT_MOC_LITERAL(20, 319, 11), // "slotTimeout"
QT_MOC_LITERAL(21, 331, 16), // "slotLightTimeout"
QT_MOC_LITERAL(22, 348, 19), // "slotSocketConnected"
QT_MOC_LITERAL(23, 368, 22) // "slotSocketDisconnected"

    },
    "MoniterClient\0signalSearchRecords\0\0"
    "signalDevicesInfosNVR\0QByteArray&\0"
    "signalDevicesInfosIPC\0signalNVRLog\0"
    "signalIPCLog\0signalDeviceNeedUpdate\0"
    "signalImportCfg\0signalDownload\0"
    "signalGetIPCColorPara\0signalGetIPCStreamPara\0"
    "signalAlarmPushed\0signalNtpResult\0"
    "signalIPCYstNo\0signalSetOsdResult\0"
    "signalNewAlarm\0int&\0slotReadSocket\0"
    "slotTimeout\0slotLightTimeout\0"
    "slotSocketConnected\0slotSocketDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MoniterClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  114,    2, 0x06 /* Public */,
       3,    1,  117,    2, 0x06 /* Public */,
       5,    1,  120,    2, 0x06 /* Public */,
       6,    1,  123,    2, 0x06 /* Public */,
       7,    1,  126,    2, 0x06 /* Public */,
       8,    1,  129,    2, 0x06 /* Public */,
       9,    1,  132,    2, 0x06 /* Public */,
      10,    0,  135,    2, 0x06 /* Public */,
      11,    1,  136,    2, 0x06 /* Public */,
      12,    1,  139,    2, 0x06 /* Public */,
      13,    0,  142,    2, 0x06 /* Public */,
      14,    0,  143,    2, 0x06 /* Public */,
      15,    1,  144,    2, 0x06 /* Public */,
      16,    0,  147,    2, 0x06 /* Public */,
      17,    2,  148,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    1,  153,    2, 0x0a /* Public */,
      20,    0,  156,    2, 0x0a /* Public */,
      21,    1,  157,    2, 0x0a /* Public */,
      22,    1,  160,    2, 0x0a /* Public */,
      23,    1,  163,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 4,    2,    2,

 // slots: parameters
    QMetaType::QString, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void MoniterClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MoniterClient *_t = static_cast<MoniterClient *>(_o);
        switch (_id) {
        case 0: _t->signalSearchRecords((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalDevicesInfosNVR((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->signalDevicesInfosIPC((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->signalNVRLog((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->signalIPCLog((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->signalDeviceNeedUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->signalImportCfg((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->signalDownload(); break;
        case 8: _t->signalGetIPCColorPara((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 9: _t->signalGetIPCStreamPara((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->signalAlarmPushed(); break;
        case 11: _t->signalNtpResult(); break;
        case 12: _t->signalIPCYstNo((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 13: _t->signalSetOsdResult(); break;
        case 14: _t->signalNewAlarm((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 15: { QString _r = _t->slotReadSocket((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: _t->slotTimeout(); break;
        case 17: _t->slotLightTimeout((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->slotSocketConnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->slotSocketDisconnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MoniterClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalSearchRecords)) {
                *result = 0;
            }
        }
        {
            typedef void (MoniterClient::*_t)(QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalDevicesInfosNVR)) {
                *result = 1;
            }
        }
        {
            typedef void (MoniterClient::*_t)(QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalDevicesInfosIPC)) {
                *result = 2;
            }
        }
        {
            typedef void (MoniterClient::*_t)(QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalNVRLog)) {
                *result = 3;
            }
        }
        {
            typedef void (MoniterClient::*_t)(QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalIPCLog)) {
                *result = 4;
            }
        }
        {
            typedef void (MoniterClient::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalDeviceNeedUpdate)) {
                *result = 5;
            }
        }
        {
            typedef void (MoniterClient::*_t)(QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalImportCfg)) {
                *result = 6;
            }
        }
        {
            typedef void (MoniterClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalDownload)) {
                *result = 7;
            }
        }
        {
            typedef void (MoniterClient::*_t)(QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalGetIPCColorPara)) {
                *result = 8;
            }
        }
        {
            typedef void (MoniterClient::*_t)(QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalGetIPCStreamPara)) {
                *result = 9;
            }
        }
        {
            typedef void (MoniterClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalAlarmPushed)) {
                *result = 10;
            }
        }
        {
            typedef void (MoniterClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalNtpResult)) {
                *result = 11;
            }
        }
        {
            typedef void (MoniterClient::*_t)(QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalIPCYstNo)) {
                *result = 12;
            }
        }
        {
            typedef void (MoniterClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalSetOsdResult)) {
                *result = 13;
            }
        }
        {
            typedef void (MoniterClient::*_t)(int & , QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MoniterClient::signalNewAlarm)) {
                *result = 14;
            }
        }
    }
}

const QMetaObject MoniterClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MoniterClient.data,
      qt_meta_data_MoniterClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MoniterClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MoniterClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MoniterClient.stringdata))
        return static_cast<void*>(const_cast< MoniterClient*>(this));
    return QObject::qt_metacast(_clname);
}

int MoniterClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void MoniterClient::signalSearchRecords(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MoniterClient::signalDevicesInfosNVR(QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MoniterClient::signalDevicesInfosIPC(QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MoniterClient::signalNVRLog(QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MoniterClient::signalIPCLog(QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MoniterClient::signalDeviceNeedUpdate(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MoniterClient::signalImportCfg(QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MoniterClient::signalDownload()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void MoniterClient::signalGetIPCColorPara(QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MoniterClient::signalGetIPCStreamPara(QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MoniterClient::signalAlarmPushed()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}

// SIGNAL 11
void MoniterClient::signalNtpResult()
{
    QMetaObject::activate(this, &staticMetaObject, 11, Q_NULLPTR);
}

// SIGNAL 12
void MoniterClient::signalIPCYstNo(QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MoniterClient::signalSetOsdResult()
{
    QMetaObject::activate(this, &staticMetaObject, 13, Q_NULLPTR);
}

// SIGNAL 14
void MoniterClient::signalNewAlarm(int & _t1, QByteArray & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_END_MOC_NAMESPACE
