QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp\
    rvairplane.cpp \
    rvbb8.cpp \
    rvbody.cpp \
    rvbounce.cpp \
    rvcamera.cpp \
    rvcube.cpp \
    rvcurve.cpp \
    rvdice.cpp \
    rvhelix.cpp \
    rvlight.cpp \
    rvmesh.cpp \
    rvmodel.cpp \
    rvplane.cpp \
    rvplanet.cpp \
    rvpyramid.cpp \
    rvscene.cpp \
    rvskybox.cpp \
    rvspecularcube.cpp \
    rvspecularsphere.cpp \
    rvspeculartorus.cpp \
    rvsphere.cpp \
    rvsphericalcamera.cpp \
    rvstereocamera.cpp \
    rvsubjectivecamera.cpp \
    rvsurface.cpp \
    rvterrain.cpp \
    rvtexcube.cpp \
    rvtorus.cpp \
    rvwidget.cpp

HEADERS += \
    mainwindow.h\
    rvairplane.h \
    rvbb8.h \
    rvbody.h \
    rvbounce.h \
    rvcamera.h \
    rvcube.h \
    rvcurve.h \
    rvdice.h \
    rvhelix.h \
    rvlight.h \
    rvmesh.h \
    rvmodel.h \
    rvplane.h \
    rvplanet.h \
    rvpyramid.h \
    rvscene.h \
    rvskybox.h \
    rvspecularcube.h \
    rvspecularsphere.h \
    rvspeculartorus.h \
    rvsphere.h \
    rvsphericalcamera.h \
    rvstereocamera.h \
    rvsubjectivecamera.h \
    rvsurface.h \
    rvterrain.h \
    rvtexcube.h \
    rvtorus.h \
    rvwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


windows:LIBS += -lopengl32

DISTFILES += \
    2k_earth_daymap.jpg \
    2k_earth_nightmap.jpg \
    FS_checker_texture.fsh \
    FS_plan.fsh \
    FS_plan_texture.fsh \
    FS_planet_texture.fsh \
    FS_simple.fsh \
    FS_simple_texture.fsh \
    VS_simple.vsh \
    VS_simple_texture.vsh \
    VS_simpler.vsh \
    wood.png

RESOURCES += \
    RVResources.qrc \
    RVResources.qrc

FORMS += \
    mainwindow.ui





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../assimp/lib/ -lassimp-vc143-mt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../assimp/lib/ -lassimp-vc143-mtd

INCLUDEPATH += $$PWD/../../assimp/include
DEPENDPATH += $$PWD/../../assimp/include
