add_library(world_state WorldState.cpp
        GUIMap.cpp
        GUIPlayer.cpp
        Team.cpp
        ZappyEvents.cpp
        include/ZappyEvents.hpp)

target_include_directories(world_state PUBLIC include)

target_link_libraries(world_state PUBLIC utils warning_options
        zappy_data
        )
