add_executable(Views Views.cpp)
target_link_libraries(Views PRIVATE SFML::Graphics)
copy_data(Views)
