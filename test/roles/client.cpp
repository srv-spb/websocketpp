/*
 * Copyright (c) 2013, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE client
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <websocketpp/config/core.hpp>
#include <websocketpp/client.hpp>

struct stub_config : public websocketpp::config::core {
    typedef core::concurrency_type concurrency_type;

    typedef core::request_type request_type;
    typedef core::response_type response_type;

    typedef core::message_type message_type;
    typedef core::con_msg_manager_type con_msg_manager_type;
    typedef core::endpoint_msg_manager_type endpoint_msg_manager_type;

    typedef core::alog_type alog_type;
    typedef core::elog_type elog_type;

    typedef core::rng_type rng_type;
    
    typedef core::transport_type transport_type;
    
    typedef core::endpoint_base endpoint_base;
};

typedef websocketpp::client<stub_config> client;
typedef client::connection_ptr connection_ptr;

BOOST_AUTO_TEST_CASE( invalid_uri ) {
    client c;
    websocketpp::lib::error_code ec;
    
    connection_ptr con = c.get_connection("foo", ec);
    
    BOOST_CHECK( ec == websocketpp::error::make_error_code(websocketpp::error::invalid_uri) );
}

BOOST_AUTO_TEST_CASE( unsecure_endpoint ) {
    client c;
    websocketpp::lib::error_code ec;
    
    connection_ptr con = c.get_connection("wss://localhost/", ec);
    
    BOOST_CHECK( ec == websocketpp::error::make_error_code(websocketpp::error::endpoint_not_secure) );
}

BOOST_AUTO_TEST_CASE( get_connection ) {
    client c;
    websocketpp::lib::error_code ec;
    
    connection_ptr con = c.get_connection("ws://localhost/", ec);
    
    BOOST_CHECK( con );
}