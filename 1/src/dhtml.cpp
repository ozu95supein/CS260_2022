#include "dhtml.hpp"
namespace CS260
{
    void ThrowGeneralErrorMessageAbort()
    {
        std::cout << "Error. ERROR CODE: "<< WSAGetLastError() << std::endl;
        std::abort();
    }
    /**********************************************************************/
    Client::Client()
	{
        mClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	Client::~Client()
	{
        CloseAllSockets();
	}
    void Client::CloseAllSockets()
    {
        closesocket(mClientSocket);
    }
    void Client::ConnectToServer(char const* ip, uint16_t port)
    {
        //create a socket address struct and set its values
        struct sockaddr_in serverAddress;
        if ((mClientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            ThrowGeneralErrorMessageAbort();
        }
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);
        if (inet_pton(AF_INET, ip, &serverAddress.sin_addr) <= 0)
        {
            ThrowGeneralErrorMessageAbort();
        }
        //now that we have the server address, try to connect
        if (connect(mClientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
        {
            ThrowGeneralErrorMessageAbort();
        }
    }
    void Client::RunClient()
    {
        char const* ip = "127.0.0.1";
        uint16_t port = 8080;
        ConnectToServer(ip, port);
        bool Running = true;
        while (Running)
        {
            //Send filename for data request
            //receive data back from server
            //process data
        }
    }
    /**********************************************************************/
    Server::Server(int mt) 
    {
        mServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (mServerSocket == INVALID_SOCKET)
        {
            std::cout << WSAGetLastError() << std::endl;
            std::abort();
        }
        mMaxTransfers = mt;
    }
    Server::~Server()
    {
        CloseAllSockets();
    }
    void Server::CreateEndpointAndBind(char const* ip, uint16_t port)
    {
        sockaddr_in endpoint{};
        endpoint.sin_family = AF_INET;  // Family
        inet_pton(AF_INET, ip, &endpoint.sin_addr);   // Address //converts a string into binarry inet address
        endpoint.sin_port = htons(port);              // Port
        //call the bind function and do the error check
        if (bind(mServerSocket, reinterpret_cast<sockaddr*>(&endpoint), sizeof(endpoint)) == SOCKET_ERROR)
        {
            ThrowGeneralErrorMessageAbort();
        }
    }
    void Server::SetToListen()
    {
        //Set our socket to `listen` mode
        if (listen(mServerSocket, SOMAXCONN) == SOCKET_ERROR)
        {
            ThrowGeneralErrorMessageAbort();
        }
    }
    void Server::AcceptClient()
    {
        mAcceptedClientSocket = accept(mServerSocket, NULL, NULL);
        if (mAcceptedClientSocket == SOCKET_ERROR)
        {
            ThrowGeneralErrorMessageAbort();
        }
    }
    void Server::RunServer()
    {
        char receive_buffer[1000];
        char send_buffer[1000];
        int len = 1000;
        int flags = 0;
        //only run for a certain number of max file transfers
        for (int i = 0; i < mMaxTransfers; i++)
        {
            //Receive data from the client(0 bytes means disconnection, -1 means error)
            int received = recv(mAcceptedClientSocket, receive_buffer, len, flags);
            //disconection
            if (received == 0)
            {
                //client diconected 
                std::cout << "Client Disconected Gracefully" << std::endl;
                break;
            }
            else if (received == SOCKET_ERROR)
            {
                std::cout << "Reception Error, ERROR CODE: " << WSAGetLastError() << std::endl;
            }
            else
            {
                //actually process the message

            }
        }
    }
    void Server::CloseAllSockets()
    {
        closesocket(mServerSocket);
        closesocket(mAcceptedClientSocket);
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
}