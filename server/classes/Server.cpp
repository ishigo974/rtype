#include <memory>
#include <iostream>
#include "Server.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "ITcpSocket.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkTCP.hpp"
#include "Room.hpp"
#include "IComponent.hpp"
#include "LobbySystem.hpp"
#include "NotImplemented.hpp"
#include "InvalidRequest.hpp"

namespace RType
{
    /*
    ** Static variables
    */
    const short int         Server::defaultPort     = 6667;
    const Buffer            Server::responseOK      = Server::getResponseOK();

    /*
    ** Constructors/Destructor
    */
    Server::Server() :
        _quit(false), _acceptor(Server::defaultPort),
        _monitor(SocketMonitor::getInstance()),
        _em(ECS::EntityManager::getInstance()),
        _sm(ECS::SystemManager::getInstance())
    {
        init();
    }

    Server::Server(short int port) :
        _quit(false), _acceptor(port),
        _monitor(SocketMonitor::getInstance()),
        _em(ECS::EntityManager::getInstance()),
        _sm(ECS::SystemManager::getInstance())
    {
        init();
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
                std::to_string(_acceptor.getPort()));
        while (!_quit)
        {
            try {
                _monitor.update();
                if (_monitor.isReadable(&_acceptor))
                    onClientConnection();
                _em.updateAll();
                _sm.processAll();
                checkDisconnected();
            } catch (Exception::NotImplemented const& e) {
                display(std::string(e.what()), true);
            } catch (Exception::InvalidRequest const& /*e*/) {
                // TODO handle
            }
            // TODO add exceptions
        }
    }

    void            Server::notifyDisconnected(unsigned int id)
    {
        _disconnected.push_back(id);
    }

    std::string     Server::toString() const
    {
        return std::to_string(_acceptor.getPort()); // TODO
    }

    /*
    ** Protected member functions
    */
    void            Server::init()
    {
        _monitor.registerSocket(&_acceptor);
        _em.registerComponent(std::make_unique<Component::NetworkTCP>());
        _em.registerComponent(std::make_unique<Component::Room>());
        _sm.registerSystem(std::make_unique<System::Lobby>());
    }

    void            Server::onClientConnection()
    {
        Component::NetworkTCP*  network;
        ITcpSocket*             socket = _acceptor.accept();
        ECS::Entity&            entity =
            _em.create(Component::MASK_NETWORKTCP | Component::MASK_PLAYER);

        network = entity
            .getComponent<Component::NetworkTCP>(Component::MASK_NETWORKTCP);
        if (network == nullptr)
            throw std::runtime_error("NetworkTCP component not found");
        network->setSocket(std::unique_ptr<ITcpSocket>(socket));
        network->setEntityId(entity.getId());
        _monitor.registerSocket(socket);
		display("New connection from " + socket->getAddr() + ":" +
                std::to_string(socket->getPort()));
    }

    void            Server::checkDisconnected()
    {
        for (auto& id: _disconnected)
            ECS::EntityManager::getInstance().destroy(id);
    }

    /*
    ** Static functions
    */
    void            Server::display(std::string const& msg, bool err)
    {
        if (err)
            std::cout << "| " << msg << std::endl;
        else
            std::cerr << "| " << msg << std::endl;
    }

    Buffer          Server::getResponseOK()
    {
        Buffer      res;

        res.append<uint16_t>(LOBBY_OK);
        res.append<uint32_t>(0);
        return res;
    }
}
