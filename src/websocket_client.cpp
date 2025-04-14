#include "websocket_client.hpp"
#include <iostream>

WebSocketClient::WebSocketClient() {
  ws_client_.set_access_channels(websocketpp::log::alevel::all);
  ws_client_.clear_access_channels(websocketpp::log::alevel::frame_payload);
  ws_client_.init_asio();

  ws_client_.set_open_handler(
      [this](websocketpp::connection_hdl hdl) { on_open(hdl); });
  ws_client_.set_fail_handler(
      [this](websocketpp::connection_hdl hdl) { on_fail(hdl); });
  ws_client_.set_close_handler(
      [this](websocketpp::connection_hdl hdl) { on_close(hdl); });
}

void WebSocketClient::connect(const std::string &uri) {
  try {
    websocketpp::lib::error_code ec;
    client::connection_ptr con = ws_client_.get_connection(uri, ec);
    if (ec) {
      std::cout << "Connection error: " << ec.message() << std::endl;
      return;
    }

    connection_ = con->get_handle();
    ws_client_.connect(con);
  } catch (const std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }
}

void WebSocketClient::run() {
  try {
    ws_client_.run();
  } catch (const std::exception &e) {
    std::cout << "Run exception: " << e.what() << std::endl;
  }
}

void WebSocketClient::on_open(websocketpp::connection_hdl) {
  std::cout << "Connected to server!" << std::endl;
}

void WebSocketClient::on_fail(websocketpp::connection_hdl) {
  std::cout << "Connection failed!" << std::endl;
}

void WebSocketClient::on_close(websocketpp::connection_hdl) {
  std::cout << "Connection closed!" << std::endl;
}
