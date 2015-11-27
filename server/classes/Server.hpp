#ifndef SERVER_HPP_
# define SERVER_HPP_

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
    Server&       operator=(Server const& other) = delete;

  public:
    void          run();

  protected:
    void          onClientConnection();

  public:
    static const short int    defaultPort;

  protected:
    bool            _quit;
    SocketMonitor   _monitor;
    TcpAcceptor     _acceptor;
  };
}

#endif /* !SERVER_HPP_ */
