add_executable(Events-c Events-c.cpp)
target_link_libraries(Events-c PRIVATE SFML::Graphics)
copy_data(Events-c)
