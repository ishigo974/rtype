//
// Created by Denis Le Borgne on 06/12/2015.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <unistd.h>
#endif

#include <sstream>
#include "TcpConnector.hpp"


TcpConnector::TcpConnector(std::string const& addr, short int port)
        : TcpSocket(addr, port)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
         throw std::runtime_error("WSAStartup failed");
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
        throw std::runtime_error("LOBYTE / HIBYTE failed");
    if ((_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            throw std::runtime_error("Socket failed");
#else
    if ((_socket = ::socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")
            ->p_proto)) < 0)
        throw std::runtime_error("Socket failed");
#endif
}

TcpConnector::~TcpConnector()
{
    close();
}

short int TcpConnector::getPort() const
{
    return _port;
}

std::string const& TcpConnector::getAddr() const
{
    return _addr;
}

bool TcpConnector::connect()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    struct sockaddr_in sin;

    inet_pton(AF_INET, _addr.c_str(), &sin.sin_addr);
    sin.sin_port = htons(_port);
    sin.sin_family = AF_INET;

    if (WSAConnect(_socket, reinterpret_cast<struct sockaddr *>(&sin), sizeof(SOCKADDR), nullptr, nullptr, nullptr, nullptr)
            == SOCKET_ERROR)
        return false;
    return true;
#else
    struct sockaddr_in sin;

    sin.sin_addr.s_addr = inet_addr(_addr.c_str());
    sin.sin_port        = htons(_port);
    sin.sin_family      = AF_INET;
    return (::connect(_socket, reinterpret_cast<struct sockaddr *>(&sin),
                      sizeof(sin)) >= 0);
#endif
}

rSocket TcpConnector::getSocket() const
{
    return _socket;
}

std::string TcpConnector::toString() const
{
    std::ostringstream ss;

    ss << "TcpConnector {"
    << "\n\tSocket " << this->_socket
    << "\n\tPort " << this->_port
    << "\n}" << std::endl;

    return ss.str();
}
