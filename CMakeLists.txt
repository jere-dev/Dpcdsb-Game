cmake_minimum_required(VERSION 3.10)

project(Game)

add_subdirectory(Game/Vendor/GLFW/)
add_subdirectory(Game/Vendor/flecs/)

file(GLOB Game_SRC
     "Game/src/*.h"
     "Game/src/*.cpp"

)

file(GLOB box2d_INCLUDE
     "Game/Vendor/box2d/include/box2d/*.h"
)


file(GLOB box2d_SRC
     "Game/Vendor/box2d/src/collision/*.cpp"
     "Game/vendor/box2d/src/common/*.cpp"
     "Game/vendor/box2d/src/dynamics/*.cpp"
     "Game/vendor/box2d/src/rope/*.cpp"
)


add_library(GLAD STATIC Game/Vendor/GLAD/src/glad.c)
target_include_directories(GLAD PRIVATE ${CMAKE_CURRENT_SOURCE_DIR/}Game/Vendor/GLAD/include)

add_library(box2d STATIC ${box2d_SRC} ${box2d_INCLUDE})
target_include_directories(box2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR/}Game/Vendor/box2d/include)

add_executable(Game ${Game_SRC})

target_include_directories(Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR/}Game/Vendor/GLAD/include)
target_include_directories(Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR/}Game/Vendor/flecs/include)
target_include_directories(Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR/}Game/Vendor/glm)
target_include_directories(Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR/}Game/Vendor/box2d/include)

target_link_libraries(Game glfw)
target_link_libraries(Game GLAD)
target_link_libraries(Game flecs::flecs_static)
target_link_libraries(Game box2d)


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)