#ifndef NUEVOFORM_H
#define NUEVOFORM_H

#include <QWidget>
#include "gestorproductos.h"

namespace Ui {
class NuevoForm;
}

class NuevoForm : public QWidget
{
    Q_OBJECT

public:
    explicit NuevoForm(QWidget *parent = nullptr, GestorProductos *gestorProductos = nullptr);
    ~NuevoForm();

private slots:
    void on_anadirButton_released();

private:
    Ui::NuevoForm *ui;
    GestorProductos *m_gestorProductos;
    void cargarDatos();


};

#endif // NUEVOFORM_H
