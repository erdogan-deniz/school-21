/****************************************************************************
** Meta object code from reading C++ file 'window_one.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../window_one.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_one.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSWindow_OneENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSWindow_OneENDCLASS = QtMocHelpers::stringData(
    "Window_One",
    "add_digit",
    "",
    "draw_graph",
    "char*",
    "formula",
    "xBegin",
    "xEnd",
    "yBegin",
    "yEnd",
    "long double*",
    "X",
    "Ui::Window_One*",
    "sx"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSWindow_OneENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[11];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[6];
    char stringdata5[8];
    char stringdata6[7];
    char stringdata7[5];
    char stringdata8[7];
    char stringdata9[5];
    char stringdata10[13];
    char stringdata11[2];
    char stringdata12[16];
    char stringdata13[3];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSWindow_OneENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSWindow_OneENDCLASS_t qt_meta_stringdata_CLASSWindow_OneENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "Window_One"
        QT_MOC_LITERAL(11, 9),  // "add_digit"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 10),  // "draw_graph"
        QT_MOC_LITERAL(33, 5),  // "char*"
        QT_MOC_LITERAL(39, 7),  // "formula"
        QT_MOC_LITERAL(47, 6),  // "xBegin"
        QT_MOC_LITERAL(54, 4),  // "xEnd"
        QT_MOC_LITERAL(59, 6),  // "yBegin"
        QT_MOC_LITERAL(66, 4),  // "yEnd"
        QT_MOC_LITERAL(71, 12),  // "long double*"
        QT_MOC_LITERAL(84, 1),  // "X"
        QT_MOC_LITERAL(86, 15),  // "Ui::Window_One*"
        QT_MOC_LITERAL(102, 2)   // "sx"
    },
    "Window_One",
    "add_digit",
    "",
    "draw_graph",
    "char*",
    "formula",
    "xBegin",
    "xEnd",
    "yBegin",
    "yEnd",
    "long double*",
    "X",
    "Ui::Window_One*",
    "sx"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWindow_OneENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x08,    1 /* Private */,
       3,    7,   27,    2, 0x08,    2 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, 0x80000000 | 10, 0x80000000 | 12,    5,    6,    7,    8,    9,   11,   13,

       0        // eod
};

Q_CONSTINIT const QMetaObject Window_One::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSWindow_OneENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWindow_OneENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWindow_OneENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Window_One, std::true_type>,
        // method 'add_digit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'draw_graph'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<long double *, std::false_type>,
        QtPrivate::TypeAndForceComplete<Ui::Window_One *, std::false_type>
    >,
    nullptr
} };

void Window_One::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Window_One *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->add_digit(); break;
        case 1: _t->draw_graph((*reinterpret_cast< std::add_pointer_t<char*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<long double*>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<Ui::Window_One*>>(_a[7]))); break;
        default: ;
        }
    }
}

const QMetaObject *Window_One::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window_One::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWindow_OneENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Window_One::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
