cmake_minimum_required(VERSION 3.5)

project(SBomber VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE)
set(HEADER)

list(APPEND HEADER
        include/enums/ConsoleColors.h
        include/enums/CraterSize.h
        include/Bomb.h
        include/Crater.h
        include/DestroyableGroundObject.h
        include/DynamicObject.h
        include/GameObject.h
        include/Ground.h
        include/House.h
        include/LevelGUI.h
        include/MyTools.h
        include/Plane.h
        include/SBomber.h
        include/ScreenSingleton.h
        include/Tank.h)




list(APPEND SOURCE
        src/Bomb.cpp
        src/Crater.cpp
        src/Ground.cpp
        src/House.cpp
        src/LevelGUI.cpp
        src/main.cpp
        src/MyTools.cpp
        src/Plane.cpp
        src/SBomber.cpp
        src/ScreenSingleton.cpp
        src/Tank.cpp)



file(GLOB SOURCES "src/*.cpp")

include_directories(include)

set(all_code_files
        ${HEADER}
        ${SOURCE})

add_executable(${PROJECT_NAME} ${all_code_files} ${SOURCES})