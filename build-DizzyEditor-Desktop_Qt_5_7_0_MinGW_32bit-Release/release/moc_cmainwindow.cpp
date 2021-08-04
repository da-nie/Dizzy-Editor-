/****************************************************************************
** Meta object code from reading C++ file 'cmainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DizzyEditor/cmainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CMainWindow_t {
    QByteArrayData data[15];
    char stringdata0[417];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMainWindow_t qt_meta_stringdata_CMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CMainWindow"
QT_MOC_LITERAL(1, 12, 38), // "on_cCheckBox_Matherial_Barrie..."
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 41), // "on_cCheckBox_Matherial_FirstP..."
QT_MOC_LITERAL(4, 94, 47), // "on_cCheckBox_Matherial_Before..."
QT_MOC_LITERAL(5, 142, 34), // "on_cPushButton_SetPartName_cl..."
QT_MOC_LITERAL(6, 177, 28), // "on_cAction_SaveMap_triggered"
QT_MOC_LITERAL(7, 206, 28), // "on_cAction_LoadMap_triggered"
QT_MOC_LITERAL(8, 235, 30), // "on_cAction_ExportMap_triggered"
QT_MOC_LITERAL(9, 266, 23), // "On_ToolBar_Main_SetPart"
QT_MOC_LITERAL(10, 290, 26), // "On_ToolBar_Main_SelectPart"
QT_MOC_LITERAL(11, 317, 23), // "On_ToolBar_Main_MoveMap"
QT_MOC_LITERAL(12, 341, 30), // "on_cAction_SaveMapAs_triggered"
QT_MOC_LITERAL(13, 372, 38), // "on_cComboBox_Scale_currentInd..."
QT_MOC_LITERAL(14, 411, 5) // "index"

    },
    "CMainWindow\0on_cCheckBox_Matherial_Barrier_clicked\0"
    "\0on_cCheckBox_Matherial_FirstPlane_clicked\0"
    "on_cCheckBox_Matherial_BeforeBackground_clicked\0"
    "on_cPushButton_SetPartName_clicked\0"
    "on_cAction_SaveMap_triggered\0"
    "on_cAction_LoadMap_triggered\0"
    "on_cAction_ExportMap_triggered\0"
    "On_ToolBar_Main_SetPart\0"
    "On_ToolBar_Main_SelectPart\0"
    "On_ToolBar_Main_MoveMap\0"
    "on_cAction_SaveMapAs_triggered\0"
    "on_cComboBox_Scale_currentIndexChanged\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void CMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CMainWindow *_t = static_cast<CMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cCheckBox_Matherial_Barrier_clicked(); break;
        case 1: _t->on_cCheckBox_Matherial_FirstPlane_clicked(); break;
        case 2: _t->on_cCheckBox_Matherial_BeforeBackground_clicked(); break;
        case 3: _t->on_cPushButton_SetPartName_clicked(); break;
        case 4: _t->on_cAction_SaveMap_triggered(); break;
        case 5: _t->on_cAction_LoadMap_triggered(); break;
        case 6: _t->on_cAction_ExportMap_triggered(); break;
        case 7: _t->On_ToolBar_Main_SetPart(); break;
        case 8: _t->On_ToolBar_Main_SelectPart(); break;
        case 9: _t->On_ToolBar_Main_MoveMap(); break;
        case 10: _t->on_cAction_SaveMapAs_triggered(); break;
        case 11: _t->on_cComboBox_Scale_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CMainWindow.data,
      qt_meta_data_CMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CMainWindow.stringdata0))
        return static_cast<void*>(const_cast< CMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
