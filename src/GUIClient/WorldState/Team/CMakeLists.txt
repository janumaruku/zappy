add_library(team STATIC Team.cpp)

target_include_directories(team PUBLIC include)

target_link_libraries(team PUBLIC warning_options)
