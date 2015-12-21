//
// Created by Denis Le Borgne on 14/12/2015.
//

#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
#include "SocketMonitor.hpp"
#include "UdpSocket.hpp"

UdpSocket::UdpSocket(short int port) : BaseSocket()
{
    _port        = port;
    if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        throw std::runtime_error("socket failed");
}

UdpSocket::~UdpSocket()
{
}

size_t  UdpSocket::sendTo(Buffer const& buffer, std::string const& addr) const
{
    ssize_t            ret;
    struct sockaddr_in dest;

    dest.sin_addr.s_addr = inet_addr(addr.c_str());
    dest.sin_port        = htons(_port);
    dest.sin_family      = AF_INET;

    if ((ret = ::sendto(_socket, buffer.data(), buffer.size(), 0,
                        reinterpret_cast<struct sockaddr *>(&dest),
                        sizeof(dest))) == -1)
        throw std::runtime_error("send failed");
    return (static_cast<size_t>(ret));
}

size_t        UdpSocket::receiveFrom(Buffer& buffer, size_t len,
                                     std::string& addr) const
{
    ssize_t            ret;
    struct sockaddr_in client;
    char               *buff      = new char[len];
    socklen_t          clientsize = sizeof(client);
    struct timeval     tv;


    std::memset(&client, 0, sizeof(client));
    ret = -1;
    tv.tv_sec  = 2;
    tv.tv_usec = 0;

    if (setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
        throw std::runtime_error("SetSockOpt failed");
    if (((ret = ::recvfrom(_socket, buff, len, 0,
                          reinterpret_cast<struct sockaddr *>(&client),
                          &clientsize)) == -1) && errno != EAGAIN)
        throw std::runtime_error("receive failed");
   if (ret == -1 && errno == EAGAIN)
        ret = 0;
    else
    {
        addr.assign(inet_ntoa(client.sin_addr));
        buffer.setData(buff, static_cast<size_t>(ret));
    }
    delete[] buff;
    return static_cast<size_t>(ret);
}

bool UdpSocket::bind() const
{
    struct sockaddr_in addr;

    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(_port);
    return (::bind(_socket, reinterpret_cast<struct sockaddr *>(&addr),
                   sizeof(addr)) >= 0);
}

short int UdpSocket::getPort() const
{
    return (this->_port);
}

rSocket UdpSocket::getSocket() const
{
    return (this->_socket);
}

void UdpSocket::setPort(short int port)
{
    _port = port;
}

std::string UdpSocket::toString() const
{
    std::string ss;

    ss += "UdpSocket {";
    ss += "\n\tSocket ";
    ss += this->_socket;
    ss += "\n\tPort ";
    ss += this->_port;
    ss += "\n}\n";

    return ss;
}

size_t UdpSocket::send(Buffer const& buffer) const
{
    return BaseSocket::send(buffer);
}

size_t UdpSocket::receive(Buffer& buffer, size_t len) const
{
    return BaseSocket::receive(buffer, len);
}

void UdpSocket::close() const
{
    BaseSocket::close();
}
