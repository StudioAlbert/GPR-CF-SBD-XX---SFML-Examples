add_executable(Motor
        main.cpp
        motor.cc
        auto_entity.cc
        enemy.cc
        projectile.cc
        entity_manager.cc
        starship_player.cc)
target_link_libraries(Motor PRIVATE SFML::Graphics)
copy_data(Motor)
