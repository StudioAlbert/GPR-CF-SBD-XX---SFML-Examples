add_executable(OOPHero main.cpp player.cpp)
target_link_libraries(OOPHero PRIVATE SFML::Graphics)
copy_data(OOPHero)
