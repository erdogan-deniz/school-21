/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qt_viewer/mainwindow.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_pushButton_clicked",
    "",
    "on_lineEdit_textChanged",
    "arg1",
    "lineEdit_2_setText",
    "obj_data",
    "on_pushButton_4_clicked",
    "on_pushButton_3_clicked",
    "on_pushButton_2_clicked",
    "on_pushButton_5_clicked",
    "on_bZoom_it_clicked",
    "on_bZoom_out_clicked",
    "on_horizontalSlider_valueChanged",
    "value",
    "on_horizontalSlider_2_valueChanged",
    "on_horizontalSlider_3_valueChanged",
    "closeEvent",
    "QCloseEvent*",
    "writeSettings",
    "readSettings",
    "on_pushButton_6_clicked",
    "on_pushButton_7_clicked",
    "gifMaking",
    "on_horizontalSlider_4_valueChanged",
    "on_comboBox_2_currentTextChanged",
    "on_horizontalSlider_5_valueChanged",
    "on_horizontalSlider_6_valueChanged",
    "on_horizontalSlider_7_valueChanged",
    "on_comboBox_3_currentTextChanged",
    "on_comboBox_4_currentTextChanged",
    "on_comboBox_5_currentTextChanged",
    "on_btn_settings_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[66];
    char stringdata0[11];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[24];
    char stringdata4[5];
    char stringdata5[19];
    char stringdata6[9];
    char stringdata7[24];
    char stringdata8[24];
    char stringdata9[24];
    char stringdata10[24];
    char stringdata11[20];
    char stringdata12[21];
    char stringdata13[33];
    char stringdata14[6];
    char stringdata15[35];
    char stringdata16[35];
    char stringdata17[11];
    char stringdata18[13];
    char stringdata19[14];
    char stringdata20[13];
    char stringdata21[24];
    char stringdata22[24];
    char stringdata23[10];
    char stringdata24[35];
    char stringdata25[33];
    char stringdata26[35];
    char stringdata27[35];
    char stringdata28[35];
    char stringdata29[33];
    char stringdata30[33];
    char stringdata31[33];
    char stringdata32[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 21),  // "on_pushButton_clicked"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 23),  // "on_lineEdit_textChanged"
        QT_MOC_LITERAL(58, 4),  // "arg1"
        QT_MOC_LITERAL(63, 18),  // "lineEdit_2_setText"
        QT_MOC_LITERAL(82, 8),  // "obj_data"
        QT_MOC_LITERAL(91, 23),  // "on_pushButton_4_clicked"
        QT_MOC_LITERAL(115, 23),  // "on_pushButton_3_clicked"
        QT_MOC_LITERAL(139, 23),  // "on_pushButton_2_clicked"
        QT_MOC_LITERAL(163, 23),  // "on_pushButton_5_clicked"
        QT_MOC_LITERAL(187, 19),  // "on_bZoom_it_clicked"
        QT_MOC_LITERAL(207, 20),  // "on_bZoom_out_clicked"
        QT_MOC_LITERAL(228, 32),  // "on_horizontalSlider_valueChanged"
        QT_MOC_LITERAL(261, 5),  // "value"
        QT_MOC_LITERAL(267, 34),  // "on_horizontalSlider_2_valueCh..."
        QT_MOC_LITERAL(302, 34),  // "on_horizontalSlider_3_valueCh..."
        QT_MOC_LITERAL(337, 10),  // "closeEvent"
        QT_MOC_LITERAL(348, 12),  // "QCloseEvent*"
        QT_MOC_LITERAL(361, 13),  // "writeSettings"
        QT_MOC_LITERAL(375, 12),  // "readSettings"
        QT_MOC_LITERAL(388, 23),  // "on_pushButton_6_clicked"
        QT_MOC_LITERAL(412, 23),  // "on_pushButton_7_clicked"
        QT_MOC_LITERAL(436, 9),  // "gifMaking"
        QT_MOC_LITERAL(446, 34),  // "on_horizontalSlider_4_valueCh..."
        QT_MOC_LITERAL(481, 32),  // "on_comboBox_2_currentTextChanged"
        QT_MOC_LITERAL(514, 34),  // "on_horizontalSlider_5_valueCh..."
        QT_MOC_LITERAL(549, 34),  // "on_horizontalSlider_6_valueCh..."
        QT_MOC_LITERAL(584, 34),  // "on_horizontalSlider_7_valueCh..."
        QT_MOC_LITERAL(619, 32),  // "on_comboBox_3_currentTextChanged"
        QT_MOC_LITERAL(652, 32),  // "on_comboBox_4_currentTextChanged"
        QT_MOC_LITERAL(685, 32),  // "on_comboBox_5_currentTextChanged"
        QT_MOC_LITERAL(718, 23)   // "on_btn_settings_clicked"
    },
    "MainWindow",
    "on_pushButton_clicked",
    "",
    "on_lineEdit_textChanged",
    "arg1",
    "lineEdit_2_setText",
    "obj_data",
    "on_pushButton_4_clicked",
    "on_pushButton_3_clicked",
    "on_pushButton_2_clicked",
    "on_pushButton_5_clicked",
    "on_bZoom_it_clicked",
    "on_bZoom_out_clicked",
    "on_horizontalSlider_valueChanged",
    "value",
    "on_horizontalSlider_2_valueChanged",
    "on_horizontalSlider_3_valueChanged",
    "closeEvent",
    "QCloseEvent*",
    "writeSettings",
    "readSettings",
    "on_pushButton_6_clicked",
    "on_pushButton_7_clicked",
    "gifMaking",
    "on_horizontalSlider_4_valueChanged",
    "on_comboBox_2_currentTextChanged",
    "on_horizontalSlider_5_valueChanged",
    "on_horizontalSlider_6_valueChanged",
    "on_horizontalSlider_7_valueChanged",
    "on_comboBox_3_currentTextChanged",
    "on_comboBox_4_currentTextChanged",
    "on_comboBox_5_currentTextChanged",
    "on_btn_settings_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  176,    2, 0x0a,    1 /* Public */,
       3,    1,  177,    2, 0x0a,    2 /* Public */,
       5,    1,  180,    2, 0x0a,    4 /* Public */,
       7,    0,  183,    2, 0x08,    6 /* Private */,
       8,    0,  184,    2, 0x08,    7 /* Private */,
       9,    0,  185,    2, 0x08,    8 /* Private */,
      10,    0,  186,    2, 0x08,    9 /* Private */,
      11,    0,  187,    2, 0x08,   10 /* Private */,
      12,    0,  188,    2, 0x08,   11 /* Private */,
      13,    1,  189,    2, 0x08,   12 /* Private */,
      15,    1,  192,    2, 0x08,   14 /* Private */,
      16,    1,  195,    2, 0x08,   16 /* Private */,
      17,    1,  198,    2, 0x08,   18 /* Private */,
      19,    0,  201,    2, 0x08,   20 /* Private */,
      20,    0,  202,    2, 0x08,   21 /* Private */,
      21,    0,  203,    2, 0x08,   22 /* Private */,
      22,    0,  204,    2, 0x08,   23 /* Private */,
      23,    0,  205,    2, 0x08,   24 /* Private */,
      24,    1,  206,    2, 0x08,   25 /* Private */,
      25,    1,  209,    2, 0x08,   27 /* Private */,
      26,    1,  212,    2, 0x08,   29 /* Private */,
      27,    1,  215,    2, 0x08,   31 /* Private */,
      28,    1,  218,    2, 0x08,   33 /* Private */,
      29,    1,  221,    2, 0x08,   35 /* Private */,
      30,    1,  224,    2, 0x08,   37 /* Private */,
      31,    1,  227,    2, 0x08,   39 /* Private */,
      32,    0,  230,    2, 0x08,   41 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_lineEdit_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'lineEdit_2_setText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<obj_data, std::false_type>,
        // method 'on_pushButton_4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_5_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_bZoom_it_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_bZoom_out_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_horizontalSlider_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_horizontalSlider_2_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_horizontalSlider_3_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'closeEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCloseEvent *, std::false_type>,
        // method 'writeSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_6_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_7_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'gifMaking'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_horizontalSlider_4_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_comboBox_2_currentTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_horizontalSlider_5_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_horizontalSlider_6_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_horizontalSlider_7_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_comboBox_3_currentTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_comboBox_4_currentTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_comboBox_5_currentTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_btn_settings_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_lineEdit_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->lineEdit_2_setText((*reinterpret_cast< std::add_pointer_t<obj_data>>(_a[1]))); break;
        case 3: _t->on_pushButton_4_clicked(); break;
        case 4: _t->on_pushButton_3_clicked(); break;
        case 5: _t->on_pushButton_2_clicked(); break;
        case 6: _t->on_pushButton_5_clicked(); break;
        case 7: _t->on_bZoom_it_clicked(); break;
        case 8: _t->on_bZoom_out_clicked(); break;
        case 9: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->on_horizontalSlider_2_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_horizontalSlider_3_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->closeEvent((*reinterpret_cast< std::add_pointer_t<QCloseEvent*>>(_a[1]))); break;
        case 13: _t->writeSettings(); break;
        case 14: _t->readSettings(); break;
        case 15: _t->on_pushButton_6_clicked(); break;
        case 16: _t->on_pushButton_7_clicked(); break;
        case 17: _t->gifMaking(); break;
        case 18: _t->on_horizontalSlider_4_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 19: _t->on_comboBox_2_currentTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->on_horizontalSlider_5_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 21: _t->on_horizontalSlider_6_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 22: _t->on_horizontalSlider_7_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 23: _t->on_comboBox_3_currentTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 24: _t->on_comboBox_4_currentTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 25: _t->on_comboBox_5_currentTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 26: _t->on_btn_settings_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 27;
    }
    return _id;
}
QT_WARNING_POP
