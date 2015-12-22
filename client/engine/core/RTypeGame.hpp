#ifndef RTYPEGAME_HPP_
# define RTYPEGAME_HPP_

# include <memory>
# include <string>
# include <unordered_map>
# include <vector>
# include "EntityManager.hpp"
# include "Behaviour.hpp"
# include "Input.hpp"
# include "Event.hpp"
# include "Renderer.hpp"
# include "BehaviourSystem.hpp"
# include "CommandSystem.hpp"
# include "PhysicsEngine.hpp"
# include "MobSystem.hpp"
# include "Menu.hpp"
# include "NetworkSystem.hpp"
# include "IMobType.hpp"
# include "MapParser.hpp"
# include "AudioEffectPlayer.hpp"
# include "HRChrono.hpp"

class MobSystem;

class RTypeGame
{
public:
    typedef std::unique_ptr<RType::MobType::IMobType>   UniqueMobType;
    typedef std::unordered_map<unsigned int,
                               UniqueMobType>           MobTypeMap;
    typedef std::vector<RType::Map::Parser::Map>        MapCollection;

public:
    RTypeGame(std::string const& addr = defaultAddr,
              short port = defaultPort);
    virtual ~RTypeGame();

public:
    RTypeGame(RTypeGame const& other) = delete;
    RTypeGame&          operator=(RTypeGame const& other) = delete;

public:
    void                run();

protected:
    void                handleGame();
    void                initGameSample();
    void                loadMapsFromFile();
    void                loadMobTypesFromFile();

public:
    static const double         defaultFixedStep;
    static const std::string    defaultAddr;
    static const short          defaultPort;
    static const std::string    mobTypesPath;
    static const std::string    mapsPath;

protected:
    std::string                 _addr;
    short                       _port;
    bool                        _quit;
    bool                        _isPlaying;
    EntityManager               _em;
    Renderer                    _renderer;
    Input                       _input;
    BehaviourSystem             _bs;
    RType::NetworkSystem        _network;
    CommandSystem               _cs;
    cu::Event                   _event;
    Menu*                       _menu;
    double                      _lag;
    double                      _fixedStep;
    MobTypeMap                  _mobTypes;
    MapCollection               _maps;
    Time::HRChrono              _chrono;
    MobSystem                   _ms;
    PhysicsEngine               _physics;
    AudioEffectPlayer           _audio;
};

#endif /* !RTYPEGAME_HPP_ */
