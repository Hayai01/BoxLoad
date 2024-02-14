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
    setWindowTitle("");
    m_gestorProductos = new GestorProductos();
    cargarDatos();
    QStringList headers;
    headers << "SKU" << "Nombre" << "Descripción" << "Precio de Venta" << "Precio de Compra" << "Unidades";
    ui->tablaProductos->setColumnCount(headers.size());
    ui->tablaProductos->setHorizontalHeaderLabels(headers);
    ui->tablaProductos->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


}

PantallaPrincipal::~PantallaPrincipal()
{
     delete m_gestorProductos;
    delete ui;
}

void PantallaPrincipal::cargarDatos()
{

    // Obtener la lista de productos desde el GestorProductos
    const QList<Producto*>& productosList = m_gestorProductos->obtenerProductos();

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
    nuevoProductoForm->setWindowTitle("Ingreso de datos");
    nuevoProductoForm->show();
    cargarDatos();
}


void PantallaPrincipal::on_action_Salir_triggered()
{
    close();
}


void PantallaPrincipal::on_action_Ingreso_triggered()
{
    NuevoForm *nuevoForm = new NuevoForm(nullptr, m_gestorProductos);
    nuevoForm->setWindowModality(Qt::ApplicationModal);
    nuevoForm->setWindowTitle("Ingreso de Producto");
    nuevoForm->show();
    cargarDatos();
}


void PantallaPrincipal::on_action_Egreso_triggered()
{
    EgresoForm *egresoForm = new EgresoForm(nullptr, m_gestorProductos);
    egresoForm->setWindowModality(Qt::ApplicationModal);
    egresoForm->setWindowTitle("Egreso de Producto");
    egresoForm->show();
    cargarDatos();
}


void PantallaPrincipal::on_actionKardex_triggered()
{
    KardexForm *kardexForm = new KardexForm(nullptr, m_gestorProductos);
    kardexForm->setWindowModality(Qt::ApplicationModal);
    kardexForm->setWindowTitle("Kardex de Producto");
    kardexForm->show();
    cargarDatos();
}


void PantallaPrincipal::on_actionPedidos_triggered()
{
    PedidosPendientesForm *pedidosPendientesForm = new PedidosPendientesForm(nullptr, m_gestorProductos);
    pedidosPendientesForm->setWindowModality(Qt::ApplicationModal);
    pedidosPendientesForm->setWindowTitle("Pedidos Pendientes");
    pedidosPendientesForm->show();
    cargarDatos();
}


