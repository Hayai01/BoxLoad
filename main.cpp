#include "pantallaprincipal.h"
#include <QTranslator>
#include <QApplication>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator traduccion;
    QStringList idiomas;
    idiomas << "Spanish" <<"German"<<"French";

    QString idiomaSeleccionado = QInputDialog::getItem(NULL,
                                                       "language",
                                                       "Select an Lenguage",
                                                       idiomas);
    if(idiomaSeleccionado == "German"){
        if(traduccion.load(":/BoxLoad_de.qm")) {
            qApp->installTranslator(&traduccion);
        } else {
            qDebug() << "Error al cargar la traducción alemana.";
        }
    }

    if(idiomaSeleccionado == "French"){
        if(traduccion.load(":/BoxLoad_fr.qm")) {
            qApp->installTranslator(&traduccion);
        } else {
            qDebug() << "Error al cargar la traducción francesa.";
        }
    }
    if(idiomaSeleccionado != "Spanish"){
        a.installTranslator(&traduccion);
    }

    PantallaPrincipal w;
    w.show();
    return a.exec();
}
