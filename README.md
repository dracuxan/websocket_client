# A CLI based WebSocket Client Written in C++

## Directory Structure:

```
websocket_client/
├── src/
│   ├── websocket_client.h        # WebSocket connection logic (header)
│   ├── websocket_client.cpp      # WebSocket connection logic (implementation)
│   ├── message_handler.h         # Message sending/receiving logic (header)
│   ├── message_handler.cpp       # Message sending/receiving logic (implementation)
│   ├── cli.h                     # Command-line interface (header)
│   ├── cli.cpp                   # Command-line interface (implementation)
│   └── main.cpp                  # Main entry point
├── tests/
│   ├── websocket_client_test.cpp # Unit tests for WebSocket client
│   ├── message_handler_test.cpp  # Unit tests for message handler
│   └── test_main.cpp             # Test framework entry point
├── build/
│   └── BUILD.gn                  # GN build configuration
├── include/
│   ├── CLI11.hpp                 # CLI11 library header
│   └── websocketpp/              # WebSocket++ headers (folder)
└── README.md                     # Project description and build instructions
```

## Questions encountered during the creation of this project

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
