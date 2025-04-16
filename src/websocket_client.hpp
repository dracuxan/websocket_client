#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

#include <websocketpp/common/memory.hpp>
#include <websocketpp/common/thread.hpp>

#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string.h>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class connection_metadata {
public:
  typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;
  connection_metadata(int id, websocketpp::connection_hdl hdl, std::string uri)
      : m_id(id), m_hdl(hdl), m_uri(uri), m_status("Connecting"),
        m_server("N/A") {}
  void on_open(client *c, websocketpp::connection_hdl hdl) {
    m_status = "Open";

    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
  }

  void on_fail(client *c, websocketpp::connection_hdl hdl) {
    m_status = "Failed";

    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
    m_error_reason = con->get_ec().message();
  }

  friend std::ostream &operator<<(std::ostream &out,
                                  connection_metadata const &data);

private:
  int m_id;
  websocketpp::connection_hdl m_hdl;
  std::string m_status;
  std::string m_uri;
  std::string m_server;
  std::string m_error_reason;
};

std::ostream &operator<<(std::ostream &out, connection_metadata const &data);

// std::ostream &operator<<(std::ostream &out, connection_metadata const &data)
// {
//   out << "> URI: " << data.m_uri << "\n"
//
//       << "> Status: " << data.m_status << "\n"
//       << "> Remote Server: "
//       << (data.m_server.empty() ? "None Specified" : data.m_server) << "\n"
//       << "> Error/close reason: "
//       << (data.m_error_reason.empty() ? "N/A" : data.m_error_reason);
//
//   return out;
// }
//
// class websocket_endpoint {
// public:
//   websocket_endpoint() : m_next_id(0) {
//     m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
//     m_endpoint.clear_error_channels(websocketpp::log::elevel::all);
//
//     m_endpoint.init_asio();
//     m_endpoint.start_perpetual();
//
//     m_thread.reset(new websocketpp::lib::thread(&client::run, &m_endpoint));
//   }
//
//   int connect(std::string const &uri) {
//     websocketpp::lib::error_code ec;
//
//     client::connection_ptr con = m_endpoint.get_connection(uri, ec);
//
//     if (ec) {
//       std::cout << "> Connect initialization error: " << ec.message()
//                 << std::endl;
//       return -1;
//     }
//
//     int new_id = m_next_id++;
//     connection_metadata::ptr metadata_ptr(
//         new connection_metadata(new_id, con->get_handle(), uri));
//     m_connection_list[new_id] = metadata_ptr;
//
//     con->set_open_handler(websocketpp::lib::bind(
//         &connection_metadata::on_open, metadata_ptr, &m_endpoint,
//         websocketpp::lib::placeholders::_1));
//     con->set_fail_handler(websocketpp::lib::bind(
//         &connection_metadata::on_fail, metadata_ptr, &m_endpoint,
//         websocketpp::lib::placeholders::_1));
//
//     m_endpoint.connect(con);
//
//     return new_id;
//   }
//
//   connection_metadata::ptr get_metadata(int id) const {
//     con_list::const_iterator metadata_it = m_connection_list.find(id);
//     if (metadata_it == m_connection_list.end()) {
//       return connection_metadata::ptr();
//     } else {
//       return metadata_it->second;
//     }
//   }
//
// private:
//   typedef std::map<int, connection_metadata::ptr> con_list;
//
//   client m_endpoint;
//   websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;
//
//   con_list m_connection_list;
//   int m_next_id;
// };
