cmake_minimum_required(VERSION 3.6)
project(VectorTD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/libconfig/libconfig.h
    include/GL/glut.h
        include/ControlEngine.h
    include/Engine.h
    include/GameEngine.h
    include/GraphicEngine.h
    include/GraphicPrimitives.h
    include/libGraphicInclude.h
    include/Stopwatch.h
    src/MonsterAbstract.cpp
    src/MonsterAbstract.h
    src/Case.cpp
    src/Case.h
    src/main.cpp
    src/MyControlEngine.cpp
    src/MyControlEngine.h
    src/MyGameEngine.cpp
    src/MyGameEngine.h
    src/MyGraphicEngine.cpp
    src/MyGraphicEngine.h
    src/Shoot.cpp
    src/Shoot.h
    src/TowerRed.cpp
    src/TowerRed.h src/Game.cpp src/Game.h src/TowerAbstract.cpp src/TowerAbstract.h src/TowerGreen.cpp src/TowerGreen.h src/TowerBlue.cpp src/TowerBlue.h src/MonsterRed.cpp src/MonsterRed.h src/MonsterGreen.cpp src/MonsterGreen.h src/MonsterYellow.cpp src/MonsterYellow.h src/MonsterPurple.cpp src/MonsterPurple.h src/Button.cpp src/Button.h src/config.cfg)

include_directories(include)

add_executable(VectorTD ${SOURCE_FILES})