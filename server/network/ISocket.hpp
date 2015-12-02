//
// Created by Denis Le Borgne on 18/11/2015.
//

#ifndef RTYPE_ISOCKET_HPP
# define RTYPE_ISOCKET_HPP

# include "Buffer.hpp"
# include "IStringable.hpp"
# include "IMonitorable.hpp"

class ISocket : public IStringable, public IMonitorable
{
public:
    virtual ~ISocket()
    { }

public:
    virtual void   close() const                             = 0;
    virtual size_t send(Buffer& buffer) const                = 0;
    virtual size_t receive(Buffer& buffer, size_t len) const = 0;

public:
    virtual short int getPort() const = 0;
    virtual std::string const& getAddr() const = 0;
};

#endif //RTYPE_ISOCKET_HPP
