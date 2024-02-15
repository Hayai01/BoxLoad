#include "nuevoform.h"
#include "ui_nuevoform.h"

NuevoForm::NuevoForm(QWidget *parent, GestorProductos *gestorProductos)
    : QWidget(parent), ui(new Ui::NuevoForm), m_gestorProductos(gestorProductos)
{
    ui->setupUi(this);
     cargarDatos();
}

NuevoForm::~NuevoForm()
{
    delete ui;
}

void NuevoForm::cargarDatos()
{
    const QVector<Producto*>& productos = m_gestorProductos->obtenerProductos();

    for (const Producto* producto : productos) {
        ui->productosComboBox->addItem(producto->nombre());
    }

    connect(ui->productosComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index >= 0 && index < productos.size()) {
            const Producto* productoSeleccionado = productos.at(index);
            int unidades = productoSeleccionado->unidades();
            ui->unidadesExistentesLabel->setText(tr("Unidades existentes: %1").arg(unidades));
        } else {
            ui->unidadesExistentesLabel->setText(tr("Unidades existentes: N/A"));
        }
    });
}

void NuevoForm::on_anadirButton_released()
{
    int index = ui->productosComboBox->currentIndex();

    if (index >= 0 && index < m_gestorProductos->obtenerProductos().size()) {
        int unidadesA = ui->anadirUnidadesSpinBox->value();
        m_gestorProductos->anadirUnidades(index, unidadesA);
        const Producto* productoSeleccionado = m_gestorProductos->obtenerProductos().at(index);
        ui->unidadesExistentesLabel->setText(tr("Unidades existentes: %1").arg(productoSeleccionado->unidades()));
    }
    close();
}
