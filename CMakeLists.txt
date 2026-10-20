cmake_minimum_required(VERSION 3.28) # plancher impose par SFML 3.1
project(GPR_CF_SBD_XX_SFML_Examples CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Les sources sont en UTF-8, MSVC ne le devine pas.
if(MSVC)
    add_compile_options(/utf-8)
endif()

# SFML est recuperee et compilee ici : rien a installer sur la machine.
# Statique (BUILD_SHARED_LIBS OFF) : aucune DLL a copier a cote des executables.
set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_NETWORK OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

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
