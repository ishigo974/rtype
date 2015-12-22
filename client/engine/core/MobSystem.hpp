#ifndef MOBSYSTEM_HPP_
# define MOBSYSTEM_HPP_

# include "HRChrono.hpp"
# include "EntityManager.hpp"
# include "MapParser.hpp"
# include "IMobType.hpp"

/*
** tmp ; will be moved to the server
*/
class MobSystem
{
public:
    typedef std::unique_ptr<RType::MobType::IMobType>   UniqueMobType; // tmp
    typedef std::unordered_map<unsigned int,
                               UniqueMobType>           MobTypeMap; // tmp

public:
    MobSystem(EntityManager *em, Time::HRChrono const* chrono,
              MobTypeMap* mobTypes);
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
    MobTypeMap*                 _mobTypes;
};

#endif /* !MOBSYSTEM_HPP_ */
