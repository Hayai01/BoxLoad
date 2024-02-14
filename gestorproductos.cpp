#include "gestorproductos.h"

GestorProductos::GestorProductos() {
    // Puedes realizar inicializaciones adicionales si es necesario
}

void GestorProductos::agregarProducto(const Producto &producto) {
    m_productos.append(new Producto(producto));

    // Obtener la fecha y hora actual
    QDateTime fechaHoraActual = QDateTime::currentDateTime();

    // Registrar el agregado del nuevo producto en el historial
    m_productos.last()->agregarRegistro(fechaHoraActual);
}

const QVector<Producto*>& GestorProductos::obtenerProductos() const {
    return m_productos;
}

void GestorProductos::anadirUnidades(int indiceProducto, int unidades)
{
    if (indiceProducto >= 0 && indiceProducto < m_productos.size()) {
        Producto* producto = m_productos[indiceProducto];

        // Obtener los datos actuales del producto
        float precioCompraActual = producto->precioCompra();
        float precioVentaActual = producto->precioVenta();
        int unidadesActuales = producto->unidades();

        // Calcular el nuevo precio de compra como la media del precio de compra existente
        // y el nuevo precio de compra
        float nuevoPrecioCompra = ((precioCompraActual * unidadesActuales) +
                                   (precioCompraActual * unidades)) /
                                  (unidadesActuales + unidades);

        // Calcular el nuevo precio de venta como la media del precio de venta existente
        // y el nuevo precio de compra
        float nuevoPrecioVenta = ((precioVentaActual * unidadesActuales) +
                                  (nuevoPrecioCompra * unidades)) /
                                 (unidadesActuales + unidades);

        // Actualizar los precios y las unidades del producto
        producto->setPrecioCompra(nuevoPrecioCompra);
        producto->setPrecioVenta(nuevoPrecioVenta + nuevoPrecioVenta*0.25);
        producto->setUnidades(unidadesActuales + unidades);

        // Obtener la fecha y hora actual
        QDateTime fechaHoraActual = QDateTime::currentDateTime();

        // Registrar el cambio en el historial del producto
        producto->agregarRegistro(fechaHoraActual);
    }
}

void GestorProductos::eliminarUnidades(int indiceProducto, int unidades)
{
    if (indiceProducto >= 0 && indiceProducto < m_productos.size()) {
        Producto* producto = m_productos[indiceProducto];
        producto->setUnidades(producto->unidades() - unidades);

        // Obtener la fecha y hora actual
        QDateTime fechaHoraActual = QDateTime::currentDateTime();

        // Registrar el cambio en el historial del producto
        producto->agregarRegistro(fechaHoraActual);
    }
}

QQueue<QPair<QDateTime, Producto>> GestorProductos::historial(int indiceProducto) const {
    QQueue<QPair<QDateTime, Producto>> historialProducto;

    if (indiceProducto >= 0 && indiceProducto < m_productos.size()) {
        QVector<QPair<QDateTime, Producto>> historialVector = m_productos[indiceProducto]->obtenerHistorial().toVector();
        for (const auto &registro : historialVector) {
            historialProducto.enqueue(registro);
        }
    }

    return historialProducto;
}
