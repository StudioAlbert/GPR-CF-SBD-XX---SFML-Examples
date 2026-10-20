add_executable(AnimationClass AnimationClass.cpp Animation.cpp)
target_link_libraries(AnimationClass PRIVATE SFML::Graphics)
copy_data(AnimationClass)
