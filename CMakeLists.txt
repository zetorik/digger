cmake_minimum_required(VERSION 3.10)

project(Digger VERSION 1.0 LANGUAGES CXX)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

add_executable(Digger main.cpp scr/game.cpp scr/input_manager.cpp scr/player.cpp scr/sprite_renderer.cpp scr/utils.cpp scr/rock.cpp scr/transform.cpp scr/collision.cpp scr/collision_manager.cpp scr/explosion.cpp scr/texture_manager.cpp scr/ore.cpp scr/audio_manager.cpp scr/sound.cpp scr/health_bar.cpp)

target_link_libraries(Digger PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)

target_compile_features(Digger PRIVATE cxx_std_20)

file(COPY ${CMAKE_SOURCE_DIR}/assets/
     DESTINATION ${CMAKE_BINARY_DIR}/assets/)
