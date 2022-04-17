#pragma once

#include <vector>

#include "HttpEndpoint.h"

class RestHandler : public HttpEndpoint {

public:
    RestHandler(const std::string& address, const std::string& port);

private:
    void handleGet(http_request message);
    void handlePut(http_request message);
    void initRestHandlers() override;

    void defaultReplyFor(http_request message);
    void sumReplyFor(http_request message);
    void avgReplyFor(http_request message);
    float calculateSum();

    std::vector<int> numbers;
};
