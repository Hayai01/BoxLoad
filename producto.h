#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QString>
#include <QTime>
#include <stack>
#include <QVector>

using namespace std;

class Producto
{
public:
    Producto();
    Producto(const QString &SKU, const QString &nombre, const QString &descripcion, float precioVenta, float precioCompra, int unidades);
    QString SKU() const;
    void setSKU(const QString &newSKU);
    QString nombre() const;
    void setNombre(const QString &newNombre);
    QString descripcion() const;
    void setDescripcion(const QString &newDescripcion);
    float precioVenta() const;
    void setPrecioVenta(float newPrecioVenta);
    float precioCompra() const;
    void setPrecioCompra(float newPrecioCompra);
    int unidades() const;
    void setUnidades(int newUnidades);
    QString mostrarInformacion() const;
    void agregarRegistro(const QDateTime &fechaHora);
    QVector<QPair<QDateTime, Producto>> obtenerHistorial() const;

private:
    QString m_SKU;
    QString m_nombre;
    QString m_descripcion;
    float m_precioVenta;
    float m_precioCompra;
    int m_unidades;

    QVector<QPair<QDateTime, Producto>> m_historial;

};

#endif // PRODUCTO_H
