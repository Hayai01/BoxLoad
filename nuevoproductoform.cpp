#include "nuevoproductoform.h"
#include "ui_nuevoproductoform.h"
#include <QMessageBox>

NuevoProductoForm::NuevoProductoForm(QWidget *parent, GestorProductos *gestorProductos) :
    QWidget(parent),
    ui(new Ui::NuevoProductoForm),
    m_gestorProductos(gestorProductos)
{
    ui->setupUi(this);
    if (m_gestorProductos == nullptr) {
        qDebug() << "Error: GestorProductos no está inicializado";
        // Puedes manejar este error de alguna manera específica si es necesario
    }
}


NuevoProductoForm::~NuevoProductoForm()
{
    delete ui;
}

void NuevoProductoForm::on_pushButton_released()
{
    QString SKU = ui->skuLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString description = ui->descriptionTextEdit->toPlainText();
    float sellingPrice = ui->sellingPriceSpinBox->value();
    float purchasePrice = ui->purchasePriceSpinBox->value();
    int units = ui->unitsSpinBox->value();

    if (SKU.isEmpty() || name.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Por favor, complete todos los campos."));
        return;
    }
    if (sellingPrice <= 0 || purchasePrice <= 0 || units <= 0) {
        QMessageBox::warning(this, tr("Error"), tr("Los precios y unidades deben ser mayores que cero."));
        return;
    }

    const QVector<Producto*>& productos = m_gestorProductos->obtenerProductos();
    for (const Producto* producto : productos) {
        if (producto->SKU() == SKU || producto->nombre() == name) {
            QMessageBox::warning(this, tr("Error"), tr("Ya existe un producto con el mismo nombre o SKU."));
            return;
        }
    }

    Producto *p = new Producto(SKU, name, description, sellingPrice, purchasePrice, units);

    if (m_gestorProductos) {
        m_gestorProductos->agregarProducto(*p);
        qDebug() << "Producto agregado al GestorProductos";
    } else {
        qDebug() << "Error: GestorProductos no está inicializado";
    }

    this->close();
}
