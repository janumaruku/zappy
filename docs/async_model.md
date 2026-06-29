# The Async Model {#async_model}

The main and most powerful feature of the library is its asynchronous model. The possibility of doing asynchronous
operations without the need of threads. All of that is possible, thanks to the use of [`poll(2)`](https://man7.org/linux/man-pages/man2/poll.2.html)


## Why asynchronous?

First, synchronous operations are still possible with the library. But why do you need synchronous operations?

What you have to understand is that when doing input output operations, the input operations are
blocking. That means that when you start reading from a file descriptor (via `std::getline()` for example) at a
certain point in time in your program, the rest of the program is blocked until the read operation completes.

```cpp
std::string line;

std::getline(std::cin, line); // blocks until the read operation completes

std::cout << "Read line: " << line << std::endl;
```

In the example above, the program is blocked until the user types a line. In this case, you could think that it's not
really an issue. Maybe because we need the data from the user before we can do anything else. But in a situation where
you have, for example, a socket accepting multiple connections, and each connection can send and receive data, you
can't loop through the list of connected sockets and read / write data from them.

\includelineno blocking_socket.cpp

There are several issues with the above code:

### 1. Bocking `accept()`

At line 28, the program is blocked because the system call `accept()` is blocking. And it will be until 
a client effectively connects to the server and got accepted. Otherwise, the program will be blocked forever at
that point indefinitely. Even if several clients successfully connect to the server, on the next iteration of the
loop, at the same line, the program will be blocked again, even though no client is trying to connect. Then the
next instructions will never be executed.

### 2. Bocking `read()`

At line 35, the program is blocked because the system call `read()` is blocking. There, the server is trying to read
some bytes from the client file descriptor. But it can only get data from it only if the client actually sends
some data. Otherwise, the server will be blocked forever at that point indefinitely, waiting for data to arrive. But
that's not the only issue. Because there could be several clients connected to the server, and because the read
operation is blocking, the clients will have to wait for the client above them in the list to send and receive data
before getting the handle and do their request. So one client not responding will block the whole server and all other
clients.

### How to address these issues then?

That's where asynchronous operations come in. What does it really mean to do asynchronous operations? In the usual
context, it means that the program can continue to do other things while the system call is blocking. And still in the
usual context, this involves multithreading (using C++ `std::async` for example, or just `std::thread`).

But in the network context, we don't necessarily need to use threads. We have some really useful functions, and the one
we use in our case is [poll(2)](https://man7.org/linux/man-pages/man2/poll.2.html). It's a system call that allows us to
know when a file descriptor is ready to be read or written.

\includelineno accept_with_poll.cpp

### 1. Non-blocking `accept()`

At line 33, `accept()` is now only called when `fds[0].revents & POLLIN` is true, meaning the
kernel has already confirmed that a connection is waiting. `poll()` at line 28 is the one that waits,
up to the specified timeout, monitoring all file descriptors at once. If a connection arrives
before the timeout expires, it returns immediately. If no client is connecting but some are sending
data, `poll()` still returns and the loop proceeds to handle them.

### 2. Non-blocking `read()`

At line 43, `read()` is only called when `fds[i].revents & POLLIN` is true for that specific
client fd. If a client is silent, its fd is simply skipped. It does not stall the loop. Every
client gets served as soon as it has data ready, independently of the others.

> Even in that context, we can't really say that the operations are asynchronous. All we are doing
> is telling the kernel that we want to know when a file descriptor is ready to be read or written.
> Then we read or write from the file descriptor at a specific point in time when we won't block
> the rest of the program.
 
## The async model in the library

In the library, asynchronous operations are done using some classes that implement the async model,
like `ConnectedSocket` and `Acceptor`. They both subscrit to the `IOContext` class, which is the
main class that drives the async operations. `ConnectedSocket` and `Acceptor` register their operations
to the `IOContext` using the `postRead` and `postWrite` public methods.

### The async model in `network::Acceptor`

The `Acceptor` class is a wrapper around `ListenSocket`, the functions `bind()` and `listen()` and the
system call `accept()`. It only exposes the `asyncAccept()` method, which is the one that accepts
new connections.

\includelineno acceptor_async_accept.cpp

What you see on the code above is a use of the async model with `Acceptor`. The first line of the main
function creates an `IOContext` and the next one creates an `Acceptor`, attached to that context and
listening on a specific port. Next, you have the call to the function `startAccept(acceptor)`, which
is non-blocking, and we will why in a moment. And finally, we have the call to `iocontext.run()`. This
one is blocking though. That's why it's always called last.

The function `startAccept()` is a helper function that calls `asyncAccept()` on the `Acceptor`. What
really happens is that the `Acceptor` does try to accept a new connection immediately. Instead, it
registers a callback that will be called when the kernel signals readiness. That's why the call there
is non-blocking. And when you get back to the main, the call to `iocontext.run()` is what actually
blocks lunches the file descriptor polling loop and the execution of the callbacks.

Another thing to notice is that inside the callback registered in `startAccept()`, you have a recursive
call to `startAccept()`. That means that when the file descriptor will be ready, and the callback
will be executed, during that execution, it will call `startAccept()` again, which will register
another callback. That's how the acceptor can accept multiple connections at the same time.

### The async model in `network::ConnectedSocket`

`ConnectedSocket` exposes two async methods: `asyncReadSome()` to receive data and `asyncWrite()`
to send it. The example below combines everything seen so far, accepting connections and handling
the read/write cycle for each client in a circular, callback-driven loop.

\includelineno connected_socket_async.cpp

`startClient()` at line 39 is the entry point for a newly accepted client. It allocates the read
buffer on the heap via `shared_ptr` and hands it to `handleRead()`. From there the cycle is:

- `handleRead()` registers an async read. When data arrives, it prints it and calls `handleWrite()`.
- `handleWrite()` registers an async write. When the write completes, it calls `handleRead()` again.

The loop is circular and keeps running as long as the connection is alive.

> **Pay attention to buffer lifetime.** Both `ConstBuffer` and `MutableBuffer` store a raw pointer
> to the underlying data. They do not own it. If the buffer goes out of scope before the async
> operation completes, the pointer dangles and the behavior is undefined. The fix is to
> heap-allocate the buffer and capture the `shared_ptr` in the callback lambda, as done at lines 51
> and 70: the lambda keeps the `shared_ptr` alive until the callback fires, guaranteeing the raw
> pointer remains valid.

## How `IOContext` ties it all together

After looking at how `Acceptor` and `ConnectedSocket` work, you might be wondering what is actually
happening under the hood. Both classes never call `poll(2)` or `accept()` or `read()` directly when
you call `asyncAccept()`, `asyncReadSome()`, or `asyncWrite()`. Instead, they register a callback
and a file descriptor with the `IOContext`, using its `postRead` and `postWrite` methods. The
`IOContext` is the one that actually drives the whole thing.

Internally, `IOContext` maintains a list of `pollfd` structures and a queue of pending callbacks
per file descriptor. Every time you post an async operation, it is enqueued, not executed
immediately. The execution happens only when you tick the loop, which is what `ioContext.run()`
does. That is why in all the examples above, `ioContext.run()` is always called last, and it is the
only blocking call in the `main` function.

Here is what really happens, step by step, every time you make an async call:

\dot
digraph lifecycle {
    rankdir=LR;
    node [shape=box, style="filled,rounded", fontname="Helvetica", fontsize=11];

    post     [label="asyncReadSome()\nor asyncWrite()"];
    enqueue  [label="postRead / postWrite\nenqueues callback"];
    poll2    [label="poll(2)\nwaits for kernel"];
    ready    [label="fd ready"];
    dispatch [label="read/write happens\ncallback executed"];

    post -> enqueue -> poll2 -> ready -> dispatch;
}
\enddot

1. You call `asyncReadSome()` or `asyncWrite()` on a `ConnectedSocket`, or `asyncAccept()` on an
   `Acceptor`. Internally, this calls `postRead` or `postWrite` on the `IOContext`, registering
   your callback alongside the file descriptor.
2. The `IOContext` enqueues the operation and updates the `pollfd` entry for that fd to watch for
   the correct event (`POLLIN` or `POLLOUT`).
3. On the next loop tick, `poll(2)` waits (up to the configured timeout) until at least one
   watched fd is ready.
4. For each ready fd, the `IOContext` pops the front of its callback queue and invokes it. That is
   when your lambda runs.

`IOContext` exposes three methods to control how the loop ticks:

| Method | Behaviour |
|--------|-----------|
| `run()` | Blocks, ticking the loop continuously until `stop()` is called. The normal entry point for a server. |
| `poll()` | Runs a single tick: calls `poll(2)` once, dispatches ready callbacks, then returns. |
| `pollAll()` | Drains all pending operations without blocking on `poll(2)`. Returns once the queue is empty. |