#pragma once

#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
#include <string>
#include <cpprest/http_msg.h>

using namespace web;
using namespace http;
using namespace http::experimental::listener;

class HttpEndpoint {

public:
    HttpEndpoint(const std::string& address, const std::string& port);
    virtual ~HttpEndpoint() {};

    void setEndpoint(const std::string& mount_point);
    std::string endpoint() const;
    pplx::task<void> accept();
    pplx::task<void> shutdown();
    
protected:
    virtual void initRestHandlers() = 0;
    std::vector<utility::string_t> requestPath(const http_request & message);

    http_listener _listener;

private:
    uri_builder endpointBuilder;
};
