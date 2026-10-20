add_executable(Sound src/main.cpp)
target_link_libraries(Sound PRIVATE SFML::Graphics SFML::Audio)
copy_data(Sound)
