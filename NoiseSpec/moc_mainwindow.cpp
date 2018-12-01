/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TOperatorModeUI_t {
    QByteArrayData data[5];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TOperatorModeUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TOperatorModeUI_t qt_meta_stringdata_TOperatorModeUI = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TOperatorModeUI"
QT_MOC_LITERAL(1, 16, 9), // "LostFocus"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 18), // "EnableOperatorMode"
QT_MOC_LITERAL(4, 46, 13) // "ReturnPressed"

    },
    "TOperatorModeUI\0LostFocus\0\0"
    "EnableOperatorMode\0ReturnPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TOperatorModeUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TOperatorModeUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TOperatorModeUI *_t = static_cast<TOperatorModeUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LostFocus(); break;
        case 1: _t->EnableOperatorMode(); break;
        case 2: _t->ReturnPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TOperatorModeUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TOperatorModeUI::LostFocus)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TOperatorModeUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TOperatorModeUI::EnableOperatorMode)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TOperatorModeUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TOperatorModeUI::ReturnPressed)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TOperatorModeUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TOperatorModeUI.data,
      qt_meta_data_TOperatorModeUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TOperatorModeUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TOperatorModeUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TOperatorModeUI.stringdata0))
        return static_cast<void*>(const_cast< TOperatorModeUI*>(this));
    return QObject::qt_metacast(_clname);
}

int TOperatorModeUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void TOperatorModeUI::LostFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TOperatorModeUI::EnableOperatorMode()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void TOperatorModeUI::ReturnPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[32];
    char stringdata0[668];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "on_RawDataRadio_toggled"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 7), // "checked"
