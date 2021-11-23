/****************************************************************************
** Meta object code from reading C++ file 'Hud.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Hud.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Hud.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Hud_t {
    QByteArrayData data[11];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Hud_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Hud_t qt_meta_stringdata_Hud = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Hud"
QT_MOC_LITERAL(1, 4, 27), // "increase_max_health_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 29), // "increase_health_regen_clicked"
QT_MOC_LITERAL(4, 63, 23), // "increase_damage_clicked"
QT_MOC_LITERAL(5, 87, 31), // "increase_movement_speed_clicked"
QT_MOC_LITERAL(6, 119, 29), // "increase_attack_speed_clicked"
QT_MOC_LITERAL(7, 149, 29), // "increase_bullet_speed_clicked"
QT_MOC_LITERAL(8, 179, 14), // "increase_level"
QT_MOC_LITERAL(9, 194, 16), // "update_btn_color"
QT_MOC_LITERAL(10, 211, 13) // "check_upgrade"

    },
    "Hud\0increase_max_health_clicked\0\0"
    "increase_health_regen_clicked\0"
    "increase_damage_clicked\0"
    "increase_movement_speed_clicked\0"
    "increase_attack_speed_clicked\0"
    "increase_bullet_speed_clicked\0"
    "increase_level\0update_btn_color\0"
    "check_upgrade"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Hud[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,

       0        // eod
};

void Hud::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Hud *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->increase_max_health_clicked(); break;
        case 1: _t->increase_health_regen_clicked(); break;
        case 2: _t->increase_damage_clicked(); break;
        case 3: _t->increase_movement_speed_clicked(); break;
        case 4: _t->increase_attack_speed_clicked(); break;
        case 5: _t->increase_bullet_speed_clicked(); break;
        case 6: _t->increase_level(); break;
        case 7: _t->update_btn_color(); break;
        case 8: { bool _r = _t->check_upgrade();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Hud::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Hud.data,
    qt_meta_data_Hud,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Hud::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Hud::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Hud.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Hud::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
