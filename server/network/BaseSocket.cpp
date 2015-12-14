//
// Created by Denis Le Borgne on 13/12/2015.
//

#include <sys/socket.h>
#include "BaseSocket.hpp"

BaseSocket::BaseSocket()
{ }

BaseSocket::~BaseSocket()
{
    close();
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
size_t    UdpSocket::send(Buffer const& buffer) const
{
    struct sockaddr_in client;
    WSABUF toSend;
    DWORD SendBytes;
    size_t ret;
    std::vector<char> str(buffer.data(), buffer.data() + buffer.size());

    toSend.len = buffer.size();
    toSend.buf = str.data();
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", &client.sin_addr); //TODO GET IPADDR
    client.sin_port = _port;

    if ((ret = WSASendTo(_socket, &toSend, 1, &SendBytes, 0,
    reinterpret_cast<SOCKADDR *>(&client), sizeof(client), nullptr, nullptr))
            == SOCKET_ERROR)
        throw std::runtime_error("WSASend failed");
    return ret;
    }

size_t    UdpSocket::receive(Buffer& buffer, size_t len) const
{
    WSABUF wsabuf;
    DWORD read_size = 0;
    DWORD flags = 0;
    struct sockaddr_in client;
    int clientSize = sizeof (client);

    wsabuf.buf = new char[len];
    wsabuf.len = len;
    if (::WSARecvFrom(_socket, &wsabuf, 1, &read_size, &flags,
    reinterpret_cast<SOCKADDR *>(&client), &clientSize, nullptr, nullptr)
                  == SOCKET_ERROR)
          {
            delete wsabuf.buf;
            throw std::runtime_error("WSARecv failed");
          }
    buffer.append(wsabuf.buf, read_size);
    delete wsabuf.buf;
    //TODO do something with client addr
    return (read_size);
}
#else

size_t        BaseSocket::send(Buffer const& buffer) const
{
    ssize_t ret;

    if ((ret = ::send(_socket, buffer.data(), buffer.size(), 0)) == -1)
        throw std::runtime_error("send failed");
    return (static_cast<size_t>(ret));
}

size_t        BaseSocket::receive(Buffer& buffer, size_t len) const
{
    ssize_t ret;
    char    *buff = new char[len];

    if ((ret = ::recv(_socket, buff, len, 0)) == -1)
        throw std::runtime_error("receive failed");
    buffer.setData(buff, static_cast<size_t>(ret));
    return static_cast<size_t>(ret);

}

#endif

void BaseSocket::close() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    closesocket(_socket);
#else
    ::close(_socket);
#endif
}