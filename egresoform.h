#ifndef EGRESOFORM_H
#define EGRESOFORM_H

#include <QWidget>
#include "gestorproductos.h"

namespace Ui {
class EgresoForm;
}

class EgresoForm : public QWidget
{
    Q_OBJECT

public:
    explicit EgresoForm(QWidget *parent = nullptr,GestorProductos *gestorProductos = nullptr);
    ~EgresoForm();

private slots:

    void on_eliminarButton_released();

private:
    Ui::EgresoForm *ui;
    GestorProductos *m_gestorProductos;
    void cargarDatos();
};

#endif // EGRESOFORM_H
