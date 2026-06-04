# network_lib {#mainpage}

A lightweight C++ library for building TCP servers and clients. The architecture is inspired by
[boost::asio](https://www.boost.org/doc/libs/latest/doc/html/boost_asio/overview.html). It covers
the same core ideas (async I/O, an event loop, callback-based operations).
It's a simplified version of what has been done in [boost::asio](https://www.boost.org/doc/libs/latest/doc/html/boost_asio/overview.html)

## Architecture Overview

The library is layered. At the bottom sit the primitives; at the top sits an optional high-level
routing abstraction. The heartbeat of the whole system is the `IOContext`. It drives the event loop
and provides a public interface to register async operations.

\dot
digraph architecture {
    label="network_lib layers";
    rankdir=TB;
    node [shape=box, style="filled,rounded", fontname="Helvetica", fontsize=11];

    subgraph cluster_routing {
        label="High-level Abstraction";
        Router [label="Router<TClientState>"];
    }

    subgraph cluster_conn {
        label="Connection Management";
        Acceptor     ;
        ConnectedSocket ;
        ListeningSocket ;
    }

    subgraph cluster_loop {
        label="Event Loop";
        IOContext [label="IOContext — poll(2)"];
    }

    subgraph cluster_prim {
        label="Primitives";
        Endpoint  ;
        Buffer    ;
        ErrorCode ;
    }

    Router      -> Acceptor     [style=invis];
    Acceptor    -> IOContext     [style=invis];
    IOContext   -> Endpoint      [style=invis];
}
\enddot

- `IOContext`: is the central event loop. Every async operation is registered with it and driven
  by its `run()` / `poll()` / `pollAll()` methods.
- `Acceptor`: wraps a `ListeningSocket` and accepts incoming TCP connections asynchronously,
  producing `ConnectedSocket` instances handed to your callback. The `ListeningSocket` itself is not
  really used by the user. The `Acceptor` wraps it to provide a more convenient interface.
- `ConnectedSocket`: is the per-client handle. It supports both synchronous (`read`, `write`) and
  asynchronous (`asyncReadSome`, `asyncWrite`) operations. That's what's embedded in classes like `TcpClient` and
  `ClientSession`.
- `Endpoint`: holds an IPv4 address and port, the address type used throughout the library.
- `Buffer`: provides `ConstBuffer` and `MutableBuffer` value types, along with factory overloads
  for strings, vectors, and raw pointers. Both of them are created through the function
  `network::buffer`.
- `ErrorCode`: defines `FtpErrorCode`, a custom `std::error_code`, use throughout the library to describe
  errors.
- `Router<TClientState>`: is an optional high-level layer. If the user protocol is structured in a HTTP-like way,
  the `Router` class can be used to handle requests dispatching more efficiently.

## Quick Start

The example below sets up a TCP server that accepts one client, sends a greeting, and exits.

```cpp
#include <iostream>

#include "Network/include/IoContext.hpp"
#include "Network/include/Acceptor.hpp"
#include "Network/include/Buffer.hpp"

int main()
{
    network::IOContext ioContext;
    network::Acceptor  acceptor{ioContext, network::Endpoint{8080, "127.0.0.1"}};

    acceptor.asyncAccept([&](const std::error_code &ec,
                   const std::shared_ptr<network::ConnectedSocket> &socket) {
        if (ec) {
            std::cerr << ec.message() << std::endl;
            return;
        }

        std::string msg = "Welcome\r\n";
        socket->asyncWrite(network::buffer(msg), [](auto, auto) {});
    });

    ioContext.run();
    
    return 0;
}
```

## Pages

- \subpage async_model  : How the event loop works and how to schedule async operations
- \subpage routing      : The `Router<TClientState>` high-level abstraction
