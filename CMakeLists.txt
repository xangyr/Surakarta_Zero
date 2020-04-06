cmake_minimum_required(VERSION 3.15)
project(Surakarta_Zero)

set(CMAKE_CXX_STANDARD 14)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)

add_executable(Surakarta_Zero_New main.cpp ui.cpp ui.h chessboard.cpp chessboard.h ArrayList.cpp ArrayList.h basic.h basic.cpp search_engine.cpp move_generator.cpp evaluator.cpp test.cpp test.h)

target_link_libraries(Surakarta_Zero_New ${SDL2_IMAGE_LIBRARY} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})