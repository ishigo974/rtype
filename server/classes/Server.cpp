// Standards includes
#include <thread>
#include <memory>
#include <functional>
#include <iostream>
#include <fstream>
#include "DLLoader.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
# ifndef STDIN_FILENO
#  define STDIN_FILENO 0
# endif
#else
# include <unistd.h>
#endif

// Server/Misc includes
#include "Server.hpp"
#include "Request.hpp"
#include "ITcpSocket.hpp"

// Entities related includes
#include "Entity.hpp"
#include "EntityManager.hpp"

// Systems related includes
#include "SystemManager.hpp"
#include "LobbySystem.hpp"
#include "InGameSystem.hpp"
#include "ShotFiringSystem.hpp"

// Components related includes
#include "IComponent.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkTCP.hpp"
#include "NetworkUDP.hpp"
#include "RoomComponent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "ShotComponent.hpp"
#include "MobComponent.hpp"

// Exceptions includes
#include "NotImplemented.hpp"
#include "InvalidRequest.hpp"

namespace RType
{
    /*
    ** Static variables
    */
    const short int     Server::defaultPort     = 6667;
    const Buffer        Server::responseOK      = Server::getResponseOK();
    const Buffer        Server::responseKO      = Server::getResponseKO();
    const unsigned int  Server::stdinFileNo     = STDIN_FILENO;
    const std::string   Server::mobTypesPath    = ".rtypemobs";

    const Server::CLICMDHandlers    Server::cliCmdHandlers =
    {
        { "users",  { "list connected users",   &Server::handleCLIClients } },
        { "rooms",  { "list rooms",             &Server::handleCLIRooms } },
        { "quit",   { "shutdown server",        &Server::handleCLIQuit } },
        { "help",   { "displays infos about how to use the server's CLI",
                      &Server::handleCLIHelp } },
    };

    /*
    ** Constructors/Destructor
    */
    Server::Server(short int port) :
        _port(port),
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
        std::thread     inGameHandler(std::bind(&Server::readInGameEvents,
                                                this));

