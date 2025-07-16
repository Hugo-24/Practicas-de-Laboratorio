QT += core gui widgets

CONFIG += c++17

TEMPLATE = app
TARGET = SimulacionGravitacional

INCLUDEPATH += Encabezados \
Fuentes

SOURCES += \
    main.cpp \
    Fuentes/cuerpo.cpp \
    Fuentes/ventana_principal.cpp

HEADERS += \
    Encabezados/cuerpo.h \
    Encabezados/ventana_principal.h

FORMS += \
    Interfaz/ventana_principal.ui
