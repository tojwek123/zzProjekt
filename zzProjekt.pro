#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T19:53:21
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = zzProjekt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    ui/loginwindow.cpp \
    ui/mainwindow.cpp \
    ui/racerview.cpp \
    backend/dbconnection.cpp \
    backend/timetablewidgetitem.cpp \
    backend/datetimetablewidgetitem.cpp \
    ui/planracedialog.cpp \
    backend/specificdatescalendar.cpp \
    backend/qcustomplot/qcustomplot.cpp \
    ui/personaltimesplot.cpp \
    ui/profilesettings.cpp \
    ui/adminview.cpp

HEADERS  += \
    ui/loginwindow.h \
    ui/mainwindow.h \
    ui/racerview.h \
    backend/dbconnection.h \
    backend/timetablewidgetitem.h \
    backend/datetimetablewidgetitem.h \
    ui/planracedialog.h \
    backend/specificdatescalendar.h \
    backend/qcustomplot/qcustomplot.h \
    ui/personaltimesplot.h \
    ui/profilesettings.h \
    ui/adminview.h

FORMS    += \
    ui/loginwindow.ui \
    ui/mainwindow.ui \
    ui/racerview.ui \
    ui/planracedialog.ui \
    ui/personaltimesplot.ui \
    ui/profilesettings.ui \
    ui/adminview.ui
