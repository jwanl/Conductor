cd ../emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ../Conductor

emcc -o target/conductor.html \
    Conductor/main.cpp \
    Conductor/gamestate.cpp \
    Conductor/graphics.cpp \
    Conductor/highscore.cpp \
    Conductor/level.cpp \
    Conductor/musicplayer.cpp \
    Conductor/track.cpp \
    -Wall -std=c++14 ./../raylib/src/libraylib.a \
    -I. -I ./../raylib/src \
    -L. -L ./../raylib/src -s USE_GLFW=3 \
    -s ASYNCIFY \
    -s TOTAL_MEMORY=67108864 \
    -s FORCE_FILESYSTEM=1 --preload-file resources \
    --shell-file ./shell.html \
    -DPLATFORM_WEB 

