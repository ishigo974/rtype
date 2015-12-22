#ifndef MOBSYSTEM_HPP_
# define MOBSYSTEM_HPP_

# include "HRChrono.hpp"
# include "EntityManager.hpp"
# include "MapParser.hpp"

class MobSystem
{
public:
    MobSystem(EntityManager *em, Time::HRChrono const* chrono);
    virtual ~MobSystem();

private:
    MobSystem() = delete;
    MobSystem(MobSystem const& other) = delete;
    MobSystem&      operator=(MobSystem const& other) = delete;

public:
    void            process();
    void            setMap(RType::Map::Parser::Content const& map);
    void            resetMap();

protected:
    EntityManager*              _em;
    Time::HRChrono const*       _chrono;
    RType::Map::Parser::Content _map;
    RType::Map::Parser::Content _current;
};

#endif /* !MOBSYSTEM_HPP_ */
