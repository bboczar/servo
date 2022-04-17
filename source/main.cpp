#include <iostream>
#include "RestHandler.h"

int main()
{
    RestHandler serv("127.0.0.1","8080");
    serv.setEndpoint("/api");
    serv.accept().wait();
    while(1==1)
    {
        sleep(1000);
    }
    return 0;
}
