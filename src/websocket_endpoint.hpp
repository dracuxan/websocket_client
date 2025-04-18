#ifndef WEBSOCKET_ENDPOINT_HPP
#define WEBSOCKET_ENDPOINT_HPP

#include "connection_metadata.hpp"

#include <map>
#include <string>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/config/asio_client.hpp>

class websocket_endpoint {
public:
  websocket_endpoint();
  ~websocket_endpoint();

  int connect(std::string const &uri);
  void close(int id, websocketpp::close::status::value code,
             std::string reason);
  void send(int id, std::string message);
  connection_metadata::ptr get_metadata(int id) const;
  void list_connections() const;

private:
  typedef std::map<int, connection_metadata::ptr> con_list;

  // Configure TLS
  websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context>
  on_tls_init();

  tls_client m_endpoint;
  websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;

  con_list m_connection_list;
  int m_next_id;
};

#endif // WEBSOCKET_ENDPOINT_HPP
