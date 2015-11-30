#include <iostream>
#include "Server.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "ITcpSocket.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkTCP.hpp"

namespace RType
{
  /*
  ** Static variables
  */
  const short int       Server::defaultPort   = 6667;

  /*
  ** Constructors/Destructor
  */
  Server::Server() : _quit(false), _monitor(), _acceptor(Server::defaultPort)
  {
    _monitor.registerSocket(&_acceptor);
  }

  Server::Server(short int port) : _quit(false), _monitor(), _acceptor(port)
  {
    _monitor.registerSocket(&_acceptor);
  }

  Server::~Server()
  {
  }

  /*
  ** Public member functions
  */
  void          Server::run()
  {
    display("Server is now running on port " +
            std::to_string(_acceptor.getPort()) + ")");
    while (!_quit)
    {
      _monitor.update();
      if (_monitor.isReadable(&_acceptor))
        onClientConnection();
    }
  }

  std::string   Server::toString() const
  {
    return std::to_string(_acceptor.getPort()); // TODO
  }

  /*
  ** Protected member functions
  */
  void          Server::onClientConnection()
  {
    ITcpSocket*      socket = _acceptor.accept();
    ECS::Entity&     entity = ECS::EntityManager::getInstance()
                                .create(Component::MASK_NETWORKTCP);

    entity.getComponent<Component::NetworkTCP>(Component::MASK_NETWORKTCP)
          ->setSocket(std::unique_ptr<ITcpSocket>(socket));
    display("New connection from " + socket->getAddr() + " " +
            std::to_string(socket->getPort()));
  }

  /*
  ** Static functions
  */
  void          Server::display(std::string const& msg)
  {
    std::cout << "| " << msg << std::endl;
  }
}
