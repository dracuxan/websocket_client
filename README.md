# A CLI based WebSocket Client Written in C++

## Directory Structure:

```
websocket_client/
├── build/
│   ├── BUILDCONFIG.gn           # GN build system configuration
│   ├── BUILD.gn                 # GN build rules for the build directory
│   └── toolchain/               # Toolchain configuration files
├── BUILD.gn                     # Root GN build configuration file
├── compile_flags.txt            # Compiler flags for tooling (e.g., clangd, code completion)
├── include/
│   ├── CLI11.hpp                # CLI11 library header for command-line parsing
│   └── websocketpp/             # WebSocket++ library headers
├── Makefile                     # Makefile for building the project using Make
├── README.md                    # Project overview and build/setup instructions
└── src/
    ├── command_parser.cpp       # Implementation of the command-line parser
    ├── command_parser.hpp       # Header for command-line parsing logic
    ├── connection_metadata.cpp  # Implementation for managing WebSocket connection metadata
    ├── connection_metadata.hpp  # Header for connection metadata structures
    ├── main.cpp                 # Main application entry point
    ├── websocket_endpoint.cpp   # Implementation of WebSocket client connection
    └── websocket_endpoint.hpp   # Header for WebSocket connection logic
```

## Build and Run Commands

```bash
make build
```

builds the project by running `gn gen out` and `ninja -C out`.

```bash
make run
```

runs the project using binary in `out` directory.

## A bit of theory

1. GN vs Ninja?
   > GN is used to generate Ninja build files. Ninja is used to build the entire project.
2. What is a WebSocket, and how does it differ from regular HTTP?
   > WebSockets enable real-time chats with a persistent connection.
3. How do you establish a WebSocket connection between a client and a server?
   > Establish it with an HTTP handshake upgrading to a ws:// or wss:// connection.
4. What are the main advantages of using WebSockets for real-time communication?
   > WebSockets offer low latency and bidirectional data for real-time apps.
5. How do you send and receive messages using a WebSocket?
   > Send with a send method, receive via an event handler in a loop.
6. What happens if a WebSocket connection is lost—can it reconnect automatically?
   > Connection closes on loss; auto-reconnect depends on manual or library logic.

## References:

- https://websocket.org/guides/road-to-websockets/
- https://docs.websocketpp.org/index.html
