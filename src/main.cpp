#include "command_parser.hpp"
#include "websocket_endpoint.hpp"

#include <iostream>
#include <string>

int main() {
  std::cout << "WebSocket Secure Client\n";
  std::cout << "=======================\n";
  std::cout << "Type 'help' for command list\n\n";

  websocket_endpoint endpoint;
  command_parser parser(endpoint);

  bool running = true;
  std::string input;

  while (running) {
    std::cout << "Enter Command: ";
    std::getline(std::cin, input);

    running = parser.process_command(input);
  }

  std::cout << "Exiting application..." << std::endl;
  return 0;
}
