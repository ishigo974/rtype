//
// Created by Denis Le Borgne on 18/11/2015.
//

#ifndef RTYPE_ISOCKET_HPP
# define RTYPE_ISOCKET_HPP

# include "IBuffer.hpp"

class ISocket
{
public:
    virtual ~ISocket() {}

public:
    virtual size_t send(IBuffer const* buffer) const = 0;
    virtual IBuffer const* recv() const = 0;
    virtual void close() const = 0;
    virtual bool isReadable() const = 0;
    virtual bool isWritable() const = 0;
};

#endif //RTYPE_ISOCKET_HPP
