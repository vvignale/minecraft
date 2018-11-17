QT += core gui opengl

TARGET = warmup
TEMPLATE = app

# If you add your own folders, add them to INCLUDEPATH and DEPENDPATH, e.g.
# INCLUDEPATH += folder1 folder2
# DEPENDPATH += folder1 folder2

INCLUDEPATH += src
DEPENDPATH += src

#LIBS += -lglut -lGLU

SOURCES +=  src/common_engine/camera.cpp \
    src/common_engine/player.cpp \
    src/common_engine/application.cpp \
    src/common_engine/screen.cpp \
    src/common_engine/graphics.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/view.cpp \
    src/common_engine/entity.cpp \
    src/common_engine/world.cpp \
    src/common_engine/shape.cpp \
    src/common_engine/cylinder.cpp \
    src/common_engine/range.cpp \
    src/common_engine/physicsentity.cpp \
    src/common_engine/staticphysicsentity.cpp \
    src/game/minecraftapp.cpp \
    src/game/minecraftmainmenu.cpp \
    src/game/minecraftgamescreen.cpp \
    src/game/minecraftworld.cpp \
    src/voxel_engine/chunk.cpp \
    src/voxel_engine/voxel.cpp \
    src/game/minecraftgrassvoxel.cpp \
    src/game/minecraftchunk.cpp \
    src/common_engine/noisegenerator.cpp \
    src/voxel_engine/voxelmanager.cpp \
    src/game/minecraftvoxelmanager.cpp \
    src/game/minecraftglassvoxel.cpp \
    src/game/minecrafticevoxel.cpp \
    src/common_engine/aab.cpp \
    src/common_engine/ray.cpp \
    src/game/minecraftcow.cpp \
    src/game/minecraftreedvoxel.cpp \
    src/game/minecraftgoal.cpp \
    src/game/minecraftendscreen.cpp \
    src/common_engine/perlinnoise.cpp \
    src/common_engine/resourceloader.cpp \
    src/game/minecraftbarkvoxel.cpp \
    src/game/minecraftleafvoxel.cpp \
    src/game/minecraftwatervoxel.cpp \
    src/game/minecraftflowervoxel.cpp \
    src/game/minecrafttallgrassvoxel.cpp \
    src/game/minecraftlightbarkvoxel.cpp \
    src/game/minecraftopaqueleafvoxel.cpp



HEADERS +=  src/common_engine/camera.h \
    src/common_engine/player.h \
    src/common_engine/application.h \
    src/common_engine/screen.h \
    src/common_engine/graphics.h \
    src/mainwindow.h \
    src/main.h \
    src/common_engine/vector.h \
    src/view.h \
    src/common_engine/entity.h \
    src/common_engine/world.h \
    src/common_engine/shape.h \
    src/common_engine/cylinder.h \
    src/common_engine/range.h \
    src/common_engine/physicsentity.h \
    src/common_engine/staticphysicsentity.h \
    src/game/minecraftapp.h \
    src/game/minecraftmainmenu.h \
    src/game/minecraftgamescreen.h \
    src/game/minecraftworld.h \
    src/voxel_engine/chunk.h \
    src/voxel_engine/voxel.h \
    src/game/minecraftgrassvoxel.h \
    src/game/minecraftchunk.h \
    src/common_engine/noisegenerator.h \
    src/voxel_engine/voxelmanager.h \
    src/game/minecraftvoxelmanager.h \
    src/game/minecraftglassvoxel.h \
    src/game/minecrafticevoxel.h \
    src/common_engine/aab.h \
    src/common_engine/ray.h \
    src/game/minecraftcow.h \
    src/game/minecraftreedvoxel.h \
    src/game/minecraftgoal.h \
    src/game/minecraftendscreen.h \
    src/common_engine/perlinnoise.h \
    src/common_engine/resourceloader.h \
    src/common_engine/glm.h \
    src/game/minecraftbarkvoxel.h \
    src/game/minecraftleafvoxel.h \
    src/game/minecraftwatervoxel.h \
    src/game/minecraftflowervoxel.h \
    src/game/minecrafttallgrassvoxel.h \
    src/game/minecraftlightbarkvoxel.h \
    src/game/minecraftopaqueleafvoxel.h

FORMS += src/mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    fog.vert \
    fog.vert \
    fog.frag
