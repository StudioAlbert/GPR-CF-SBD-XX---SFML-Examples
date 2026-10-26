cmake_minimum_required(VERSION 3.28) # plancher impose par SFML 3.1
project(GPR_CF_SBD_XX_SFML_Examples CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Les sources sont en UTF-8, MSVC ne le devine pas.
if(MSVC)
    add_compile_options(/utf-8)
endif()

# SFML vient de vcpkg, comme dans les projets des etudiants : `vcpkg.json` dit ce
# qu'il faut, et vcpkg l'installe au moment de la configuration. Les DLL sont
# recopiees a cote des executables par vcpkg lui-meme, il n'y a rien a faire.
#
# Il faut la toolchain vcpkg. CLion la met en place depuis son panneau Vcpkg ;
# en ligne de commande :
#   cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
find_package(SFML 3 COMPONENTS Graphics Audio System REQUIRED)

# Copie le dossier data/ de la cible a cote de son executable.
# Sans ca, les chemins relatifs du code ne trouvent rien a l'execution.
function(copy_data target)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:${target}>/data")
endfunction()

add_subdirectory(Animation)
add_subdirectory(AnimationClass)
add_subdirectory(Audio)
add_subdirectory(ConstMethods)
add_subdirectory(Events-a)
add_subdirectory(Events-b)
add_subdirectory(Events-c)
add_subdirectory(Events-d)
add_subdirectory(Graphics)
add_subdirectory(HelloWorld)
add_subdirectory(LevelEditor/01_basic_tilemap_editor)
add_subdirectory(LevelEditor/02_player_movement)
add_subdirectory(LevelEditor/03_save_load)
add_subdirectory(Motor)
add_subdirectory(MoveAndJump)
add_subdirectory(OOPHero)
add_subdirectory(Sound)
add_subdirectory(TimeClock)
add_subdirectory(Views)
