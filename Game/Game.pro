TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    gameview.cpp \
    graphicsItem/aircrew.cpp \
    graphicsItem/backgrounditem.cpp \
    graphicsItem/bank.cpp \
    graphicsItem/cleaner.cpp \
    graphicsItem/enemy.cpp \
    graphicsItem/hiteffect.cpp \
    graphicsItem/hospitalgate.cpp \
    graphicsItem/penguin.cpp \
    graphicsItem/player.cpp \
    graphicsItem/questlight.cpp \
    graphicsItem/sceneitem.cpp \
    graphicsItem/teacher.cpp \
    graphicsItem/train.cpp \
    graphicsItem/tutor.cpp \
    window/login.cpp \
    main.cc \
    map/airportmap.cpp \
    map/basemap.cpp \
    map/citymap.cpp \
    map/hospitalmap.cpp \
    map/universitymap.cpp \
    scene/airportscene.cpp \
    scene/basicscene.cpp \
    scene/cityscene.cpp \
    scene/endscene.cpp \
    scene/hospitalscene.cpp \
    scene/startscene.cpp \
    scene/tamperescene.cpp \
    scene/universityscene.cpp \
    window/buswindow.cpp \
    window/talkwindow.cpp

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    window/login.ui \
    window/buswindow.ui \
    window/talkwindow.ui

HEADERS += \
    Constants.hh \
    gameview.hh \
    graphicsItem/aircrew.hh \
    graphicsItem/backgrounditem.hh \
    graphicsItem/bank.hh \
    graphicsItem/cleaner.hh \
    graphicsItem/enemy.hh \
    graphicsItem/hiteffect.hh \
    graphicsItem/hospitalgate.hh \
    graphicsItem/penguin.hh \
    graphicsItem/player.hh \
    graphicsItem/questlight.hh \
    graphicsItem/sceneitem.hh \
    graphicsItem/teacher.hh \
    graphicsItem/train.hh \
    graphicsItem/tutor.hh \
    window/login.hh \
    map/airportmap.hh \
    map/basemap.hh \
    map/citymap.hh \
    map/hospitalmap.hh \
    map/universitymap.hh \
    scene/airportscene.hh \
    scene/basicscene.hh \
    scene/cityscene.hh \
    scene/endscene.hh \
    scene/hospitalscene.hh \
    scene/startscene.hh \
    scene/tamperescene.hh \
    scene/universityscene.hh \
    window/buswindow.hh \
    window/talkwindow.hh

RESOURCES += \
    animation.qrc \
    background.qrc \
    map.qrc \
    music.qrc \
    penguin.qrc

DISTFILES +=
