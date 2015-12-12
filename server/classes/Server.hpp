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
        enum Response
        {
            LOBBY_LISTROOMS = 400,
            LOBBY_OK        = 601,
            LOBBY_KO        = 602
        };

    public:
        Server();
        Server(short int port);
        virtual ~Server();

    private:
        Server(Server const& other) = delete;
        Server&         operator=(Server const& other) = delete;

    public:
        void            run();
        void            notifyDisconnected(unsigned int id);

    protected:
        void            init();
        void            onClientConnection();
        void            checkDisconnected();

    public:
        virtual std::string     toString() const;

    public:
        static void             display(std::string const& msg,
                                        bool err = false);

    protected:
        static Buffer           getResponseOK();

    public:
        static const short int      defaultPort;
        static const Buffer         responseOK;

    protected:
        bool                        _quit;
        TcpAcceptor                 _acceptor;
        SocketMonitor&              _monitor;
        ECS::EntityManager&         _em;
        ECS::SystemManager&         _sm;
        std::vector<unsigned int>   _disconnected;
    };
}

#endif /* !SERVER_HPP_ */
