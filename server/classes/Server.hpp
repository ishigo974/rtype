#ifndef SERVER_HPP_
# define SERVER_HPP_

# include "EntityManager.hpp"
# include "SystemManager.hpp"
# include "SocketMonitor.hpp"
# include "TcpAcceptor.hpp"

namespace RType
{
    class Server : public IStringable
    {
    public:
        Server();
        Server(short int port);
        virtual ~Server();

    private:
        Server(Server const& other) = delete;
        Server&         operator=(Server const& other) = delete;

    public:
        void            run();

    protected:
        void            init();
        void            onClientConnection();

    public:
        virtual std::string     toString() const;

    public:
        static void   display(std::string const& msg, bool err = false);

    public:
        static const short int    defaultPort;

    protected:
        bool                    _quit;
        TcpAcceptor             _acceptor;
        SocketMonitor&          _monitor;
        ECS::EntityManager&     _em;
        ECS::SystemManager&     _sm;
    };
}

#endif /* !SERVER_HPP_ */
