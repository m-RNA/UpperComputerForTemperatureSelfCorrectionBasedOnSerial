QT       += core gui printsupport serialport opengl multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# DEFINES += QT_NO_DEBUG_OUTPUT
DEFINES += QCUSTOMPLOT_USE_OPENGL

# OpenGl平台相关
win32 {
    LIBS+=-lopengl32 -lglu32
}
unix {
    LIBS = -lGL -lGLU -lglut
}

#如果USE_LOCAL_COMPILED_LIB = 1 ，QT+=xlsx，否则include(../xlsx/qtxlsx.pri)
DEFINES += USE_LOCAL_COMPILED_LIB=1
QT += xlsx
# INCLUDEPATH +=../xlsx
# include(../xlsx/qtxlsx.pri)

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  \
    about \
    message \
    big_float\
    wizard\
    sound \
    qcustomplot \
    least_square_method \
    collect_data \
    start_serial \
    othersetting \
    document \
    ../eigen-3.4.0

SOURCES += \
    about/about.cpp \
    collect_data/bll_data_collect.cpp \
    collect_data/bll_data_wave.cpp \
    collect_data/bll_save_data_to_xlsx.cpp \
    collect_data/collectpanel.cpp \
    config.c \
    document/help_doc.cpp \
    least_square_method/bll_leastssquare.cpp \
    least_square_method/cv_table.cpp \
    least_square_method/fitchart.cpp \
    least_square_method/rangechart.cpp \
    main.cpp \
    message/message.cpp \
    othersetting/othersetting.cpp \
    sound/bll_sound.cpp \
    start_serial/bll_codeconverter.cpp \
    start_serial/bll_serial.cpp \
    start_serial/bll_serialrecvanalyse.cpp \
    start_serial/startcommunication.cpp\
    mainwindow.cpp \
    qcustomplot/interactchart.cpp \
    qcustomplot/qcustomplot.cpp \
    wizard/serialsetting.cpp \
    wizard/wizard.cpp

HEADERS += \
    big_float/BigFloat.h \
    collect_data/bll_data_collect.h \
    collect_data/bll_data_wave.h \
    collect_data/bll_save_data_to_xlsx.h \
    config.h \
    about/about.h \
    collect_data/collectpanel.h \
    document/help_doc.h \
    least_square_method/bll_leastssquare.h \
    least_square_method/cv_table.h \
    least_square_method/fitchart.h \
    least_square_method/rangechart.h \
    mainwindow.h \
    message/message.h \
    othersetting/othersetting.h \
    qcustomplot/interactchart.h \
    qcustomplot/qcustomplot.h \
    sound/bll_sound.h \
    start_serial/bll_codeconverter.h \
    start_serial/bll_serial.h \
    start_serial/bll_serialrecvanalyse.h \
    start_serial/startcommunication.h \
    wizard/serialsetting.h \
    wizard/wizard.h

FORMS += \
    about/about.ui \
    collect_data/collectpanel.ui \
    document/help_doc.ui \
    mainwindow.ui \
    othersetting/othersetting.ui \
    start_serial/startcommunication.ui \
    wizard/serialsetting.ui \
    wizard/wizard.ui

TRANSLATIONS += \
    TemperatureSensorCalibration_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    main.qrc \
    message/Message.qrc \
    qss.qrc

RC_FILE  += \
    logo.rc
