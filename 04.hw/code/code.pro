QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    generalprocess.cpp \
    main.cpp \
    mainwindow.cpp \
    specificprocess.cpp

HEADERS += \
    generalprocess.h \
    mainwindow.h \
    specificprocess.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LC:\opencv\build\x64\vc16\lib -lopencv_world4100
else:win32:CONFIG(debug, debug|release): LIBS += -LC:\opencv\build\x64\vc16\lib -lopencv_world4100d
win32:CONFIG(release, debug|release): LIBS += -LC:\opencv\build\x64\vc16\bin -lopencv_world4100
else:win32:CONFIG(debug, debug|release): LIBS += -LC:\opencv\build\x64\vc16\bin -lopencv_world4100d
INCLUDEPATH += C:\opencv\build\include
DEPENDPATH += C:\opencv\build\include
