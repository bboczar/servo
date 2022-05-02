#include <iostream>
#include "RestHandler.h"

int main()
{
    RestHandler serv("0.0.0.0","12345");
    serv.setEndpoint("/api");
    serv.accept().wait();
    while(1==1)
    {
        sleep(1000);
    }
    return 0;
}
