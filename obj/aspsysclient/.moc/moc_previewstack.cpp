/****************************************************************************
** Meta object code from reading C++ file 'previewstack.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/aspsysclient/previewstack.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'previewstack.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PreviewStack_t {
    QByteArrayData data[18];
    char stringdata[338];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PreviewStack_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PreviewStack_t qt_meta_stringdata_PreviewStack = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PreviewStack"
QT_MOC_LITERAL(1, 13, 23), // "sigVideoPauseBtnClicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 6), // "bPause"
QT_MOC_LITERAL(4, 45, 15), // "sigVideoChanged"
QT_MOC_LITERAL(5, 61, 8), // "QWidget*"
QT_MOC_LITERAL(6, 70, 20), // "signalPrepareConnect"
QT_MOC_LITERAL(7, 91, 18), // "signalExitFullView"
QT_MOC_LITERAL(8, 110, 23), // "signalToggleMainSubView"
QT_MOC_LITERAL(9, 134, 26), // "slotCameraSwitchBtnClicked"
QT_MOC_LITERAL(10, 161, 5), // "bFlag"
QT_MOC_LITERAL(11, 167, 25), // "slotCameraLightBtnClicked"
QT_MOC_LITERAL(12, 193, 24), // "slotVideoPauseBtnClicked"
QT_MOC_LITERAL(13, 218, 23), // "slotVideoPlayBtnClicked"
QT_MOC_LITERAL(14, 242, 23), // "slotVideoNextBtnClicked"
QT_MOC_LITERAL(15, 266, 22), // "slotVideoPreBtnClicked"
QT_MOC_LITERAL(16, 289, 24), // "slotvideoAheadBtnClicked"
QT_MOC_LITERAL(17, 314, 23) // "slotVideoSaveBtnClicked"

    },
    "PreviewStack\0sigVideoPauseBtnClicked\0"
    "\0bPause\0sigVideoChanged\0QWidget*\0"
    "signalPrepareConnect\0signalExitFullView\0"
    "signalToggleMainSubView\0"
    "slotCameraSwitchBtnClicked\0bFlag\0"
    "slotCameraLightBtnClicked\0"
    "slotVideoPauseBtnClicked\0"
    "slotVideoPlayBtnClicked\0slotVideoNextBtnClicked\0"
    "slotVideoPreBtnClicked\0slotvideoAheadBtnClicked\0"
    "slotVideoSaveBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PreviewStack[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       6,    1,   85,    2, 0x06 /* Public */,
       7,    0,   88,    2, 0x06 /* Public */,
       8,    0,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   90,    2, 0x0a /* Public */,
      11,    1,   93,    2, 0x0a /* Public */,
      12,    1,   96,    2, 0x0a /* Public */,
      13,    1,   99,    2, 0x0a /* Public */,
      14,    0,  102,    2, 0x0a /* Public */,
      15,    0,  103,    2, 0x0a /* Public */,
      16,    0,  104,    2, 0x0a /* Public */,
      17,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PreviewStack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PreviewStack *_t = static_cast<PreviewStack *>(_o);
        switch (_id) {
        case 0: _t->sigVideoPauseBtnClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sigVideoChanged((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->signalPrepareConnect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalExitFullView(); break;
        case 4: _t->signalToggleMainSubView(); break;
        case 5: _t->slotCameraSwitchBtnClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->slotCameraLightBtnClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->slotVideoPauseBtnClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->slotVideoPlayBtnClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->slotVideoNextBtnClicked(); break;
        case 10: _t->slotVideoPreBtnClicked(); break;
        case 11: _t->slotvideoAheadBtnClicked(); break;
        case 12: _t->slotVideoSaveBtnClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PreviewStack::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewStack::sigVideoPauseBtnClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (PreviewStack::*_t)(QWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewStack::sigVideoChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (PreviewStack::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewStack::signalPrepareConnect)) {
                *result = 2;
            }
        }
        {
            typedef void (PreviewStack::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewStack::signalExitFullView)) {
                *result = 3;
            }
        }
        {
            typedef void (PreviewStack::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewStack::signalToggleMainSubView)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject PreviewStack::staticMetaObject = {
    { &QStackedWidget::staticMetaObject, qt_meta_stringdata_PreviewStack.data,
      qt_meta_data_PreviewStack,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PreviewStack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PreviewStack::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PreviewStack.stringdata))
        return static_cast<void*>(const_cast< PreviewStack*>(this));
    return QStackedWidget::qt_metacast(_clname);
}

int PreviewStack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStackedWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void PreviewStack::sigVideoPauseBtnClicked(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PreviewStack::sigVideoChanged(QWidget * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PreviewStack::signalPrepareConnect(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PreviewStack::signalExitFullView()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void PreviewStack::signalToggleMainSubView()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
