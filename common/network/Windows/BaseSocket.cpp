
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
    WSABUF             toSend;
    DWORD              SendBytes;
    size_t             ret;
    std::vector<char>  buff(buffer.data(), buffer.data() + buffer.size());

    toSend.len             = buffer.size();
    toSend.buf             = buff.data();

	if ((ret = ::WSASend(_socket, &toSend, 1, &SendBytes, 0, nullptr, nullptr))
		== SOCKET_ERROR)
		throw std::runtime_error("WSASend failed");
	return SendBytes;
}

size_t    BaseSocket::receive(Buffer& buffer, size_t len) const
{
    WSABUF             wsabuf;
    DWORD              read_size  = 0;
    DWORD              flags      = 0;

    wsabuf.buf = new char[len];
    wsabuf.len = len;
    if (::WSARecv(_socket, &wsabuf, 1, &read_size, &flags, nullptr, nullptr)
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
