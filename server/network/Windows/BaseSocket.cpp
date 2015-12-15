//
// Created by Denis Le Borgne on 14/12/2015.
//


#include "BaseSocket.hpp"

BaseSocket::BaseSocket()
{ }

BaseSocket::~BaseSocket()
{
    close();
}

size_t    BaseSocket::send(Buffer const& buffer) const
{
    struct sockaddr_in client;
    WSABUF toSend;
    DWORD SendBytes;
    size_t ret;
    std::vector<char> str(buffer.data(), buffer.data() + buffer.size());

    toSend.len = buffer.size();
    toSend.buf = str.data();
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", &client.sin_addr);
    client.sin_port = _port;

    if ((ret = WSASendTo(_socket, &toSend, 1, &SendBytes, 0,
    reinterpret_cast<SOCKADDR *>(&client), sizeof(client), nullptr, nullptr))
            == SOCKET_ERROR)
        throw std::runtime_error("WSASend failed");
    return ret;
    }

size_t    BaseSocket::receive(Buffer& buffer, size_t len) const
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
    return (read_size);
}

void BaseSocket::close() const
{
    closesocket(_socket);
}
