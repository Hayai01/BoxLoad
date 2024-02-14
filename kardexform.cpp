#include "kardexform.h"
#include "ui_kardexform.h"
#include <QPainter>

KardexForm::KardexForm(QWidget *parent, GestorProductos *gestorProductos)
    : QWidget(parent), ui(new Ui::KardexForm), m_gestorProductos(gestorProductos)
{
    ui->setupUi(this);
    // Configuración de la tabla
    ui->historialTable->setColumnCount(7); // Establecer el número de columnas

    // Establecer los encabezados de las columnas
    QStringList headers;
    headers << "Fecha y Hora" << "SKU" << "Nombre" << "Descripción" << "Precio de Venta" << "Precio de Compra" << "Unidades";
               ui->historialTable->setHorizontalHeaderLabels(headers);

    // Ajustar el tamaño de las columnas para que se ajusten al contenido
    ui->historialTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    cargarDatos();
    connect(ui->productosComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &KardexForm::actualizarHistorial);
}
KardexForm::~KardexForm()
{
    delete ui;
}

void KardexForm::cargarDatos()
{
    // Obtener la lista de productos desde el GestorProductos
    const QList<Producto*>& productos = m_gestorProductos->obtenerProductos();

    // Agregar productos al comboBox en NuevoForm
    for (const Producto* producto : productos) {
        ui->productosComboBox->addItem(producto->nombre());
    }

}

void KardexForm::actualizarHistorial()
{
    qDebug() << "Actualizando historial...";

    // Limpiar la tabla de historial
    ui->historialTable->clearContents();
    ui->historialTable->setRowCount(0);

    // Obtener el índice del producto seleccionado
    int index = ui->productosComboBox->currentIndex();
    qDebug() << "Índice seleccionado:" << index;

        // Verificar si el índice es válido
        if (index >= 0 && index < m_gestorProductos->obtenerProductos().size()) {
        qDebug() << "Producto seleccionado válido.";

            // Obtener el historial del producto seleccionado
        QList<QPair<QDateTime, Producto>> historial = m_gestorProductos->historial(index);
        qDebug() << "Tamaño del historial:" << historial.size();
                                               qDebug() << "Historial:";

            for (const auto& registro : historial) {
                qDebug() << "Fecha y hora:" << registro.first.toString();
                qDebug() << "Producto:" << registro.second.nombre();
            }

            // Configuración de la gráfica



            for (const QPair<QDateTime, Producto>& registro : historial) {
            const Producto& producto = registro.second;
            const QDateTime& fechaHora = registro.first;

            int rowCount = ui->historialTable->rowCount();
            qDebug() << "Agregando fila:" << rowCount;

            ui->historialTable->insertRow(rowCount);

            // Añadir datos a las celdas de la fila
            QTableWidgetItem *itemFechaHora = new QTableWidgetItem(fechaHora.toString());
            QTableWidgetItem *itemSKU = new QTableWidgetItem(producto.SKU());
            QTableWidgetItem *itemNombre = new QTableWidgetItem(producto.nombre());
            QTableWidgetItem *itemDescripcion = new QTableWidgetItem(producto.descripcion());
            QTableWidgetItem *itemPrecioVenta = new QTableWidgetItem(QString::number(producto.precioVenta()));
            QTableWidgetItem *itemPrecioCompra = new QTableWidgetItem(QString::number(producto.precioCompra()));
            QTableWidgetItem *itemUnidades = new QTableWidgetItem(QString::number(producto.unidades()));

            ui->historialTable->setItem(rowCount, 0, itemFechaHora);
            ui->historialTable->setItem(rowCount, 1, itemSKU);
            ui->historialTable->setItem(rowCount, 2, itemNombre);
            ui->historialTable->setItem(rowCount, 3, itemDescripcion);
            ui->historialTable->setItem(rowCount, 4, itemPrecioVenta);
            ui->historialTable->setItem(rowCount, 5, itemPrecioCompra);
            ui->historialTable->setItem(rowCount, 6, itemUnidades);

            // Configuración de la gráfica
            int margin = 20; // Margen alrededor de la gráfica
            int availableWidth = ui->graficaWidget->width() - 2 * margin;
            int availableHeight = ui->graficaWidget->height() - 2 * margin;

            // Crear una imagen para dibujar la gráfica
            QImage grafica(ui->graficaWidget->size(), QImage::Format_RGB32);
            grafica.fill(Qt::white); // Rellenar con color blanco

            // Crear un objeto QPainter para dibujar en la imagen
            QPainter painter(&grafica);

            // Dibujar ejes x e y
            // Dibujar ejes x e y
            painter.drawLine(margin, ui->graficaWidget->height() - margin, ui->graficaWidget->width() - margin, ui->graficaWidget->height() - margin); // Eje x
            painter.drawLine(margin, margin, margin, ui->graficaWidget->height() - margin); // Eje y

            // Obtener el máximo número de unidades para establecer la escala en el eje y
            int maxUnits = 0;
            for (const QPair<QDateTime, Producto>& registro : historial) {
                maxUnits = qMax(maxUnits, registro.second.unidades());
            }

            // Calcular el ancho de las barras
            int barWidth = availableWidth / historial.size();

            // Dibujar las barras para representar el número de unidades
            for (int i = 0; i < historial.size(); ++i) {
                const QPair<QDateTime, Producto>& registro = historial[i];
                const Producto& producto = registro.second;

                // Calcular la altura de la barra en función del número de unidades
                float barHeightRatio = static_cast<float>(producto.unidades()) / maxUnits;
                int barHeight = barHeightRatio * availableHeight;

                // Calcular la posición x de la barra
                int x = margin + i * barWidth + barWidth / 4; // Ajuste para centrar la barra

                // Calcular la posición y de la barra
                int y = ui->graficaWidget->height() - margin - barHeight;

                // Dibujar la barra
                painter.fillRect(x, y, barWidth / 2, barHeight, Qt::blue); // Cambiar el color si lo deseas

                // Dibujar la fecha debajo de la barra
                QString fecha = registro.first.date().toString("dd/MM/yyyy");
                painter.drawText(x, ui->graficaWidget->height() - margin + 15, fecha);
            }

            // Dibujar las etiquetas en el eje y
            for (int i = 0; i <= 5; ++i) { // Ajustar el número de etiquetas según sea necesario
                int y = ui->graficaWidget->height() - margin - i * availableHeight / 5;
                painter.drawText(margin - 15, y + 5, QString::number(i * maxUnits / 5)); // Etiquetas en el eje y
            }

            // Mostrar la imagen en el widget de la gráfica
            ui->graficaWidget->setPixmap(QPixmap::fromImage(grafica));
            }

    } else {
        qDebug() << "Índice seleccionado inválido.";
    }
}
