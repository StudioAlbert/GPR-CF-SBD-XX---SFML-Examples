add_executable(Animation Animation.cpp)
target_link_libraries(Animation PRIVATE SFML::Graphics)
copy_data(Animation)
