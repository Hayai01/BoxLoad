#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include <QString>
class Proveedor
{
public:
    Proveedor();
    Proveedor(const QString &nombre, const QString &direccion, const QString &telefono);

    QString nombre() const;
    void setNombre(const QString &newNombre);
    QString direccion() const;
    void setDireccion(const QString &newDireccion);
    QString telefono() const;
    void setTelefono(const QString &newTelefono);

private:
    QString m_nombre;
    QString m_direccion;
    QString m_telefono;
};

#endif // PROVEEDOR_H
