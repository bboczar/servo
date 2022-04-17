#include "RestHandler.h"

#include <string>

RestHandler::RestHandler(const std::string& address, const std::string& port)
    : HttpEndpoint(address, port)
{}

void RestHandler::initRestHandlers() {
	_listener.support(methods::GET,std::bind(&RestHandler::handleGet,this,std::placeholders::_1));
	_listener.support(methods::PUT,std::bind(&RestHandler::handlePut,this,std::placeholders::_1));
}

float RestHandler::calculateSum() {
    float sum = 0;
    for(unsigned int i = 0;i<numbers.size();i++) {
        sum+=numbers[i];
    }
    return sum;
}

void RestHandler::handleGet(http_request message) {
    std::vector<std::string> path = requestPath(message);

    if(path.empty())
    {
        defaultReplyFor(message);
    }
    else
    {
        if (path.front() == "avg")
        {
            avgReplyFor(message);
        }
        else if (path.front() == "sum")
        {
            sumReplyFor(message);
        }
    }

    message.reply(status_codes::BadRequest);
}
void RestHandler::handlePut(http_request message)
{
    message.extract_json().then([this, message](pplx::task<json::value> task)
    {
        try
        {
            json::value val = task.get();
            int number = val[U("number")].as_number().to_int32();
            numbers.push_back(number);
            message.reply(status_codes::OK);
        }
        catch(std::exception& e) {
            message.reply(status_codes::BadRequest);
        }
    });
}

void RestHandler::defaultReplyFor(http_request message)
{
    std::vector<json::value> jsonNumbers;

    for(const auto& number : numbers)
    {
        json::value jsonNumber;
        jsonNumber["number"] = json::value::number(number);
        jsonNumbers.push_back(jsonNumber);
    }

    json::value reply;
    reply["numbers"] = json::value::array(jsonNumbers);

    message.reply(status_codes::OK, reply);
}

void RestHandler::avgReplyFor(http_request message)
{
    const float avg = calculateSum() / numbers.size();
    
    json::value reply;
    reply["avg"] = json::value::number(avg);

    message.reply(status_codes::OK, reply);
}

void RestHandler::sumReplyFor(http_request message)
{
    const float sum = calculateSum();

    json::value reply;
    reply["sum"] = json::value::number(sum);

    message.reply(status_codes::OK, reply);
}