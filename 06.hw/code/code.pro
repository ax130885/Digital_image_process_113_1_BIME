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

# 預設部署規則
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 根據建置模式（debug/release）設定 OpenCV 庫
win32:CONFIG(release, debug|release): LIBS += -LC:\opencv\mybuild\install\x64\vc17\lib -lopencv_world4100
else:win32:CONFIG(debug, debug|release): LIBS += -LC:\opencv\mybuild\install\x64\vc17\lib -lopencv_world4100d

# 添加 DLL 路徑，確保執行時能找到
win32:CONFIG(release, debug|release): LIBS += -LC:\opencv\mybuild\install\x64\vc17\bin
else:win32:CONFIG(debug, debug|release): LIBS += -LC:\opencv\mybuild\install\x64\vc17\bin

# 包含 OpenCV 的標頭檔
INCLUDEPATH += C:\opencv\build\include C:\opencv\mybuild\include
DEPENDPATH += C:\opencv\build\include C:\opencv\mybuild\include
