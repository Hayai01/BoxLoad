QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    egresoform.cpp \
    gestorproductos.cpp \
    kardexform.cpp \
    main.cpp \
    nuevoform.cpp \
    nuevoproductoform.cpp \
    pantallaprincipal.cpp \
    producto.cpp

HEADERS += \
    egresoform.h \
    gestorproductos.h \
    kardexform.h \
    nuevoform.h \
    nuevoproductoform.h \
    pantallaprincipal.h \
    producto.h

FORMS += \
    egresoform.ui \
    kardexform.ui \
    nuevoform.ui \
    nuevoproductoform.ui \
    pantallaprincipal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagenes.qrc
