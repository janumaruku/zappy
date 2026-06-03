add_library(utils STATIC Logger.cpp
        OptionException.cpp
        Options.cpp
        StringUtils.cpp)

target_include_directories(utils PUBLIC include)

target_link_libraries(utils PUBLIC design_pattern warning_options)
