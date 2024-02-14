#include "pantallaprincipal.h"
#include "ui_pantallaprincipal.h"

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
}

PantallaPrincipal::~PantallaPrincipal()
{
     delete m_gestorProductos;
    delete ui;
}


void PantallaPrincipal::on_action_Nuevo_Producto_triggered()
{
    NuevoProductoForm *nuevoProductoForm = new NuevoProductoForm(nullptr, m_gestorProductos);
    nuevoProductoForm->setWindowModality(Qt::ApplicationModal);
    nuevoProductoForm->setWindowTitle("Ingreso de datos");
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
    nuevoForm->setWindowTitle("Ingreso de Producto");
    nuevoForm->show();
}


void PantallaPrincipal::on_action_Egreso_triggered()
{
    EgresoForm *egresoForm = new EgresoForm(nullptr, m_gestorProductos);
    egresoForm->setWindowModality(Qt::ApplicationModal);
    egresoForm->setWindowTitle("Egreso de Producto");
    egresoForm->show();
}


void PantallaPrincipal::on_actionKardex_triggered()
{
    KardexForm *kardexForm = new KardexForm(nullptr, m_gestorProductos);
    kardexForm->setWindowModality(Qt::ApplicationModal);
    kardexForm->setWindowTitle("Kardex de Producto");
    kardexForm->show();
}


void PantallaPrincipal::on_actionPedidos_triggered()
{
    PedidosPendientesForm *pedidosPendientesForm = new PedidosPendientesForm(nullptr, m_gestorProductos);
    pedidosPendientesForm->setWindowModality(Qt::ApplicationModal);
    pedidosPendientesForm->setWindowTitle("Pedidos Pendientes");
    pedidosPendientesForm->show();
}

