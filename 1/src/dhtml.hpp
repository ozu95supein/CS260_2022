#include <iostream>
#include <string>
#include "networking.hpp"
#include <cstdlib>
namespace CS260
{
    class Client
    {
    public:
        Client();
        ~Client();
        void ConnectToServer(char const* ip, uint16_t port);
        void CloseAllSockets();
        void RunClient();
    private:
        SOCKET mClientSocket;

    };

    class Server
    {
    public:
        Server(int mt);
        ~Server();
        void CreateEndpointAndBind(char const* ip, uint16_t port);
        void SetToListen();
        void AcceptClient();
        void RunServer();
        void CloseAllSockets();
    private:
        SOCKET mServerSocket;
        SOCKET mAcceptedClientSocket;
        int mMaxTransfers;
    };

    void DisplayHelpMessage();
}
