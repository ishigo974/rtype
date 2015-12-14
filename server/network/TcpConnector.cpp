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
        : _addr(addr), _port(port)
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

void TcpConnector::close() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
    ::close(_socket);
#endif
}

size_t TcpConnector::send(Buffer const& buffer) const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    WSABUF toSend;
    DWORD SendBytes;
    size_t ret;
    std::vector<char> str(buffer.data(), buffer.data() + buffer.size());

    toSend.len = buffer.size();
    toSend.buf = str.data();
    if ((ret = WSASend(_socket, &toSend, 1, &SendBytes, 0, nullptr, nullptr)) == SOCKET_ERROR)
    {
        ;//TODO throw
    }
    return ret;
#else
    ssize_t ret;

    if ((ret = ::send(_socket, buffer.data(), buffer.size(), 0)) < 0)
        throw std::runtime_error("send failed");
    return static_cast<size_t >(ret);
#endif

}

size_t TcpConnector::receive(Buffer& buffer, size_t len) const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    WSABUF wsabuf;
    DWORD read_size = 0;
    DWORD flags = 0;


    wsabuf.buf = new char[len];
    wsabuf.len = len;
    if (::WSARecv(_socket, &wsabuf, 1, &read_size, &flags, nullptr, nullptr)
                  == SOCKET_ERROR)
          {
            delete wsabuf.buf;
            return 0;
          }
        buffer.append(wsabuf.buf, read_size);
        return (read_size);
#else
    ssize_t ret;
    char    *buff = new char[len];

    if ((ret = ::recv(_socket, buff, len, 0)) == -1)
        throw std::runtime_error("receive failed");
    buffer.setData(buff, static_cast<size_t>(ret));
    return static_cast<size_t>(ret);
#endif
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
