add_library(design_pattern STATIC FactoryTemplate.cpp
        include/IObserver.hpp
        include/ISubject.hpp
        include/ASubject.cpp
        include/ASubject.hpp
        include/AObserver.cpp
        include/AObserver.hpp)

target_include_directories(design_pattern PUBLIC include)

target_link_libraries(design_pattern PUBLIC warning_options)
