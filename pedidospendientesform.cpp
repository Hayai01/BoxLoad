#include "pedidospendientesform.h"
#include "ui_pedidospendientesform.h"

PedidosPendientesForm::PedidosPendientesForm(QWidget *parent,GestorProductos *gestorProductos)
    :QWidget(parent),ui(new Ui::PedidosPendientesForm),
    m_gestorProductos(gestorProductos)
{
    ui->setupUi(this);
    cargarDatos();

    QStringList headers;
    headers << "Producto" << "Unidades" << "Costo del Pedido" << "Eliminar";
    ui->tablaPedidos->setColumnCount(headers.size());
    ui->tablaPedidos->setHorizontalHeaderLabels(headers);


}

PedidosPendientesForm::~PedidosPendientesForm()
{
    delete ui;
}

void PedidosPendientesForm::cargarDatos()
{
    // Obtener la lista de productos desde el GestorProductos
    const QVector<Producto*>& productos = m_gestorProductos->obtenerProductos();

    // Agregar productos al comboBox en NuevoForm
    for (const Producto* producto : productos) {
        ui->productosComboBox->addItem(producto->nombre());
    }
}

void PedidosPendientesForm::on_pushButton_released()
{
    // Obtener el índice del producto seleccionado en el comboBox
    int index = ui->productosComboBox->currentIndex();

    // Verificar si el índice es válido
    if (index >= 0 && index < m_gestorProductos->obtenerProductos().size()) {
        // Obtener el producto seleccionado
        const Producto* productoSeleccionado = m_gestorProductos->obtenerProductos().at(index);

        // Obtener las unidades ingresadas
        int unidades = ui->unidadesSpinBox->value();

        // Obtener el costo de compra del producto seleccionado
        float costoCompra = productoSeleccionado->precioCompra();

        // Calcular el costo total del pedido
        float costoPedido = unidades * costoCompra;

        // Insertar una nueva fila en la tabla con los valores del producto, unidades, costo del pedido y un botón de eliminación
        int rowCount = ui->tablaPedidos->rowCount();
        ui->tablaPedidos->insertRow(rowCount);

        QTableWidgetItem *itemProducto = new QTableWidgetItem(productoSeleccionado->nombre());
        QTableWidgetItem *itemUnidades = new QTableWidgetItem(QString::number(unidades));
        QTableWidgetItem *itemCostoPedido = new QTableWidgetItem(QString::number(costoPedido));

        ui->tablaPedidos->setItem(rowCount, 0, itemProducto); // Columna de Producto
        ui->tablaPedidos->setItem(rowCount, 1, itemUnidades); // Columna de Unidades
        ui->tablaPedidos->setItem(rowCount, 2, itemCostoPedido); // Columna de Costo del pedido

        // Crear un botón de eliminación
        QPushButton *eliminarButton = new QPushButton("Eliminar");
        connect(eliminarButton, &QPushButton::clicked, [this, rowCount]() {
            // Eliminar la fila correspondiente al botón de eliminación clickeado
            ui->tablaPedidos->removeRow(rowCount);
        });

        // Insertar el botón de eliminación en la última columna de la nueva fila
        ui->tablaPedidos->setCellWidget(rowCount, 3, eliminarButton);
    } else {
        // Manejar el caso en que el índice no es válido
        // Por ejemplo, mostrar un mensaje de error
    }
}