        while (!_quit)
        {
            try {
                _monitor.update();
                if (_monitor.isReadable(stdinFileNo))
                    onCLICommand();
                if (_monitor.isReadable(&_acceptor))
                    onClientConnection();
                _em.updateAll();
                _sm.processAll();
                checkDisconnected();
            } catch (Exception::NotImplemented const& e) {
                display(std::string(e.what()), true);
            } catch (Exception::InvalidRequest const& /*e*/) {
                // TODO handle
            } catch (...) {
                _quit = true;
                display("Waiting for InGameHandler thread");
                inGameHandler.join();
                throw ;
            }
        }
        display("Waiting for InGameHandler thread");
        inGameHandler.join();
        display("Server is shutting down");
    }

    void            Server::notifyDisconnected(unsigned int id)
    {
        _disconnected.push_back(id);
    }

    void            Server::readInGameEvents()
    {
        try {
            while (!_quit)
                _sm.update(Component::MASK_NETWORKUDP);
        } catch (std::exception const& e) {
            display("Fatal error: " + std::string(e.what()), true);
            _quit = true;
        } catch (...) {
            display("Unexpected internal error", true);
            _quit = true;
        }
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
        _monitor.registerRaw(stdinFileNo);

        _em.registerComponent(std::make_unique<Component::NetworkTCP>());
        _em.registerComponent(std::make_unique<Component::NetworkUDP>());
        _em.registerComponent(std::make_unique<Component::Room>());
        _em.registerComponent(std::make_unique<Component::Player>());
        _em.registerComponent(std::make_unique<Component::Position>());
        _em.registerComponent(std::make_unique<Component::Shot>());
        _em.registerComponent(std::make_unique<Component::Mob>());

        _sm.registerSystem(std::make_unique<System::Lobby>());
        _sm.registerSystem(std::make_unique<System::InGame>(_port + 1));
        _sm.registerSystem(std::make_unique<System::ShotFiring>());

        loadMobTypesFromFile();

        display("Server is now running on port " +
                std::to_string(_acceptor.getPort()));
    }

    void            Server::loadMobTypesFromFile()
    {
        std::ifstream   file(mobTypesPath.c_str());
        std::string     line;

        if (!file)
        {
            Server::display("Configuration file '" + mobTypesPath + "' was "
                            "not found, can't load mobs types");
            return ;
        }
        while (std::getline(file, line))
        {
            std::ifstream   mobFile(line.c_str());
            IMobType*       mobType = nullptr;

            if (line.empty())
                continue ;
            try {
                if (mobFile.good())
                {
                    mobType = DLLoader<IMobType*>::getInstanceOf(line,
                                                                 "getMobType");
                    _mobTypeFactory.learn(std::unique_ptr<IMobType>(mobType));
                    Server::display("Mob '" + mobType->getName() + "' loaded");
                }
                else
                    Server::display("Can't load mob type: No such file: " +
                                    line);
                mobFile.close();
            } catch (std::runtime_error const&) {
            }
        }
        file.close();
    }

    void            Server::checkDisconnected()
    {
        for (auto& id: _disconnected)
            ECS::EntityManager::getInstance().destroy(id);
        _disconnected.clear();
    }

    /*
    ** Events callbacks
    */
    void            Server::onClientConnection()
    {
        Component::NetworkTCP*  network;
        ITcpSocket*             socket = _acceptor.accept();
        ECS::Entity&            entity =
            _em.create(Component::MASK_NETWORKTCP | Component::MASK_PLAYER);

        network = entity.getComponent<Component::NetworkTCP>();
        if (network == nullptr)
            throw std::runtime_error("NetworkTCP component not found");
        network->setSocket(std::unique_ptr<ITcpSocket>(socket));
        network->setEntityId(entity.getId());
        network->setOnDisconnect(std::bind(&Server::notifyDisconnected,
                                            this, std::placeholders::_1));
        _monitor.registerSocket(socket);
		display("New connection from " + socket->getAddr() + ":" +
                std::to_string(socket->getPort()));
    }

    void            Server::onCLICommand()
    {
        std::string                     cmd;
        std::string                     tmp;
        ArgsTab                         args;
        std::stringstream               stream;
        CLICMDHandlers::const_iterator  it;

        getline(std::cin, tmp);
        if (!std::cin)
            _quit = true;
        if (!std::cin || tmp.empty())
            return ;
        stream.str(tmp);
        std::getline(stream, cmd, ' ');
        if ((it = cliCmdHandlers.find(cmd)) != cliCmdHandlers.end())
        {
            while (getline(stream, tmp, ' '))
                args.push_back(tmp);
            (this->*it->second.second)(args);
        }
        else
            Server::display("No command \"" + cmd + "\" ; "
                            "use \"help\" to get all available events");
    }

    /*
    ** CLI handlers
    */
    void            Server::handleCLIHelp(ArgsTab const&)
    {
        Server::display("Command Line Interface (CLI) usage :");
        for (auto& cmd: cliCmdHandlers)
            Server::display(cmd.first + "\t\t-- " + cmd.second.first);
    }

    void            Server::handleCLIRooms(ArgsTab const&)
    {
        ECS::EntityCollection   rooms = _em.getByMask(Component::MASK_ROOM);

        if (rooms.empty())
            Server::display("No rooms yet");
        else
            Server::display("Name\t| Slots\t| Players - r: "
                            "ready, n: not ready");
        for (auto& entry: rooms)
        {
            Component::Room* room =
                entry->getComponent<Component::Room>();

            if (room == nullptr)
                throw std::runtime_error("EntityManager: Retrieving entities by"
                                         " mask failed");
            Server::display(room->getRoomName() + "\t| " +
                            std::to_string(room->size()) + "/" +
                            std::to_string(Component::Room::nbMaxPlayers) +
                            "\t| " + room->getPlayersNames());
        }
    }

    void            Server::handleCLIClients(ArgsTab const&)
    {
        ECS::EntityCollection   clients =
            _em.getByMask(Component::MASK_NETWORKTCP);

        if (clients.empty())
            Server::display("No clients yet");
        else
            Server::display("Username\t| ip:port\t\t| Room");
        for (auto& entry: clients)
        {
            Component::Player*      player =
                entry->getComponent<Component::Player>();
            Component::NetworkTCP*  network =
                entry->getComponent<Component::NetworkTCP>();

            if (player == nullptr || network == nullptr)
                throw std::runtime_error("EntityManager: Retrieving entities by"
                                         " mask failed");
            Server::display(player->getUsername() + "\t| " + network->repr() +
                            "\t| " + (player->getRoom() != nullptr ?
                                      player->getRoom()->getRoomName() : ""));
        }
    }

    void            Server::handleCLIQuit(ArgsTab const&)
    {
        _quit = true;
    }

    /*
    ** Static functions
    */
    void            Server::display(std::string const& msg, bool err)
    {
        if (!err)
            std::cout << "| " << msg << std::endl;
        else
            std::cerr << "| " << msg << std::endl;
    }

    Buffer          Server::getResponseOK()
    {
        Buffer      res;

        res.append<uint16_t>(Request::SE_OK);
        res.append<uint32_t>(0);
        return res;
    }

    Buffer          Server::getResponseKO()
    {
        Buffer      res;

        res.append<uint16_t>(Request::SE_KO);
        res.append<uint32_t>(0);
        return res;
    }
}
