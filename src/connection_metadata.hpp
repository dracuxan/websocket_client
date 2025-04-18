#ifndef CONNECTION_METADATA_HPP
#define CONNECTION_METADATA_HPP

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

#include <iostream>
#include <string>
#include <vector>

// Define the client type using TLS configuration
typedef websocketpp::client<websocketpp::config::asio_tls_client> tls_client;

class connection_metadata {
public:
  typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

  connection_metadata(int id, websocketpp::connection_hdl hdl, std::string uri);

  void on_open(tls_client *c, websocketpp::connection_hdl hdl);
  void on_fail(tls_client *c, websocketpp::connection_hdl hdl);
  void on_close(tls_client *c, websocketpp::connection_hdl hdl);
  void on_message(websocketpp::connection_hdl hdl, tls_client::message_ptr msg);

  websocketpp::connection_hdl get_hdl() const;
  int get_id() const;
  std::string get_status() const;
  void record_sent_message(std::string message);

  friend std::ostream &operator<<(std::ostream &out,
                                  connection_metadata const &data);

private:
  int m_id;
  websocketpp::connection_hdl m_hdl;
  std::string m_status;
  std::string m_uri;
  std::string m_server;
  std::string m_error_reason;
  std::vector<std::string> m_messages;

  // Maximum message history to store (to prevent unbounded memory growth)
  static const size_t MAX_MESSAGE_HISTORY = 100;
};

#endif // CONNECTION_METADATA_HPP
