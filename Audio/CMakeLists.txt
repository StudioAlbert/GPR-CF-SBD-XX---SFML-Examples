add_executable(Audio src/main.cpp)
target_link_libraries(Audio PRIVATE SFML::Graphics SFML::Audio)
copy_data(Audio)
