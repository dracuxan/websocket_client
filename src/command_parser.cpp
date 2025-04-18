#include "command_parser.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

command_parser::command_parser(websocket_endpoint &endpoint)
    : m_endpoint(endpoint) {}

bool command_parser::process_command(const std::string &input) {
  if (input.empty()) {
    return true;
  }

  if (input == "exit") {
    return false;
  } else if (input == "help") {
    display_help();
  } else if (input.substr(0, 7) == "connect") {
    if (input.length() <= 8) {
      std::cout << "> Invalid connect command. Usage: connect <wss uri>"
                << std::endl;
      return true;
    }

    std::string uri = input.substr(8);
    // Basic validation of URI format
    if (uri.substr(0, 6) != "wss://") {
      std::cout
          << "> Warning: URI should start with 'wss://' for secure connections"
          << std::endl;
    }

    int id = m_endpoint.connect(uri);
    if (id != -1) {
      std::cout << "> Created connection with id " << id << std::endl;
    }
  } else if (input.substr(0, 4) == "send") {
    std::stringstream ss(input);

    std::string cmd;
    int id;
    std::string message;

    ss >> cmd >> id;
    if (ss.fail()) {
      std::cout
          << "> Invalid send command. Usage: send <connection_id> <message>"
          << std::endl;
      return true;
    }

    std::getline(ss, message);
    if (message.empty()) {
      std::cout << "> No message specified" << std::endl;
      return true;
    }

    // Remove leading space if present
    if (message[0] == ' ') {
      message = message.substr(1);
    }

    m_endpoint.send(id, message);
  } else if (input.substr(0, 5) == "close") {
    std::stringstream ss(input);

    std::string cmd;
    int id;
    int close_code = websocketpp::close::status::normal;
    std::string reason;

    ss >> cmd >> id;
    if (ss.fail()) {
      std::cout << "> Invalid close command. Usage: close <connection_id> "
                   "[<close_code>] [<reason>]"
                << std::endl;
      return true;
    }

    ss >> close_code;
    std::getline(ss, reason);

    // Remove leading space if present
    if (!reason.empty() && reason[0] == ' ') {
      reason = reason.substr(1);
    }

    m_endpoint.close(
        id, static_cast<websocketpp::close::status::value>(close_code), reason);
  } else if (input.substr(0, 4) == "show") {
    if (input.length() <= 5) {
      std::cout << "> Invalid show command. Usage: show <connection_id>"
                << std::endl;
      return true;
    }

    try {
      int id = std::stoi(input.substr(5));
      connection_metadata::ptr metadata = m_endpoint.get_metadata(id);
      if (metadata) {
        std::cout << *metadata << std::endl;
      } else {
        std::cout << "> Unknown connection id " << id << std::endl;
      }
    } catch (const std::invalid_argument &) {
      std::cout << "> Invalid connection ID format" << std::endl;
    }
  } else if (input == "list") {
    m_endpoint.list_connections();
  } else {
    std::cout << "> Unrecognized Command. Type 'help' for available commands."
              << std::endl;
  }

  return true;
}

void command_parser::display_help() const {
  std::cout << "\nCommand List:\n"
            << "connect <wss uri> - Connect to a secure WebSocket server\n"
            << "send <connection id> <message> - Send a message to the server\n"
            << "close <connection id> [<close code:default=1000>] [<close "
               "reason>] - Close a connection\n"
            << "show <connection id> - Show details of a specific connection\n"
            << "list - List all active connections\n"
            << "help - Display this help text\n"
            << "exit - Exit the program\n"
            << std::endl;
}
