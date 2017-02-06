QT += qml quick quickcontrols2 widgets

CONFIG += c++11

QMAKE_LFLAGS += -Wl,--large-address-aware

SOURCES += main.cpp \
    filecsv.cpp \
    loading.cpp \
    data.cpp \
    treatment.cpp \
    treeitem.cpp \
    treemodel.cpp \
    datacommu.cpp \
    datadocument.cpp \
    datadomaine.cpp \
    datadomaines.cpp \
    datagoal.cpp \
    datanote.cpp \
    datauser.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    filecsv.h \
    loading.h \
    data.h \
    treatment.h \
    treeitem.h \
    treemodel.h \
    datacommu.h \
    datadocument.h \
    datadomaine.h \
    datadomaines.h \
    datagoal.h \
    datanote.h \
    datauser.h

DISTFILES += \
    config.json
