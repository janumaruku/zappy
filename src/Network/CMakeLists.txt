add_library(network STATIC Acceptor.cpp
        Buffer.cpp
        ConnectedSocket.cpp
        Endpoint.cpp
        EntitySerializer.cpp
        ErrorCode.cpp
        IoContext.cpp
        ListeningSocket.cpp
        Serializer.cpp)

target_include_directories(network PUBLIC include)

target_link_libraries(network PUBLIC utils warning_options)