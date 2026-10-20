add_executable(Graphics Graphics.cpp)
target_link_libraries(Graphics PRIVATE SFML::Graphics)
copy_data(Graphics)
