#include "pantallaprincipal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PantallaPrincipal w;
    w.show();
    return a.exec();
}
