#ifndef PEDIDOSPENDIENTESFORM_H
#define PEDIDOSPENDIENTESFORM_H

#include <QWidget>
#include "gestorproductos.h"

namespace Ui {
class PedidosPendientesForm;
}

class PedidosPendientesForm : public QWidget
{
    Q_OBJECT


struct Pedido {
    QString producto;
    int unidades;
    float costo;
};

public:
    explicit PedidosPendientesForm(QWidget *parent = nullptr,GestorProductos *gestorProductos = nullptr);
    ~PedidosPendientesForm();
    void cargarDatos();
    void actualizarCostoPedido(int index);
private slots:
    void on_pushButton_released();

private:
    Ui::PedidosPendientesForm *ui;
    QVector<Pedido> pedidosPendientes;
    GestorProductos *m_gestorProductos;
};

#endif // PEDIDOSPENDIENTESFORM_H
