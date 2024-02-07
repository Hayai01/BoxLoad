#ifndef NUEVOPRODUCTOFORM_H
#define NUEVOPRODUCTOFORM_H

#include <QWidget>
#include "gestorproductos.h"

namespace Ui {
class NuevoProductoForm;
}

class NuevoProductoForm : public QWidget
{
    Q_OBJECT

public:
    explicit NuevoProductoForm(QWidget *parent = nullptr, GestorProductos *gestorProductos = nullptr);
    ~NuevoProductoForm();

private slots:
    void on_pushButton_released();

private:
    Ui::NuevoProductoForm *ui;
    GestorProductos *m_gestorProductos;
};

#endif // NUEVOPRODUCTOFORM_H
