#ifndef __NETWORKING_HPP__
#define __NETWORKING_HPP__

#include <string>
#include <iostream>

#ifdef __linux__
#include <sys/socket.h> // sockets
#include <sys/poll.h>   // poll
#include <netinet/in.h> // sockaddr_in
#include <netdb.h>      // addrinfo
#include <arpa/inet.h>  // inet_pton
#include <errno.h>      // Errors
#include <unistd.h>     // close()
#include <fcntl.h>      // Non-Blocking sockets
// Porting from windows code
#define WSAGetLastError() errno                          // In windows, errors are stored in WSAGetLastError, most errors are similar
#define WSAPoll(fds, c, timeout) ::poll(fds, c, timeout) // In windows, there is native poll. ALMOST similar.
#define WSAPOLLFD pollfd                                 //
#define SOCKET int                                       // In windows, SOCKET is the socket data type, not file descriptors
#define INVALID_SOCKET ~0                                //
#define SOCKET_ERROR -1                                  //
#define closesocket(fd) ::close(fd)                      // In windows, close is closesocket (they are not file descriptors in windows)
#define WSAEWOULDBLOCK EWOULDBLOCK
#elif _WIN32
#include <WinSock2.h> // Basic WSA features (socket, connect, ...)
#include <WS2tcpip.h> // More WSA features (such inet_pton, inet_ntop, ...)
using socklen_t = int; // Trick for accept
#endif

namespace CS260 {
    /**
     * @brief
     *  Initializes the networking library
     */
    void NetworkCreate();

    /**
     * @brief
     *  Destroys the networking library
     */
    void NetworkDestroy();

    /**
     * @brief
     *  Sets whether a socket would be blocking or not
     */
    void SetSocketBlocking(SOCKET fd, bool blocking);

    /**
     * @brief
     *  Makes socket able to reuse an address
     */
    void SetSocketReuseAddress(SOCKET fd, bool reuse);

    /**
     * @brief
     *  Waits for a socket to have activity
     */
    bool WaitForActivity(SOCKET fd, unsigned timeoutMs);

    /**
     * @brief
     *  Converts a c-string into an ip address. Throws if fails.
     */
    in_addr ToIpv4(std::string const& addr);

    /**
     * @brief
     *  Converts an address to an std::string
     */
    std::string ToString(in_addr const& addr);
}
#endif // __NETWORKING_HPP__
