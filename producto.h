#ifndef PRODUCTO_H
#define PRODUCTO_H

#include "proveedor.h"
#include <QString>
#include <QTime>
#include <stack>

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

    void agregarProveedor(const Proveedor& proveedor); // Método para agregar un proveedor a la pila
    Proveedor& obtenerProveedor(); // Método para obtener el proveedor en la cima de la pila
    void eliminarProveedor(); // Método para eliminar el proveedor en la cima de la pila
    bool pilaProveedoresVacia(); // Método para verificar si la pila de proveedores está vacía


    QVector<QPair<QDateTime, Producto>> obtenerHistorial() const; // Obtener el historial del producto
    void agregarRegistro(const QDateTime &fechaHora); // Agregar un registro al historial

private:
    QString m_SKU;
    QString m_nombre;
    QString m_descripcion;
    float m_precioVenta;
    float m_precioCompra;
    int m_unidades;

    std::stack<Proveedor> m_pilaProveedores;

    QVector<QPair<QDateTime, Producto>> m_historial;

};

#endif // PRODUCTO_H
