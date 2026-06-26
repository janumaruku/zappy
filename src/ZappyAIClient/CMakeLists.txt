set(ZAPPY_AI_WORKSPACE ${CMAKE_CURRENT_SOURCE_DIR})
set(ZAPPY_AI_BINARY    ${ZAPPY_AI_WORKSPACE}/target/release/zappy_ai)

add_custom_target(zappy_ai ALL
    COMMAND cargo build --release --manifest-path ${ZAPPY_AI_WORKSPACE}/Cargo.toml --bin zappy_ai
    COMMAND ${CMAKE_COMMAND} -E copy ${ZAPPY_AI_BINARY} ${CMAKE_SOURCE_DIR}/zappy_ai
    WORKING_DIRECTORY ${ZAPPY_AI_WORKSPACE}
    COMMENT "Building Rust AI client (cargo build --release)"
)
