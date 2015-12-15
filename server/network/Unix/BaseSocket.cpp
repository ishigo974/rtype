//
// Created by Denis Le Borgne on 14/12/2015.
//

# include <sys/socket.h>
# include <unistd.h>
#include "BaseSocket.hpp"

BaseSocket::BaseSocket()
{ }

BaseSocket::~BaseSocket()
{
    close();
}

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
void BaseSocket::close() const
{
    ::close(_socket);
}
