//
// Created by Denis Le Borgne on 21/11/2015.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else

#include <netdb.h>
#include <unistd.h>

#endif

#include <cstring>
#include <iostream>
#include <sstream>
#include "UdpSocket.hpp"

UdpSocket::UdpSocket(short int port)
    : BaseSocket()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        throw std::runtime_error("WSAStartup failed");
    if((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
        throw std::runtime_error("Socket failed");
#else
    if ((_socket = socket(AF_INET, SOCK_DGRAM, getprotobyname("UDP")
            ->p_proto)) == -1)
        throw std::runtime_error("socket failed");
#endif
    _port = port;
}

//#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
//size_t    UdpSocket::send(Buffer const& buffer) const
//{
//    struct sockaddr_in client;
//    WSABUF toSend;
//    DWORD SendBytes;
//    size_t ret;
//    std::vector<char> str(buffer.data(), buffer.data() + buffer.size());
//
//    toSend.len = buffer.size();
//    toSend.buf = str.data();
//    client.sin_family = AF_INET;
//    client.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", &client.sin_addr); //TODO GET IPADDR
//    client.sin_port = _port;
//
//    if ((ret = WSASendTo(_socket, &toSend, 1, &SendBytes, 0,
//    reinterpret_cast<SOCKADDR *>(&client), sizeof(client), nullptr, nullptr))
//            == SOCKET_ERROR)
//        throw std::runtime_error("WSASend failed");
//    return ret;
//    }
//
//size_t    UdpSocket::receive(Buffer& buffer, size_t len) const
//{
//    WSABUF wsabuf;
//    DWORD read_size = 0;
//    DWORD flags = 0;
//    struct sockaddr_in client;
//    int clientSize = sizeof (client);
//
//    wsabuf.buf = new char[len];
//    wsabuf.len = len;
//    if (::WSARecvFrom(_socket, &wsabuf, 1, &read_size, &flags,
//    reinterpret_cast<SOCKADDR *>(&client), &clientSize, nullptr, nullptr)
//                  == SOCKET_ERROR)
//          {
//            delete wsabuf.buf;
//            throw std::runtime_error("WSARecv failed");
//          }
//    buffer.append(wsabuf.buf, read_size);
//    delete wsabuf.buf;
//    //TODO do something with client addr
//    return (read_size);
//}
//#else
//
//size_t        UdpSocket::send(Buffer const& buffer) const
//{
//    ssize_t ret;
//    //TODO CHANGE TO SENDTO
//
//    if ((ret = ::send(_socket, buffer.data(), buffer.size(), 0)) == -1)
//        throw std::runtime_error("send failed");
//    return (static_cast<size_t>(ret));
//}
//
//size_t        UdpSocket::receive(Buffer& buffer, size_t len) const
//{
//    ssize_t ret;
//    char    *buff = new char[len];
//
//    //TODO CHANGE TO RECEVFROM
//    if ((ret = ::recv(_socket, buff, len, 0)) == -1)
//        throw std::runtime_error("receive failed");
//    buffer.setData(buff, static_cast<size_t>(ret));
//    return static_cast<size_t>(ret);
//
//}
//
//#endif


bool UdpSocket::bind() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(_port);
    if(::bind(_socket, reinterpret_cast<struct sockaddr *>(&server),
             sizeof(server)) == SOCKET_ERROR)
        throw std::runtime_error("bind failed");
    return true;
#else
    struct sockaddr_in addr;

    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(_port);

    return (::bind(_socket, reinterpret_cast<struct sockaddr *>(&addr),
                   sizeof(addr)) >= 0);
#endif
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
    std::ostringstream ss;

    ss << "UdpSocket {"
    << "\n\tSocket " << this->_socket
    << "\n\tPort " << this->_port
    << "\n}" << std::endl;

    return ss.str();
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
