//
// Created by Denis Le Borgne on 13/12/2015.
//

#ifndef RTYPE_SERVER_NETWORKUT_HPP
#define RTYPE_SERVER_NETWORKUT_HPP

# include <string>
# include "ABaseUT.hpp"
# include "TcpConnector.hpp"
# include "TcpAcceptor.hpp"
# include "SocketMonitor.hpp"

class NetworkUT : public UnitTesting::ABaseUT
{
public:
    NetworkUT()
    { }

    virtual ~NetworkUT()
    { }

public:
    virtual void        registerTests();
    virtual std::string getName() const;

protected:
    static void simpleServerConnect();
    static void multipleServerConnect();
    static void simpleUpdate();
    static void sendMonitor();
};


#endif //RTYPE_SERVER_NETWORKUT_HPP
