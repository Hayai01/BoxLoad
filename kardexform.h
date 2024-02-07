#ifndef KARDEXFORM_H
#define KARDEXFORM_H

#include <QWidget>
#include "gestorproductos.h"

namespace Ui {
class KardexForm;
}

class KardexForm : public QWidget
{
    Q_OBJECT

public:
    explicit KardexForm(QWidget *parent = nullptr, GestorProductos *gestorProductos = nullptr);
    ~KardexForm();
    void actualizarHistorial();

private:
    Ui::KardexForm *ui;
    GestorProductos *m_gestorProductos;
    void cargarDatos();

};

#endif // KARDEXFORM_H
