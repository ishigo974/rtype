#include "MobSystem.hpp"

MobSystem::MobSystem(EntityManager *em, Time::HRChrono const* chrono) :
    _em(em), _chrono(chrono)
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
