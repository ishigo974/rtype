//
// Created by Denis Le Borgne on 18/11/2015.
//

#ifndef RTYPE_ISOCKET_HPP
# define RTYPE_ISOCKET_HPP

# include "Buffer.hpp"
# include "IStringable.hpp"
# include "NetTypes.hpp"

class ISocket : public IStringable
{
public:
    virtual ~ISocket()
    { }

public:
    virtual size_t       send(Buffer const *buffer) const = 0;
    virtual Buffer const *recv() const                    = 0;
    virtual void         close() const                    = 0;
    virtual rSocket      getSocket() const                = 0;
};

#endif //RTYPE_ISOCKET_HPP
