cmake_minimum_required(VERSION 3.20)
project(game)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-std=c++17 -g -Wall -Wextra)

find_package(SDL2 REQUIRED)
# find_library(SDL2_LIBRARIES NAMES libSDL2 libSDL2.so libSDL2.a libSDL2.dylib)

add_library(gamelib graphics.cpp player.cpp world.cpp)
target_include_directories(gamelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDES})
target_link_libraries(gamelib PUBLIC SDL2::SDL2)

# set(SDL2_INCLUDES "C:/Users/josep/VScode/GameDev/SDL-SDL2/SDL-SDL2/include")
# set(SDL2_LIBRARIES "C:/Users/josep/VScode/GameDev/SDL-SDL2/SDL-SDL2/build/SDL2d.dll")

add_executable(main main.cpp)
target_link_libraries(main PUBLIC gamelib)

add_executable(test1 test1.cpp)
target_link_libraries(test1 PUBLIC gamelib)