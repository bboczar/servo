#include "HttpEndpoint.h"

HttpEndpoint::HttpEndpoint(const std::string& address, const std::string& port)
{
   endpointBuilder.set_host(address);
   endpointBuilder.set_port(port);
   endpointBuilder.set_scheme("http");
}

void HttpEndpoint::setEndpoint(const std::string& mount_point)
{
    endpointBuilder.set_path(mount_point);
    _listener = http_listener(endpointBuilder.to_uri());
}

std::string HttpEndpoint::endpoint() const {
    return _listener.uri().to_string();
}

pplx::task<void> HttpEndpoint::accept() {
    initRestHandlers();
    return _listener.open();
}

pplx::task<void> HttpEndpoint::shutdown() {
    return _listener.close();
}

std::vector<utility::string_t> HttpEndpoint::requestPath(const http_request& message)
{
    const auto& relativePath = uri::decode(message.relative_uri().path());
    return uri::split_path(relativePath);
}
