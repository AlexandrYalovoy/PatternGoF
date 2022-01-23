cmake_minimum_required(VERSION 3.5)

project(SBomber VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE)
set(HEADER)

list(APPEND HEADER
        include/BombDecorator.h
        include/BombIterator.h
        include/IIterator.h
        include/EvenBombIterator.h
        include/OddBombIterator.h
        include/AdapterTank.h
        include/HouseBuilder.h
        include/HouseBuilderA.h
        include/Director.h
        include/CollisionDetector.h
        include/IVisitor.h)



list(APPEND SOURCE
        src/BombDecorator.cpp
        src/BombIterator.cpp
        src/EvenBombIterator.cpp
        src/OddBombIterator.cpp
        src/AdapterTank.cpp
        src/HouseBuilder.cpp
        src/HouseBuilderA.cpp
        src/CollisionDetector.cpp
        src/IVisitor.cpp)



file(GLOB SOURCES "src/*.cpp")

include_directories(include)

set(all_code_files
        ${HEADER}
        ${SOURCE})

add_executable(${PROJECT_NAME} ${all_code_files} ${SOURCES})