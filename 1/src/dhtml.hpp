#include <iostream>
#include <string>
#include "networking.hpp"
class Client()
{
public:
    Client();
    ~Client();
private:
}
class Server()
{
public:
    Server();
    ~Server();
private:
}
void DisplayHelpMessage()
{
    std::cout << "Usage: dhtml [options] <FILE>" << std::endl;
    std::cout << "Connects to the specified address:port and makes an http request of <FILE>" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "--server                                Executes in server mode" << std::endl;
    std::cout << "--client                                Executes in client mode, closes after a transfer has happened" << std::endl;
    std::cout << "--address <ADDRESS>                     Specifies the IPV4 address in which to listen or the IPV4 address to which to connect" << std::endl;
    std::cout << "--port <PORT>                           Specifies the UDP in which to receive data or the UDP port to which to send data" << std::endl;
    std::cout << "--verbose                               If set, will display debug information, otherwise it won't" << std::endl;
    std::cout << " " << std::endl;
}
