cmake_minimum_required(VERSION 3.10)
project(TectrisC C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories(
    include
    C:/raylib/raylib/src
)
set(SOURCES
    src/main.c
    src/game/game.c
    src/game/questions.c
    src/game/questions_modo_easy.c
    src/render/render.c
    src/utils/history.c
    src/utils/stats.c
)
add_executable(Tectris ${SOURCES})
target_link_libraries(Tectris
    C:/raylib/raylib/src/libraylib.a
    winmm
    gdi32
    opengl32
)