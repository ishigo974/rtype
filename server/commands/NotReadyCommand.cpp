#include "NotReadyCommand.hpp"
#include "Player.hpp"
#include "Room.hpp"
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
        NotReady::NotReady()
        {
        }

        NotReady::~NotReady()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        NotReady::NotReady(NotReady const& other) : Command::Request(other)
        {
        }

        NotReady&  NotReady::operator=(NotReady const& other)
        {
            if (this != &other)
                Request::operator=(other);
            return *this;
        }

        /*
        ** Public member functions
        */
        void        NotReady::initFromRequest(RType::Request const&,
                                            ECS::ASystem*)
        {
        }

        void        NotReady::execute()
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
                || !room->setPlayerReadiness(*_entity, false))
                network->send(Server::responseKO);
            network->send(Server::responseOK);
        }

        void        NotReady::undo()
        {
        }

        Request*    NotReady::clone() const
        {
            return new NotReady(*this);
        }


        std::string NotReady::getName() const
        {
            return "NotReadyCommand";
        }
    }
}
