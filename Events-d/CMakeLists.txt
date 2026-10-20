add_executable(Events-d Events-d.cpp)
target_link_libraries(Events-d PRIVATE SFML::Graphics)
copy_data(Events-d)
