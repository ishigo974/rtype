#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <string>
# include <vector>
# include <unordered_map>
# include <utility>
# include "EntityManager.hpp"
# include "SystemManager.hpp"
# include "SocketMonitor.hpp"
# include "TcpAcceptor.hpp"

namespace RType
{
    class Server : public IStringable
    {
    public:
        typedef std::vector<std::string>    ArgsTab;
        typedef void    (Server::*CLICMDHandler)(ArgsTab const& args);
        typedef std::unordered_map<std::string,
                    std::pair<std::string, CLICMDHandler> >  CLICMDHandlers;

    public:
        Server(short int port = defaultPort);
        virtual ~Server();

    private:
        Server(Server const& other) = delete;
        Server&         operator=(Server const& other) = delete;

    public:
        void            run();
        void            notifyDisconnected(unsigned int id);
        void            readInGameEvents();

    protected:
        void            init();
        void            onClientConnection();
        void            onCLICommand();
        void            checkDisconnected();

    protected:
        void            handleCLIHelp(ArgsTab const& args);
        void            handleCLIRooms(ArgsTab const& args);
        void            handleCLIClients(ArgsTab const& args);
        void            handleCLIQuit(ArgsTab const& args);

    public:
        virtual std::string     toString() const;

    public:
        static void             display(std::string const& msg,
                                        bool err = false);

    protected:
        static Buffer               getResponseOK();
        static Buffer               getResponseKO();

    public:
        static const short int      defaultPort;
        static const Buffer         responseOK;
        static const Buffer         responseKO;
        static const unsigned int   stdinFileNo;
        static const CLICMDHandlers cliCmdHandlers;

    protected:
        short int                   _port;
        bool                        _quit;
        TcpAcceptor                 _acceptor;
        SocketMonitor&              _monitor;
        ECS::EntityManager&         _em;
        ECS::SystemManager&         _sm;
        std::vector<unsigned int>   _disconnected;
    };
}

#endif /* !SERVER_HPP_ */
