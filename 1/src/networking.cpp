#include "networking.hpp"
namespace CS260 {
    /**
     * @brief
     *  Initializes the networking library
     */
    void NetworkCreate()
    {
        //Initialize the `Winsock` library(windows only)
        WSAData data;
        int WinsockStartup = WSAStartup(MAKEWORD(2, 2), &data);
        if (WinsockStartup != 0)
        {
            std::cout << "Error creating the Network: " << WSAGetLastError() << std::endl;
            WSAGetLastError();
            return;
        }
    }

    /**
     * @brief
     *  Destroys the networking library
     */
    void NetworkDestroy()
    {
        WSACleanup();
    }

    /**
     * @brief
     *  Sets whether a socket would be blocking or not
     */
    void SetSocketBlocking(SOCKET fd, bool blocking)
    {

    }

    /**
     * @brief
     *  Makes socket able to reuse an address
     */
    void SetSocketReuseAddress(SOCKET fd, bool reuse)
    {

    }

    /**
     * @brief
     *  Waits for a socket to have activity
     */
    bool WaitForActivity(SOCKET fd, unsigned timeoutMs)
    {

    }

    /**
     * @brief
     *  Converts a c-string into an ip address. Throws if fails.
     */
    in_addr ToIpv4(std::string const& addr)
    {

    }

    /**
     * @brief
     *  Converts an address to an std::string
     */
    std::string ToString(in_addr const& addr)
    {

    }
}