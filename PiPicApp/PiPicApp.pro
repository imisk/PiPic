QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    benchmark.cpp \
    bhimUtils.cpp \
    calculator.cpp \
    core.cpp \
    dataManager.cpp \
    errorMessageBoxUtil.cpp \
    logStream.cpp \
    logger.cpp \
    main.cpp \
    mainWindow.cpp \
    utility.cpp

HEADERS += \
  bhimUtils.h \
  bigInt.h \
  bhimInteger.h \
    benchmark.h \
    calculator.h \
    core.h \
  dataManager.h \
  errorMessageBoxUtil.h \
    logStream.h \
    logger.h \
    mainWindow.h \
  piPicCommon.h \
  utility.h

FORMS += \
    mainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
