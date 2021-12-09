QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        iconlabelcontainer.cpp \
        playlistcontainer.cpp \
        playlistswindow.cpp \
        scrollgridlayout.cpp \
        sidebar.cpp \
        the_button.cpp \
        the_player.cpp \
        scroll_layout.cpp \
        scroll_window.cpp \
        video_scroll.cpp \
        tomeo.cpp

HEADERS += \
    constants.h \
    iconlabelcontainer.h \
    playlistcontainer.h \
    playlistswindow.h \
    scrollgridlayout.h \
    sidebar.h \
    the_button.h \
    scroll_layout.h \
    scroll_window.h \
    video_scroll.h \
    the_player.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    buttons/add.png \
    buttons/dragDrop.png \
    buttons/fForward.png \
    buttons/pause.png \
    buttons/play.png \
    buttons/reload.png \
    buttons/sDown.png \
    buttons/stop.png

RESOURCES += \
    images.qrc

