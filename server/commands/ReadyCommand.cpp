#include <iostream>
#include "ReadyCommand.hpp"
#include "PlayerComponent.hpp"
#include "RoomComponent.hpp"
#include "NetworkTCP.hpp"
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
                _entity->getComponent<Component::Player>(Component::MASK_PLAYER);
            Component::NetworkTCP*  network =
                _entity->getComponent<Component::NetworkTCP>(Component::MASK_NETWORKTCP);
            Component::Room*        room;

            if (player == nullptr || network == nullptr)
                throw std::runtime_error("Entity does not have a \
player/network component");
            if ((room = player->getRoom()) == nullptr
                || !room->setPlayerReadiness(*_entity, true))
                network->send(Server::responseKO);
            else
            {
                Buffer      buffer;

                buffer.append<uint16_t>(RType::Request::SE_CLIENTRDY);
                buffer.append<uint32_t>(sizeof(uint8_t));
                buffer.append<uint8_t>(room->getPlayerId(*_entity));
                network->send(Server::responseOK);
                room->broadcast(buffer, _entity);
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
            Buffer  start;

            start.append<uint16_t>(RType::Request::SE_GAMESTART);
            start.append<uint32_t>(0);
            room->broadcast(start);
        }
    }
}
