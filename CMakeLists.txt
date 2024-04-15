cmake_minimum_required(VERSION 3.10)

project(Game)

add_subdirectory(Game/Vendor/GLFW/)

file(GLOB Game_SRC
     "Game/src/*.h"
     "Game/src/*.cpp"

)

add_library(GLAD STATIC Game/Vendor/GLAD/src/glad.c)
target_include_directories(GLAD PRIVATE ${CMAKE_CURRENT_SOURCE_DIR/}Game/Vendor/GLAD/include)

add_executable(Game ${Game_SRC})
target_include_directories(Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR/}Game/Vendor/GLAD/include)
target_link_libraries(Game glfw)
target_link_libraries(Game GLAD)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)