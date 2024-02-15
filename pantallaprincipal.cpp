#include "pantallaprincipal.h"
#include "ui_pantallaprincipal.h"
#include <QStack>

#include "nuevoproductoform.h"
#include "gestorproductos.h"
#include "nuevoform.h"
#include "egresoform.h"
#include "kardexform.h"
#include "pedidospendientesform.h"


PantallaPrincipal::PantallaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PantallaPrincipal)
{
    ui->setupUi(this);


    setWindowTitle(tr("Gestión de Productos"));
        m_gestorProductos = new GestorProductos();
    cargarDatos();
    QStringList headers;
    headers << tr("SKU") << tr("Nombre") << tr("Descripción") << tr("Precio de Venta") << tr("Precio de Compra") << tr("Unidades");
                                                                                                                    ui->tablaProductos->setColumnCount(headers.size());
    ui->tablaProductos->setHorizontalHeaderLabels(headers);
    ui->tablaProductos->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);




    this->setStyleSheet(
        "font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;"
        "font-size: 14px; /* Tamaño de letra */"
        "padding: 5px; /* Espaciado interno de 5 píxeles */"
        "margin: 5px; /* Margen externo de 5 píxeles */"
        );


}

PantallaPrincipal::~PantallaPrincipal()
{
    delete m_gestorProductos;
    delete ui;
}

void PantallaPrincipal::cargarDatos()
{

    // Obtener la lista de productos desde el GestorProductos
    const QVector<Producto*>& productosList = m_gestorProductos->obtenerProductos();

    // Convertir la lista de productos a una pila de productos
    QStack<Producto*> productos;
    for (Producto* producto : productosList) {
        productos.push(producto);
    }

    // Limpiar la tabla antes de cargar nuevos datos
    ui->tablaProductos->clearContents();
    ui->tablaProductos->setRowCount(0);

    // Iterar sobre los productos en la pila y cargar los datos en la tabla
    while (!productos.empty()) {
        int rowCount = ui->tablaProductos->rowCount();
        ui->tablaProductos->insertRow(rowCount);

        Producto* producto = productos.top();
        productos.pop();

        QTableWidgetItem *itemSKU = new QTableWidgetItem(producto->SKU());
        QTableWidgetItem *itemNombre = new QTableWidgetItem(producto->nombre());
        QTableWidgetItem *itemDescripcion = new QTableWidgetItem(producto->descripcion());
        QTableWidgetItem *itemPrecioVenta = new QTableWidgetItem(QString::number(producto->precioVenta()));
        QTableWidgetItem *itemPrecioCompra = new QTableWidgetItem(QString::number(producto->precioCompra()));
        QTableWidgetItem *itemUnidades = new QTableWidgetItem(QString::number(producto->unidades()));

        ui->tablaProductos->setItem(rowCount, 0, itemSKU);
        ui->tablaProductos->setItem(rowCount, 1, itemNombre);
        ui->tablaProductos->setItem(rowCount, 2, itemDescripcion);
        ui->tablaProductos->setItem(rowCount, 3, itemPrecioVenta);
        ui->tablaProductos->setItem(rowCount, 4, itemPrecioCompra);
        ui->tablaProductos->setItem(rowCount, 5, itemUnidades);

    }
}

void PantallaPrincipal::on_action_Nuevo_Producto_triggered()
{
    NuevoProductoForm *nuevoProductoForm = new NuevoProductoForm(nullptr, m_gestorProductos);
    nuevoProductoForm->setWindowModality(Qt::ApplicationModal);
    nuevoProductoForm->setWindowTitle(tr("Ingreso de datos"));
    nuevoProductoForm->show();
}


void PantallaPrincipal::on_action_Salir_triggered()
{
    close();
}


void PantallaPrincipal::on_action_Ingreso_triggered()
{
    NuevoForm *nuevoForm = new NuevoForm(nullptr, m_gestorProductos);
    nuevoForm->setWindowModality(Qt::ApplicationModal);
    nuevoForm->setWindowTitle(tr("Ingreso de Producto"));
    nuevoForm->show();

}


void PantallaPrincipal::on_action_Egreso_triggered()
{
    EgresoForm *egresoForm = new EgresoForm(nullptr, m_gestorProductos);
    egresoForm->setWindowModality(Qt::ApplicationModal);
    egresoForm->setWindowTitle(tr("Egreso de Producto"));
    egresoForm->show();

}


void PantallaPrincipal::on_actionKardex_triggered()
{
    KardexForm *kardexForm = new KardexForm(nullptr, m_gestorProductos);
    kardexForm->setWindowModality(Qt::ApplicationModal);
    kardexForm->setWindowTitle(tr("Kardex de Producto"));
    kardexForm->show();

}


void PantallaPrincipal::on_actionPedidos_triggered()
{
    PedidosPendientesForm *pedidosPendientesForm = new PedidosPendientesForm(nullptr, m_gestorProductos);
    pedidosPendientesForm->setWindowModality(Qt::ApplicationModal);
    pedidosPendientesForm->setWindowTitle(tr("Pedidos Pendientes"));
    pedidosPendientesForm->show();

}



void PantallaPrincipal::on_pushButton_released()
{
    cargarDatos();
}
