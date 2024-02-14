#include "proveedor.h"

Proveedor::Proveedor()
{

}

Proveedor::Proveedor(const QString &nombre, const QString &direccion, const QString &telefono)
    : m_nombre(nombre), m_direccion(direccion), m_telefono(telefono) {}

QString Proveedor::nombre() const
{
    return m_nombre;
}

void Proveedor::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

QString Proveedor::direccion() const
{
    return m_direccion;
}

void Proveedor::setDireccion(const QString &newDireccion)
{
    m_direccion = newDireccion;
}

QString Proveedor::telefono() const
{
    return m_telefono;
}

void Proveedor::setTelefono(const QString &newTelefono)
{
    m_telefono = newTelefono;
}
