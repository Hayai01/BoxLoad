#ifndef PANTALLAPRINCIPAL_H
#define PANTALLAPRINCIPAL_H

#include <QMainWindow>
#include "nuevoproductoform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PantallaPrincipal; }
QT_END_NAMESPACE

class PantallaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    PantallaPrincipal(QWidget *parent = nullptr);
    ~PantallaPrincipal();

private slots:
    void on_action_Nuevo_Producto_triggered();

    void on_action_Salir_triggered();

    void on_action_Ingreso_triggered();

    void on_action_Egreso_triggered();

    void on_actionKardex_triggered();

private:
    Ui::PantallaPrincipal *ui;
    GestorProductos *m_gestorProductos;
};
#endif // PANTALLAPRINCIPAL_H
