QT += core gui widgets multimedia

CONFIG += c++17
TEMPLATE = app
TARGET = PAC_MAN

# =========================================
# INCLUDE PATHS
# =========================================
INCLUDEPATH += \
    Codigo/Core \
    Codigo/UI \
    Codigo/Personajes \
    Codigo/Enemigos \
    Codigo/Objetos

# =========================================
# CORE DEL JUEGO
# =========================================
SOURCES += \
    Codigo/Core/entidad.cpp \
    Codigo/Core/juego.cpp \
    Codigo/Core/mapa.cpp

HEADERS += \
    Codigo/Core/entidad.h \
    Codigo/Core/juego.h \
    Codigo/Core/mapa.h

# =========================================
# UI / INTERFAZ
# =========================================
SOURCES += \
    Codigo/UI/mainwindow.cpp \
    main.cpp

HEADERS += \
    Codigo/UI/mainwindow.h

FORMS += \
    Codigo/UI/mainwindow.ui

# =========================================
# PERSONAJES
# =========================================
SOURCES += \
    Codigo/Personajes/pacman.cpp

HEADERS += \
    Codigo/Personajes/pacman.h

# =========================================
# ENEMIGOS
# =========================================
SOURCES += \
    Codigo/Enemigos/fantasma.cpp

HEADERS += \
    Codigo/Enemigos/fantasma.h

# =========================================
# OBJETOS
# =========================================
SOURCES += \
    Codigo/Objetos/galleta.cpp

HEADERS += \
    Codigo/Objetos/galleta.h

# =========================================
# RECURSOS
# =========================================
RESOURCES += \
    recursos.qrc

# =========================================
# INSTALACIÓN (opcional)
# =========================================
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
