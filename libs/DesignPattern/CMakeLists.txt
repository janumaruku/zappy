add_library(design_pattern STATIC
    FactoryTemplate.cpp
    AObserver.cpp
    ASubject.cpp
)

target_include_directories(design_pattern PUBLIC include)

target_link_libraries(design_pattern PUBLIC warning_options)
