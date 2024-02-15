#include "gestorproductos.h"

GestorProductos::GestorProductos() {
    // Puedes realizar inicializaciones adicionales si es necesario
}

void GestorProductos::agregarProducto(const Producto &producto) {
    m_productos.append(new Producto(producto));

    QDateTime fechaHoraActual = QDateTime::currentDateTime();

    m_productos.last()->agregarRegistro(fechaHoraActual);
}

const QVector<Producto*>& GestorProductos::obtenerProductos() const {
    return m_productos;
}

void GestorProductos::anadirUnidades(int indiceProducto, int unidades)
{
    if (indiceProducto >= 0 && indiceProducto < m_productos.size()) {
        Producto* producto = m_productos[indiceProducto];

        float precioCompraActual = producto->precioCompra();
        float precioVentaActual = producto->precioVenta();
        int unidadesActuales = producto->unidades();

        float nuevoPrecioCompra = ((precioCompraActual * unidadesActuales) +
                                   (precioCompraActual * unidades)) /
                                  (unidadesActuales + unidades);

        float nuevoPrecioVenta = ((precioVentaActual * unidadesActuales) +
                                  (nuevoPrecioCompra * unidades)) /
                                 (unidadesActuales + unidades);

        producto->setPrecioCompra(nuevoPrecioCompra);
        producto->setPrecioVenta(nuevoPrecioVenta + nuevoPrecioVenta*0.25);
        producto->setUnidades(unidadesActuales + unidades);

        QDateTime fechaHoraActual = QDateTime::currentDateTime();

        producto->agregarRegistro(fechaHoraActual);
    }
}



void GestorProductos::eliminarUnidades(int indiceProducto, int unidades)
{
    if (indiceProducto >= 0 && indiceProducto < m_productos.size()) {
        Producto* producto = m_productos[indiceProducto];
        producto->setUnidades(producto->unidades() - unidades);

        QDateTime fechaHoraActual = QDateTime::currentDateTime();

        producto->agregarRegistro(fechaHoraActual);
    }
}

QQueue<QPair<QDateTime, Producto>> GestorProductos::historial(int indiceProducto) const {
    QQueue<QPair<QDateTime, Producto>> historialProducto;

    if (indiceProducto >= 0 && indiceProducto < m_productos.size()) {
        QVector<QPair<QDateTime, Producto>> historialVector = m_productos[indiceProducto]->obtenerHistorial();
        for (const auto &registro : historialVector) {
            historialProducto.enqueue(registro);
        }
    }

    return historialProducto;
}
