//
// Created by Denis Le Borgne on 14/12/2015.
//

# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
#include <sstream>
#include "TcpConnector.hpp"


TcpConnector::TcpConnector(std::string const& addr, short int port)
        : TcpSocket(addr, port)
{
    if ((_socket = ::socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")
            ->p_proto)) < 0)
        throw std::runtime_error("Socket failed");
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

void TcpConnector::connect()
{
    struct sockaddr_in sin;

    sin.sin_addr.s_addr = inet_addr(_addr.c_str());
    sin.sin_port        = htons(_port);
    sin.sin_family      = AF_INET;
    if (::connect(_socket, reinterpret_cast<struct sockaddr *>(&sin),
                  sizeof(sin)) < 0)
        throw std::runtime_error("Can't connect to server");
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
