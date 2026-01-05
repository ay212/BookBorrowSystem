QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminmainview.cpp \
    bookeditview.cpp \
    bookmanageview.cpp \
    bookqueryview.cpp \
    borrowreturnview.cpp \
    loginview.cpp \
    main.cpp \
    masterview.cpp \
    personalborrowview.cpp \
    readereditview.cpp \
    readermainview.cpp \
    readermanageview.cpp \
    statview.cpp

HEADERS += \
    adminmainview.h \
    bookeditview.h \
    bookmanageview.h \
    bookqueryview.h \
    borrowreturnview.h \
    loginview.h \
    masterview.h \
    personalborrowview.h \
    readereditview.h \
    readermainview.h \
    readermanageview.h \
    statview.h

FORMS += \
    adminmainview.ui \
    bookeditview.ui \
    bookmanageview.ui \
    bookqueryview.ui \
    borrowreturnview.ui \
    loginview.ui \
    masterview.ui \
    personalborrowview.ui \
    readereditview.ui \
    readermainview.ui \
    readermanageview.ui \
    statview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
