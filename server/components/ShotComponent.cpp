#include "ShotComponent.hpp"
#include "PositionComponent.hpp"
#include "ComponentsMasks.hpp"
#include "EntityManager.hpp"
#include "GameConfig.hpp"
#include "GameComponent.hpp"
#include "PlayerComponent.hpp"
#include "GameConfig.hpp"
#include "Server.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const ECS::ComponentMask    Shot::mask      = Component::MASK_SHOT;

        /*
        ** Constructor/Destructor
        */
        Shot::Shot(RType::Shot::Type type, ECS::Entity* owner,
                    Component::Game* game) :
            _type(type), _owner(owner), _game(game)
        {
        }

        Shot::~Shot()
        {
        }

        /*
        ** Copy constructor/Assign operator
        */
        Shot::Shot(Shot const& other) : _type(other._type), _owner(other._owner)
        {
        }

        Shot&               Shot::operator=(Shot const& other)
        {
            if (this != &other)
            {
                _type = other._type;
                _owner = other._owner;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void                Shot::update()
        {
            ECS::EntityManager&     em = ECS::EntityManager::getInstance();
            Component::Position*    pos =
                em.getByCmpnt(this).getComponent<Component::Position>();

            if (pos == nullptr)
                return ;
            switch (_type)
            {
                case RType::Shot::NORMAL:
                    pos->setX(pos->getX() + (Speed::bullet * Server::lag));
                    break ;
                default:
                    break ;
            }
            if (pos->getX() <= 0 || pos->getX() >= Map::width
                || pos->getY() <= 0 || pos->getY() >= Map::height)
            {
                ECS::EntityManager& em = ECS::EntityManager::getInstance();

                em.safeDestroy(em.getByCmpnt(this));
            }
        }

        void                Shot::collide(ECS::Entity&)
        {
            ECS::EntityManager& em = ECS::EntityManager::getInstance();

            em.safeDestroy(em.getByCmpnt(this));
        }

        RType::Shot::Type   Shot::getType() const
        {
            return _type;
        }

        void                Shot::setType(RType::Shot::Type type)
        {
            _type = type;
        }

        ECS::Entity*        Shot::getOwner() const
        {
            return _owner;
        }

        void                Shot::setOwner(ECS::Entity* owner)
        {
            _owner = owner;
        }

        void                Shot::setGame(Component::Game* game)
        {
            _game = game;
        }

        Component::Game*    Shot::getGame() const
        {
            return _game;
        }

        std::string         Shot::getName() const
        {
            return "ShotComponent";
        }

        ECS::ComponentMask  Shot::getMask() const
        {
            return mask;
        }

        ECS::IComponent*    Shot::clone() const
        {
            return new Shot(*this);
        }

        void                Shot::clear()
        {
            _type = RType::Shot::NORMAL;
        }

        std::string         Shot::toString() const
        {
            return "ShotComponent {\n\t_type: " +
                   std::to_string(static_cast<int>(_type)) + "}\n";
        }
    }
}