QT_MOC_LITERAL(4, 44, 20), // "on_AddButton_clicked"
QT_MOC_LITERAL(5, 65, 23), // "on_deleteButton_clicked"
QT_MOC_LITERAL(6, 89, 25), // "on_DPATable_doubleClicked"
QT_MOC_LITERAL(7, 115, 5), // "index"
QT_MOC_LITERAL(8, 121, 24), // "on_xMinBox_returnPressed"
QT_MOC_LITERAL(9, 146, 24), // "on_xMaxBox_returnPressed"
QT_MOC_LITERAL(10, 171, 24), // "on_yMinBox_returnPressed"
QT_MOC_LITERAL(11, 196, 24), // "on_yMaxBox_returnPressed"
QT_MOC_LITERAL(12, 221, 23), // "on_LogXCheckBox_toggled"
QT_MOC_LITERAL(13, 245, 23), // "on_LogYCheckBox_toggled"
QT_MOC_LITERAL(14, 269, 38), // "on_WindowSelectBox_currentInd..."
QT_MOC_LITERAL(15, 308, 4), // "arg1"
QT_MOC_LITERAL(16, 313, 25), // "on_actionExport_triggered"
QT_MOC_LITERAL(17, 339, 18), // "generateSampleData"
QT_MOC_LITERAL(18, 358, 20), // "MinusOperatorPressed"
QT_MOC_LITERAL(19, 379, 18), // "CancelOperatorMode"
QT_MOC_LITERAL(20, 398, 19), // "on_DPATable_clicked"
QT_MOC_LITERAL(21, 418, 22), // "DPATable_ReturnPressed"
QT_MOC_LITERAL(22, 441, 36), // "on_FFTAverageBox_currentIndex..."
QT_MOC_LITERAL(23, 478, 19), // "ShowDPATableContext"
QT_MOC_LITERAL(24, 498, 3), // "pos"
QT_MOC_LITERAL(25, 502, 22), // "DPAContext_ItemClicked"
QT_MOC_LITERAL(26, 525, 8), // "QAction*"
QT_MOC_LITERAL(27, 534, 6), // "action"
QT_MOC_LITERAL(28, 541, 33), // "on_actionChop_Beginning_trigg..."
QT_MOC_LITERAL(29, 575, 27), // "on_actionChop_End_triggered"
QT_MOC_LITERAL(30, 603, 32), // "on_actionRemove_Offset_triggered"
QT_MOC_LITERAL(31, 636, 31) // "on_actionExport_chart_triggered"

    },
    "MainWindow\0on_RawDataRadio_toggled\0\0"
    "checked\0on_AddButton_clicked\0"
    "on_deleteButton_clicked\0"
    "on_DPATable_doubleClicked\0index\0"
    "on_xMinBox_returnPressed\0"
    "on_xMaxBox_returnPressed\0"
    "on_yMinBox_returnPressed\0"
    "on_yMaxBox_returnPressed\0"
    "on_LogXCheckBox_toggled\0on_LogYCheckBox_toggled\0"
    "on_WindowSelectBox_currentIndexChanged\0"
    "arg1\0on_actionExport_triggered\0"
    "generateSampleData\0MinusOperatorPressed\0"
    "CancelOperatorMode\0on_DPATable_clicked\0"
    "DPATable_ReturnPressed\0"
    "on_FFTAverageBox_currentIndexChanged\0"
    "ShowDPATableContext\0pos\0DPAContext_ItemClicked\0"
    "QAction*\0action\0on_actionChop_Beginning_triggered\0"
    "on_actionChop_End_triggered\0"
    "on_actionRemove_Offset_triggered\0"
    "on_actionExport_chart_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  134,    2, 0x08 /* Private */,
       4,    0,  137,    2, 0x08 /* Private */,
       5,    0,  138,    2, 0x08 /* Private */,
       6,    1,  139,    2, 0x08 /* Private */,
       8,    0,  142,    2, 0x08 /* Private */,
       9,    0,  143,    2, 0x08 /* Private */,
      10,    0,  144,    2, 0x08 /* Private */,
      11,    0,  145,    2, 0x08 /* Private */,
      12,    1,  146,    2, 0x08 /* Private */,
      13,    1,  149,    2, 0x08 /* Private */,
      14,    1,  152,    2, 0x08 /* Private */,
      16,    0,  155,    2, 0x08 /* Private */,
      17,    0,  156,    2, 0x08 /* Private */,
      18,    0,  157,    2, 0x08 /* Private */,
      19,    0,  158,    2, 0x08 /* Private */,
      20,    1,  159,    2, 0x08 /* Private */,
      21,    0,  162,    2, 0x08 /* Private */,
      22,    1,  163,    2, 0x08 /* Private */,
      23,    1,  166,    2, 0x08 /* Private */,
      25,    1,  169,    2, 0x08 /* Private */,
      28,    0,  172,    2, 0x08 /* Private */,
      29,    0,  173,    2, 0x08 /* Private */,
      30,    0,  174,    2, 0x08 /* Private */,
      31,    0,  175,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QPoint,   24,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_RawDataRadio_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_AddButton_clicked(); break;
        case 2: _t->on_deleteButton_clicked(); break;
        case 3: _t->on_DPATable_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_xMinBox_returnPressed(); break;
        case 5: _t->on_xMaxBox_returnPressed(); break;
        case 6: _t->on_yMinBox_returnPressed(); break;
        case 7: _t->on_yMaxBox_returnPressed(); break;
        case 8: _t->on_LogXCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_LogYCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_WindowSelectBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->on_actionExport_triggered(); break;
        case 12: _t->generateSampleData(); break;
        case 13: _t->MinusOperatorPressed(); break;
        case 14: _t->CancelOperatorMode(); break;
        case 15: _t->on_DPATable_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 16: _t->DPATable_ReturnPressed(); break;
        case 17: _t->on_FFTAverageBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->ShowDPATableContext((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 19: _t->DPAContext_ItemClicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 20: _t->on_actionChop_Beginning_triggered(); break;
        case 21: _t->on_actionChop_End_triggered(); break;
        case 22: _t->on_actionRemove_Offset_triggered(); break;
        case 23: _t->on_actionExport_chart_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
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
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
