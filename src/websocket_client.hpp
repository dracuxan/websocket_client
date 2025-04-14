#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <string>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;

class WebSocketClient {
public:
  WebSocketClient();
  void connect(const std::string &uri);
  void run();

private:
  void on_open(websocketpp::connection_hdl hdl);
  void on_fail(websocketpp::connection_hdl hdl);
  void on_close(websocketpp::connection_hdl hdl);

  client ws_client_;
  websocketpp::connection_hdl connection_;
};

#endif
