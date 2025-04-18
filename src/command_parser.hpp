#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include "websocket_endpoint.hpp"
#include <string>

class command_parser {
public:
  command_parser(websocket_endpoint &endpoint);

  bool process_command(const std::string &input);
  void display_help() const;

private:
  websocket_endpoint &m_endpoint;
};

#endif // COMMAND_PARSER_HPP
