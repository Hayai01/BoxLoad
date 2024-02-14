#ifndef GESTORPRODUCTOS_H
#define GESTORPRODUCTOS_H

#include <QVector>
#include <QTime>
#include "producto.h"
#include <QQueue>

using namespace std;

class GestorProductos {
public:
    GestorProductos();

    void agregarProducto(const Producto &producto);
    const QVector<Producto*>& obtenerProductos() const;
    void anadirUnidades(int indiceProducto, int unidades);
    void eliminarUnidades(int indiceProducto, int unidades);
    QQueue<QPair<QDateTime, Producto>> historial(int indiceProducto) const;
    // Modificado


private:
    QVector<Producto*> m_productos;

};
#endif // GESTORPRODUCTOS_H
