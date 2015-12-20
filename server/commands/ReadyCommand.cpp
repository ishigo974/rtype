#include <iostream>
#include "ReadyCommand.hpp"
#include "PlayerComponent.hpp"
#include "RoomComponent.hpp"
#include "PositionComponent.hpp"
#include "NetworkTCP.hpp"
#include "NetworkUDP.hpp"
#include "ComponentsMasks.hpp"
#include "Server.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructor and destructor
        */
        Ready::Ready()
        {
        }

        Ready::~Ready()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Ready::Ready(Ready const& other) : Command::Request(other)
        {
        }

        Ready&  Ready::operator=(Ready const& other)
        {
            if (this != &other)
                Request::operator=(other);
            return *this;
        }

        /*
        ** Public member functions
        */
        void        Ready::initFromRequest(RType::Request const&,
                                           ECS::ASystem*)
        {
        }

        void        Ready::execute()
        {
            Component::Player*      player =
                _entity->getComponent<Component::Player>();
            Component::NetworkTCP*  network =
                _entity->getComponent<Component::NetworkTCP>();
            Component::Room*        room;

            if (player == nullptr || network == nullptr)
                throw std::runtime_error("Entity does not have a \
player/network component");
            if ((room = player->getRoom()) == nullptr
                || !room->setPlayerReadiness(*_entity, true))
                network->send(Server::responseKO);
            else
            {
                RType::Request         request(RType::Request::SE_CLIENTRDY);

                request.push<uint8_t>("player_id", room->getPlayerId(*_entity));
                network->send(Server::responseOK);
                room->broadcastTCP(request.toBuffer(), _entity);
            }
            if (room->allReady())
                startGame(room);
        }

        void        Ready::undo()
        {
        }

        Request*    Ready::clone() const
        {
            return new Ready(*this);
        }


        std::string Ready::getName() const
        {
            return "ReadyCommand";
        }

        /*
        ** Protected member functions
        */
        void        Ready::startGame(Component::Room* room) const
        {
            room->setIsPlaying(true);
            room->broadcastTCP(RType::Request(RType::Request::SE_GAMESTART)
                            .toBuffer());
            for (auto& test: *room)
            {
                Component::NetworkTCP*  tcp = test.second.first
                    ->getComponent<Component::NetworkTCP>();

                test.second.first
                    ->addComponent(std::make_unique<Component::NetworkUDP>(
                        tcp->getIpAddr())
                    );
                test.second.first
                    ->addComponent(std::make_unique<Component::Position>(
                        Component::Room::defaultPositions.at(test.first)
                    ));
            }
            Server::display("Room '" + room->getRoomName() + "' is launching");
        }
    }
}
