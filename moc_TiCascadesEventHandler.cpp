/****************************************************************************
 ** Meta object code from reading C++ file 'TiCascadesEventHandler.h'
 **
 ** Created: Thu Apr 19 10:18:46 2012
 **      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#include "TiCascadesEventHandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TiCascadesEventHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TiCascadesEventHandler[] = {

// content:
        6,// revision
        0,       // classname
        0, 0, // classinfo
        3, 14, // methods
        0, 0, // properties
        0, 0, // enums/sets
        0, 0, // constructors
        0,       // flags
        0,       // signalCount

        // slots: signature, parameters, type, tag, flags
        30, 24, 23, 23, 0x0a,
        51, 24, 23, 23, 0x0a,
        71, 23, 23, 23, 0x0a,

        0        // eod
        };

static const char qt_meta_stringdata_TiCascadesEventHandler[] = {
        "TiCascadesEventHandler\0\0value\0"
                "valueChanging(float)\0valueChanged(float)\0"
                "clicked()\0"
};

void TiCascadesEventHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        Q_ASSERT(staticMetaObject.cast(_o));
        TiCascadesEventHandler *_t = static_cast<TiCascadesEventHandler *>(_o);
        switch (_id)
        {
        case 0:
            _t->valueChanging((*reinterpret_cast<float (*)>(_a[1])));
            break;
        case 1:
            _t->valueChanged((*reinterpret_cast<float (*)>(_a[1])));
            break;
        case 2:
            _t->clicked();
            break;
        default:
            ;
        }
    }
}

const QMetaObjectExtraData TiCascadesEventHandler::staticMetaObjectExtraData = {
        0, qt_static_metacall
};

const QMetaObject TiCascadesEventHandler::staticMetaObject = {
        {&QObject::staticMetaObject, qt_meta_stringdata_TiCascadesEventHandler,
                qt_meta_data_TiCascadesEventHandler, &staticMetaObjectExtraData}
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TiCascadesEventHandler::getStaticMetaObject()
{   return staticMetaObject;}
#endif //Q_NO_DATA_RELOCATION
const QMetaObject *TiCascadesEventHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TiCascadesEventHandler::qt_metacast(const char *_clname)
{
    if (!_clname)
        return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TiCascadesEventHandler))
        return static_cast<void*>(const_cast<TiCascadesEventHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int TiCascadesEventHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
