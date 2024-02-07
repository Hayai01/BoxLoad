#include "nuevoproductoform.h"
#include "ui_nuevoproductoform.h"

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
    float sellingPrice = ui->sellingPriceLineEdit->text().toFloat();
    float purchasePrice = ui->purchaseLineEdit->text().toFloat();
    int units = ui->unitsLineEdit->text().toInt();

    Producto *p = new Producto(SKU, name, description, sellingPrice, purchasePrice, units);

    if (m_gestorProductos) {
        m_gestorProductos->agregarProducto(*p);
        qDebug() << "Producto agregado al GestorProductos";
    } else {
        qDebug() << "Error: GestorProductos no está inicializado";
    }


    this->close();
}

