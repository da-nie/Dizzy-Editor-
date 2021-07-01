/****************************************************************************
** Meta object code from reading C++ file 'cdialog_animations.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DizzyEditor/cdialog_animations.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cdialog_animations.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CDialog_Animations_t {
    QByteArrayData data[7];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CDialog_Animations_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CDialog_Animations_t qt_meta_stringdata_CDialog_Animations = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CDialog_Animations"
QT_MOC_LITERAL(1, 19, 26), // "on_cPushButton_Add_clicked"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 28), // "on_cPushButton_Clear_clicked"
QT_MOC_LITERAL(4, 76, 29), // "on_cPushButton_Delete_clicked"
QT_MOC_LITERAL(5, 106, 29), // "on_cPushButton_Cancel_clicked"
QT_MOC_LITERAL(6, 136, 28) // "on_cPushButton_Apply_clicked"

    },
    "CDialog_Animations\0on_cPushButton_Add_clicked\0"
    "\0on_cPushButton_Clear_clicked\0"
    "on_cPushButton_Delete_clicked\0"
    "on_cPushButton_Cancel_clicked\0"
    "on_cPushButton_Apply_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDialog_Animations[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CDialog_Animations::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CDialog_Animations *_t = static_cast<CDialog_Animations *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cPushButton_Add_clicked(); break;
        case 1: _t->on_cPushButton_Clear_clicked(); break;
        case 2: _t->on_cPushButton_Delete_clicked(); break;
        case 3: _t->on_cPushButton_Cancel_clicked(); break;
        case 4: _t->on_cPushButton_Apply_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CDialog_Animations::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CDialog_Animations.data,
      qt_meta_data_CDialog_Animations,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CDialog_Animations::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDialog_Animations::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CDialog_Animations.stringdata0))
        return static_cast<void*>(const_cast< CDialog_Animations*>(this));
    return QDialog::qt_metacast(_clname);
}

int CDialog_Animations::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
