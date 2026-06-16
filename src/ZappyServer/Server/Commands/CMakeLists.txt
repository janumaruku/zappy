add_library(zappy_server_commands STATIC)
target_include_directories(zappy_server_commands PUBLIC
    include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
target_link_libraries(zappy_server_commands PUBLIC network world utils warning_options)