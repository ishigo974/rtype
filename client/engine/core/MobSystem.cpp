#include "MobSystem.hpp"
#include "RTypeGame.hpp"
#include "Mob.hpp"
#include "Collider.hpp"

MobSystem::MobSystem(EntityManager *em, Time::HRChrono const* chrono,
                     RTypeGame::MobTypeMap* mobTypes) :
    _em(em), _chrono(chrono), _mobTypes(mobTypes)
{
}

MobSystem::~MobSystem()
{
}

void            MobSystem::process()
{
    if (_map.empty())
        return ;
    for (auto it = _map.begin(); it != _map.end(); ++it)
    {
        if ((it->first * 1000000) <= _chrono->getElapsedTime())
        {
            GameObject *first = _em->createEntity<GameObject>("LePremier", 0);

            _em->attachComponent<SpriteRenderer>(first, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
            _em->attachComponent<Mob>(first, "SR compo", _mobTypes->begin()->second.get());
            _em->attachComponent<Collider>(first, "SR compo", 32, 21);
            first->getComponent<Transform>()->getPosition().setX(it->second.x);
            first->getComponent<Transform>()->getPosition().setY(it->second.y);
            if ((it = _map.erase(it)) == _map.end())
                break ;
        }
        else
            break ;
    }
    if (_map.empty())
        std::cout << "end of map" << std::endl; // TODO end of game
}

void            MobSystem::setMap(RType::Map::Parser::Content const& map)
{
    _map = map;
    _current = _map;
}

void            MobSystem::resetMap()
{
    _current = _map;
}
