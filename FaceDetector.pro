TEMPLATE = app
CONFIG += gui c++17
CONFIG -= app_bundle
CONFIG += qt
QT += gui \
    widgets

SOURCES += \
        main.cpp \
        mainwindow.cpp

TARGET = camera

INCLUDEPATH += /usr/include/opencv4
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_imgproc
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_videoio
LIBS += -lopencv_video
LIBS += -lopencv_objdetect


# Default rules for deployment.
target.path = /home/adam/camera
INSTALLS += target

HEADERS += \
    asmOpenCv.h \
    mainwindow.h

RESOURCES +=
