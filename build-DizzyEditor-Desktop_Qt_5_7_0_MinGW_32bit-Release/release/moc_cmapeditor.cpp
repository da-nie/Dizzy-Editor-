/****************************************************************************
** Meta object code from reading C++ file 'cmapeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DizzyEditor/cmapeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmapeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CMapEditor_t {
    QByteArrayData data[5];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMapEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMapEditor_t qt_meta_stringdata_CMapEditor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CMapEditor"
QT_MOC_LITERAL(1, 11, 23), // "on_ContextMenu_CopyPart"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 24), // "on_ContextMenu_PastePart"
QT_MOC_LITERAL(4, 61, 25) // "on_ContextMenu_DeletePart"

    },
    "CMapEditor\0on_ContextMenu_CopyPart\0\0"
    "on_ContextMenu_PastePart\0"
    "on_ContextMenu_DeletePart"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMapEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CMapEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CMapEditor *_t = static_cast<CMapEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_ContextMenu_CopyPart(); break;
        case 1: _t->on_ContextMenu_PastePart(); break;
        case 2: _t->on_ContextMenu_DeletePart(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CMapEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CMapEditor.data,
      qt_meta_data_CMapEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CMapEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CMapEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CMapEditor.stringdata0))
        return static_cast<void*>(const_cast< CMapEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int CMapEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
