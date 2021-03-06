// Copyright Takatoshi Kondo 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(MQTT_TEST_COMBI_TEST_HPP)
#define MQTT_TEST_COMBI_TEST_HPP

#include "test_settings.hpp"
#include "test_broker.hpp"
#include "test_server_no_tls.hpp"
#if !defined(MQTT_NO_TLS)
#include "test_server_tls.hpp"
#endif // !defined(MQTT_NO_TLS)

#if defined(MQTT_USE_WS)
#include "test_server_no_tls_ws.hpp"
#if !defined(MQTT_NO_TLS)
#include "test_server_tls_ws.hpp"
#endif // !defined(MQTT_NO_TLS)
#endif // defined(MQTT_USE_WS)

#include <mqtt/sync_client.hpp>
#include <mqtt/async_client.hpp>

struct sync_type {};
struct async_type {};

template <typename Test>
inline void do_combi_test(Test const& test) {
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls s(ioc, b);
        auto c = MQTT_NS::make_client(ioc, broker_url, broker_notls_port);
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls s(ioc, b);
        auto c = MQTT_NS::make_client(ioc, broker_url, broker_notls_port, MQTT_NS::protocol_version::v5);
        test(ioc, c, s, b);
    }
#if !defined(MQTT_NO_TLS)
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls s(ioc, b);
        auto c = MQTT_NS::make_tls_client(ioc, broker_url, broker_tls_port);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls s(ioc, b);
        auto c = MQTT_NS::make_tls_client(ioc, broker_url, broker_tls_port, MQTT_NS::protocol_version::v5);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
#endif // !defined(MQTT_NO_TLS)
#if defined(MQTT_USE_WS)
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_client_ws(ioc, broker_url, broker_notls_ws_port);
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_client_ws(ioc, broker_url, broker_notls_ws_port, "/", MQTT_NS::protocol_version::v5);
        test(ioc, c, s, b);
    }
#if !defined(MQTT_NO_TLS)
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_tls_client_ws(ioc, broker_url, broker_tls_ws_port);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_tls_client_ws(ioc, broker_url, broker_tls_ws_port, "/", MQTT_NS::protocol_version::v5);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
#endif // !defined(MQTT_NO_TLS)
#endif // defined(MQTT_USE_WS)
}

template <typename Test>
inline void do_combi_test_sync(Test const& test) {
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls s(ioc, b);
        auto c = MQTT_NS::make_sync_client(ioc, broker_url, broker_notls_port);
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls s(ioc, b);
        auto c = MQTT_NS::make_sync_client(ioc, broker_url, broker_notls_port, MQTT_NS::protocol_version::v5);
        test(ioc, c, s, b);
    }
#if !defined(MQTT_NO_TLS)
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls s(ioc, b);
        auto c = MQTT_NS::make_tls_sync_client(ioc, broker_url, broker_tls_port);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls s(ioc, b);
        auto c = MQTT_NS::make_tls_sync_client(ioc, broker_url, broker_tls_port, MQTT_NS::protocol_version::v5);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
#endif // !defined(MQTT_NO_TLS)
#if defined(MQTT_USE_WS)
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_sync_client_ws(ioc, broker_url, broker_notls_ws_port);
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_sync_client_ws(ioc, broker_url, broker_notls_ws_port, "/", MQTT_NS::protocol_version::v5);
        test(ioc, c, s, b);
    }
#if !defined(MQTT_NO_TLS)
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_tls_sync_client_ws(ioc, broker_url, broker_tls_ws_port);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_tls_sync_client_ws(ioc, broker_url, broker_tls_ws_port, "/", MQTT_NS::protocol_version::v5);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
#endif // !defined(MQTT_NO_TLS)
#endif // defined(MQTT_USE_WS)
}

template <typename Test>
inline void do_combi_test_async(Test const& test) {
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls s(ioc, b);
        auto c = MQTT_NS::make_async_client(ioc, broker_url, broker_notls_port);
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls s(ioc, b);
        auto c = MQTT_NS::make_async_client(ioc, broker_url, broker_notls_port, MQTT_NS::protocol_version::v5);
        test(ioc, c, s, b);
    }
#if !defined(MQTT_NO_TLS)
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls s(ioc, b);
        auto c = MQTT_NS::make_tls_async_client(ioc, broker_url, broker_tls_port);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls s(ioc, b);
        auto c = MQTT_NS::make_tls_async_client(ioc, broker_url, broker_tls_port, MQTT_NS::protocol_version::v5);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
#endif // !defined(MQTT_NO_TLS)
#if defined(MQTT_USE_WS)
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_async_client_ws(ioc, broker_url, broker_notls_ws_port);
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_no_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_async_client_ws(ioc, broker_url, broker_notls_ws_port, "/", MQTT_NS::protocol_version::v5);
        test(ioc, c, s, b);
    }
#if !defined(MQTT_NO_TLS)
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_tls_async_client_ws(ioc, broker_url, broker_tls_ws_port);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
    {
        boost::asio::io_context ioc;
        test_broker b(ioc);
        test_server_tls_ws s(ioc, b);
        auto c = MQTT_NS::make_tls_async_client_ws(ioc, broker_url, broker_tls_ws_port, "/", MQTT_NS::protocol_version::v5);
        std::string path = boost::unit_test::framework::master_test_suite().argv[0];
        std::size_t pos = path.find_last_of("/\\");
        std::string base = (pos == std::string::npos) ? "" : path.substr(0, pos + 1);
        c->set_ca_cert_file(base + "cacert.pem");
        test(ioc, c, s, b);
    }
#endif // !defined(MQTT_NO_TLS)
#endif // defined(MQTT_USE_WS)
}

#endif // MQTT_TEST_COMBI_TEST_HPP
