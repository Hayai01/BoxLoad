#include "kardexform.h"
#include "ui_kardexform.h"

KardexForm::KardexForm(QWidget *parent, GestorProductos *gestorProductos)
    : QWidget(parent), ui(new Ui::KardexForm), m_gestorProductos(gestorProductos)
{
    ui->setupUi(this);
    // Configuración de la tabla
    ui->historialTable->setColumnCount(7); // Establecer el número de columnas

    // Establecer los encabezados de las columnas
    QStringList headers;
    headers << "Fecha y Hora" << "SKU" << "Nombre" << "Descripción" << "Precio de Venta" << "Precio de Compra" << "Unidades";
               ui->historialTable->setHorizontalHeaderLabels(headers);

    // Ajustar el tamaño de las columnas para que se ajusten al contenido
    ui->historialTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    cargarDatos();
    connect(ui->productosComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &KardexForm::actualizarHistorial);
}
KardexForm::~KardexForm()
{
    delete ui;
}

void KardexForm::cargarDatos()
{
    // Obtener la lista de productos desde el GestorProductos
    const QVector<Producto*>& productos = m_gestorProductos->obtenerProductos();

    // Agregar productos al comboBox en NuevoForm
    for (const Producto* producto : productos) {
        ui->productosComboBox->addItem(producto->nombre());
    }

}

void KardexForm::actualizarHistorial()
{
    qDebug() << "Actualizando historial...";

    // Limpiar la tabla de historial
    ui->historialTable->clearContents();
    ui->historialTable->setRowCount(0);

    // Obtener el índice del producto seleccionado
    int index = ui->productosComboBox->currentIndex();
    qDebug() << "Índice seleccionado:" << index;

        // Verificar si el índice es válido
        if (index >= 0 && index < m_gestorProductos->obtenerProductos().size()) {
        qDebug() << "Producto seleccionado válido.";

            // Obtener el historial del producto seleccionado
            QVector<QPair<QDateTime, Producto>> historial = m_gestorProductos->historial(index);
        qDebug() << "Tamaño del historial:" << historial.size();
                                                   qDebug() << "Historial:";
            for (const auto& registro : historial) {
                qDebug() << "Fecha y hora:" << registro.first.toString();
                qDebug() << "Producto:" << registro.second.nombre();
            }

            for (const QPair<QDateTime, Producto>& registro : historial) {
            const Producto& producto = registro.second;
            const QDateTime& fechaHora = registro.first;

            int rowCount = ui->historialTable->rowCount();
            qDebug() << "Agregando fila:" << rowCount;

            ui->historialTable->insertRow(rowCount);

            // Añadir datos a las celdas de la fila
            QTableWidgetItem *itemFechaHora = new QTableWidgetItem(fechaHora.toString());
            QTableWidgetItem *itemSKU = new QTableWidgetItem(producto.SKU());
            QTableWidgetItem *itemNombre = new QTableWidgetItem(producto.nombre());
            QTableWidgetItem *itemDescripcion = new QTableWidgetItem(producto.descripcion());
            QTableWidgetItem *itemPrecioVenta = new QTableWidgetItem(QString::number(producto.precioVenta()));
            QTableWidgetItem *itemPrecioCompra = new QTableWidgetItem(QString::number(producto.precioCompra()));
            QTableWidgetItem *itemUnidades = new QTableWidgetItem(QString::number(producto.unidades()));

            ui->historialTable->setItem(rowCount, 0, itemFechaHora);
            ui->historialTable->setItem(rowCount, 1, itemSKU);
            ui->historialTable->setItem(rowCount, 2, itemNombre);
            ui->historialTable->setItem(rowCount, 3, itemDescripcion);
            ui->historialTable->setItem(rowCount, 4, itemPrecioVenta);
            ui->historialTable->setItem(rowCount, 5, itemPrecioCompra);
            ui->historialTable->setItem(rowCount, 6, itemUnidades);
        }
    } else {
        qDebug() << "Índice seleccionado inválido.";
    }
}
