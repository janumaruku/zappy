add_executable(zappy_server
    Core.cpp
    main.cpp
    Server.cpp
)

target_include_directories(zappy_server PUBLIC
    include
)

target_link_libraries(zappy_server PUBLIC
    warning_options
    shell
    network
)

set_target_properties(zappy_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
