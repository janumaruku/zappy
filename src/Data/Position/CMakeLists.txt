add_library(position Position.cpp)

target_include_directories(position PUBLIC include)

target_link_libraries(position PUBLIC warning_options)