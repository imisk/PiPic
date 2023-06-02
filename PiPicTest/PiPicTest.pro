include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt


SOURCES += \
        main.cpp \
        test_set1.cpp \
        test_set2.cpp \
        ..\PiPicApp\utility.cpp \
        ..\PiPicApp\datamanager.cpp \
        ..\PiPicApp\bhimutils.cpp

				

HEADERS += \
  ..\PiPicApp\utility.h \
  ..\PiPicApp\datamanager.h \
  ..\PiPicApp\pipiccommon.h \
  ..\PiPicApp\bhimutils.h

	

