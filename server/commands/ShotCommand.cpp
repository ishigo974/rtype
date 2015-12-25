#include "PlayerComponent.hpp"
#include "ComponentsMasks.hpp"
#include "ShotCommand.hpp"
#include "ShipComponent.hpp"
#include "RoomComponent.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructor/Destructor
        */
        Shot::Shot() : _isFiring(false), _type(Component::Shot::NORMAL)
        {
        }

        Shot::~Shot()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Shot::Shot(Shot const& other) :
            Event(other), _isFiring(other._isFiring),
            _type(other._type), _time(other._time)
        {
        }

        Shot&                   Shot::operator=(Shot const& other)
        {
            if (this != &other)
            {
                Event::operator=(other);
                _isFiring = other._isFiring;
                _type = other._type;
                _time = other._time;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void            Shot::initFromEvent(InGameEvent const& event)
        {
            if (event.getCode() != InGameEvent::CL_SHOTSTART
                && event.getCode() != InGameEvent::CL_SHOTSTOP)
                throw std::runtime_error("Can't build Command::Shot "
                                         "from event: Invalid code " +
                                         std::to_string(event.getCode()));
            _isFiring = (event.getCode() == InGameEvent::CL_SHOTSTART);
            _type = static_cast<Component::Shot::Type>(
                event.get<uint8_t>("shot_type"));
            _time = event.get<uint64_t>("time");
        }

        Event*          Shot::clone() const
        {
            return new Shot(*this);
        }

        void            Shot::execute()
        {
            Component::Ship*    ship =
                _entity->getComponent<Component::Ship>();
            Component::Player*  player =
                _entity->getComponent<Component::Player>();
            Component::Room*    room;
            InGameEvent         event(_isFiring ? InGameEvent::SE_SHOTSTART :
                                                  InGameEvent::SE_SHOTSTOP);

            if (ship == nullptr || player == nullptr
                || (room = player->getRoom()) == nullptr)
                throw std::runtime_error("Entity does not have a "
                                         "Ship/Room/Player component");
            ship->setIsFiring(_isFiring);
            ship->setShotType(_type);
            event.push<uint8_t>("player_id", room->getPlayerId(*_entity));
            event.push<uint8_t>("shot_type", _type);
            event.push<uint64_t>("time", _time);
            room->broadcastUDP(event.toBuffer(), _entity);
        }

        void            Shot::undo()
        {
        }

        std::string     Shot::getName() const
        {
            return "ShotCommand";
        }
    }
}
