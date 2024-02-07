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
    // Obtener la lista de productos desde el GestorProductos
    const QVector<Producto*>& productos = m_gestorProductos->obtenerProductos();

    // Agregar productos al comboBox en NuevoForm
    for (const Producto* producto : productos) {
        ui->productosComboBox->addItem(producto->nombre());
    }

    connect(ui->productosComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        // Verificar si el índice es válido
        if (index >= 0 && index < productos.size()) {
            const Producto* productoSeleccionado = productos.at(index);

            // Obtener las unidades del producto seleccionado
            int unidades = productoSeleccionado->unidades();

            // Actualizar el texto del QLabel con las unidades existentes
            ui->unidadesExistentesLabel->setText(QString("Unidades existentes: %1").arg(unidades));
        } else {
            // Manejar el caso en que el índice no es válido
            ui->unidadesExistentesLabel->setText("Unidades existentes: N/A");
        }
    });
}

void NuevoForm::on_anadirButton_released()
{
    // Obtener el índice del producto seleccionado
    int index = ui->productosComboBox->currentIndex();

    // Verificar si el índice es válido
    if (index >= 0 && index < m_gestorProductos->obtenerProductos().size()) {
        // Obtener el número de unidades a añadir desde el spinBox
        int unidadesA = ui->anadirUnidadesSpinBox->value();

        // Añadir las unidades al producto seleccionado en GestorProductos
        m_gestorProductos->anadirUnidades(index, unidadesA);

        // Actualizar el texto del QLabel con las unidades existentes
        const Producto* productoSeleccionado = m_gestorProductos->obtenerProductos().at(index);
        ui->unidadesExistentesLabel->setText(QString("Unidades existentes: %1").arg(productoSeleccionado->unidades()));
    }
    close();
}

