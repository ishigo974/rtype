#include "QuitRoomCommand.hpp"
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
        QuitRoom::QuitRoom()
        {
        }

        QuitRoom::~QuitRoom()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        QuitRoom::QuitRoom(QuitRoom const& other) : Command::Request(other)
        {
        }

        QuitRoom&  QuitRoom::operator=(QuitRoom const& other)
        {
            if (this != &other)
                Request::operator=(other);
            return *this;
        }

        /*
        ** Public member functions
        */
        void        QuitRoom::initFromRequest(RType::Request const&,
                                              ECS::ASystem*)
        {
        }

        void        QuitRoom::execute()
        {
            Component::Player*      player =
                _entity->getComponent<Component::Player>(Component::MASK_PLAYER);
            Component::NetworkTCP*  network =
                _entity->getComponent<Component::NetworkTCP>(Component::MASK_NETWORKTCP);
            Component::Room*        room;

            if (player == nullptr || network == nullptr)
                throw std::runtime_error("Entity does not have a \
player/network component");
            if ((room = player->getRoom()) == nullptr)
                network->send(Server::responseKO);
            else
            {
                Buffer      buffer;

                buffer.append<uint16_t>(RType::Request::SE_QUITROOM);
                buffer.append<uint32_t>(sizeof(uint8_t));
                buffer.append<uint8_t>(room->getPlayerId(*_entity));
                room->removePlayer(*_entity);
                player->setRoom(nullptr);
                network->send(Server::responseOK);
                room->broadcast(buffer, _entity);
            }
        }

        void        QuitRoom::undo()
        {
        }

        Request*    QuitRoom::clone() const
        {
            return new QuitRoom(*this);
        }


        std::string QuitRoom::getName() const
        {
            return "QuitRoomCommand";
        }
    }
}