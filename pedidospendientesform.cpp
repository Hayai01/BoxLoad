#include "pedidospendientesform.h"
#include "ui_pedidospendientesform.h"
#include <QFile>


PedidosPendientesForm::PedidosPendientesForm(QWidget *parent,GestorProductos *gestorProductos)
    :QWidget(parent),ui(new Ui::PedidosPendientesForm),
    m_gestorProductos(gestorProductos)
{
    ui->setupUi(this);



    QStringList headers;
    headers << "Producto" << "Unidades" << "Costo del Pedido" << "Eliminar";
    ui->tablaPedidos->setColumnCount(headers.size());
    ui->tablaPedidos->setHorizontalHeaderLabels(headers);

    // Leer los pedidos pendientes desde el archivo y cargarlos en la aplicación
    QFile file("pedidos_pendientes.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 3) {
                Pedido pedido;
                pedido.producto = parts[0];
                pedido.unidades = parts[1].toInt();
                pedido.costo = parts[2].toFloat();
                pedidosPendientes.append(pedido);
            }
        }
        file.close();
    }

    cargarDatos();

}

PedidosPendientesForm::~PedidosPendientesForm()
{


    QFile file("pedidos_pendientes.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Pedido& pedido : pedidosPendientes) {
             out << pedido.producto << "," << pedido.unidades << "," << pedido.costo << "\n";
            qDebug()<<"guardados Datos";
        }
        file.close();
    }
    delete ui;
}


void PedidosPendientesForm::cargarDatos()
{
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

        // Crear un nuevo pedido y agregarlo a la lista de pedidos pendientes
        Pedido nuevoPedido;
        nuevoPedido.producto = productoSeleccionado->nombre();
        nuevoPedido.unidades = unidades;
        nuevoPedido.costo = costoPedido;

        pedidosPendientes.append(nuevoPedido);

        // Actualizar la interfaz gráfica
        int rowCount = ui->tablaPedidos->rowCount();
        ui->tablaPedidos->insertRow(rowCount);
        QTableWidgetItem *itemProducto = new QTableWidgetItem(nuevoPedido.producto);
        QTableWidgetItem *itemUnidades = new QTableWidgetItem(QString::number(nuevoPedido.unidades));
        QTableWidgetItem *itemCostoPedido = new QTableWidgetItem(QString::number(nuevoPedido.costo));
        ui->tablaPedidos->setItem(rowCount, 0, itemProducto);
        ui->tablaPedidos->setItem(rowCount, 1, itemUnidades);
        ui->tablaPedidos->setItem(rowCount, 2, itemCostoPedido);

        QPushButton *eliminarButton = new QPushButton(tr("Eliminar"));
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
