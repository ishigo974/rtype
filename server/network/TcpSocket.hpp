//
// Created by Denis Le Borgne on 21/11/2015.
//

#ifndef RTYPE_TCPSOCKET_HPP
#define RTYPE_TCPSOCKET_HPP

# include "Buffer.hpp"
# include "ITcpSocket.hpp"

class TcpSocket : public ITcpSocket
{
public:
    TcpSocket(std::string const& addr, short int port);
    TcpSocket(int socket, std::string const& addr,
              short int port); //TODO typedef
    virtual ~TcpSocket()
    { }

public:
    virtual ssize_t      send(Buffer const *buffer) const;
    virtual Buffer const *recv() const;
    virtual void         close() const;
    virtual bool         isReadable() const;
    virtual bool         isWritable() const;

public:
    virtual void registerToMonitor(fd_set *fdSet) const;
    virtual void deleteFromMonitor(fd_set *fdSet) const;

public:
    int       getSocket() const; //DO TO TYPEDEF FOR SOCKET
    short int getPort() const;
    std::string const& getAddr() const;

    void setPort(short int port);
    void setAddr(std::string const& addr);

private:
    TcpSocket(TcpSocket const& sock) = delete;
    TcpSocket& operator=(TcpSocket const& sock) = delete;

private:
    short int   _port;
    std::string _addr;
    int         _socket;
};

#endif //RTYPE_TCPSOCKET_HPP
