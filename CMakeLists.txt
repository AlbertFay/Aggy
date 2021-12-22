cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

if (WIN32)
    set(CXX_FLAGS "-Wall -Wextra")
elseif (UNIX)
    set(CXX_FLAGS "-Wall -pthread")
endif()
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

MESSAGE( STATUS "Config flags : " ${CXX_FLAGS})

project(SDL2_Wizard_Demo CXX)

if (WIN32)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/windows/")
elseif (UNIX)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/linux/")
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} src)

add_executable(wizard_demo src/main.cpp src/controller.cpp src/game.cpp src/renderer.cpp src/character.cpp src/shotfired.cpp src/resource-manager.cpp src/gamemap.cpp src/collision-manager.cpp src/ghost.cpp src/level.cpp)
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
target_link_libraries(wizard_demo ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
add_definitions(-DSDL_MAIN_HANDLED)
