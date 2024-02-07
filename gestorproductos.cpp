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
        producto->setUnidades(producto->unidades() + unidades);

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

QVector<QPair<QDateTime, Producto>> GestorProductos::historial(int indiceProducto) const {
    QVector<QPair<QDateTime, Producto>> historialProducto;

    if (indiceProducto >= 0 && indiceProducto < m_productos.size()) {
        historialProducto = m_productos[indiceProducto]->obtenerHistorial();
    }

    return historialProducto;
}
