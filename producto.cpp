#include "producto.h"

Producto::Producto()
{

}

Producto::Producto(const QString &SKU, const QString &nombre, const QString &descripcion, float precioVenta, float precioCompra, int unidades)
    : m_SKU(SKU), m_nombre(nombre), m_descripcion(descripcion), m_precioVenta(precioVenta), m_precioCompra(precioCompra), m_unidades(unidades)
{
}

QString Producto::SKU() const
{
    return m_SKU;
}

void Producto::setSKU(const QString &newSKU)
{
    m_SKU = newSKU;
}

QString Producto::nombre() const
{
    return m_nombre;
}

void Producto::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

QString Producto::descripcion() const
{
    return m_descripcion;
}

void Producto::setDescripcion(const QString &newDescripcion)
{
    m_descripcion = newDescripcion;
}

float Producto::precioVenta() const
{
    return m_precioVenta;
}

void Producto::setPrecioVenta(float newPrecioVenta)
{
    m_precioVenta = newPrecioVenta;
}

float Producto::precioCompra() const
{
    return m_precioCompra;
}

void Producto::setPrecioCompra(float newPrecioCompra)
{
    m_precioCompra = newPrecioCompra;
}

int Producto::unidades() const
{
    return m_unidades;
}

void Producto::setUnidades(int newUnidades)
{
    m_unidades = newUnidades;
}

QString Producto::mostrarInformacion() const
{
    QString precioVentaStr = QString::number(m_precioVenta);
    QString precioCompraStr = QString::number(m_precioCompra);
    QString unidadesStr = QString::number(m_unidades);

    return m_SKU + " " + m_nombre + " " + m_descripcion + " " + precioVentaStr + " " + precioCompraStr + " " + unidadesStr;
}

QVector<QPair<QDateTime, Producto>> Producto::obtenerHistorial() const {
    return m_historial;
}


void Producto::agregarRegistro(const QDateTime &fechaHora) {
    m_historial.append(qMakePair(fechaHora, *this));
}
