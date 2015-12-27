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
# include "Menu.hpp"
# include "NetworkSystem.hpp"
# include "IMobType.hpp"
# include "MapParser.hpp"
# include "AudioEffectPlayer.hpp"
# include "HRChrono.hpp"
# include "GameManagerBehaviour.hpp"

class MobSystem;

class RTypeGame
{
public:
    typedef std::unique_ptr<RType::MobType::IMobType>   UniqueMobType;
    typedef std::unordered_map<unsigned int,
                               UniqueMobType>           MobTypeMap;

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
    void                initGame();
    void                initGameSample();
    void                loadMobTypesFromFile();

public:
    static const std::string    defaultAddr;
    static const short          defaultPort;
    static const std::string    mobTypesPath;

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
    Time::HRChrono              _chrono;
    PhysicsEngine               _physics;
    AudioEffectPlayer           _audio;
    GameManagerBehaviour*       _gmb;
};

#endif /* !RTYPEGAME_HPP_ */
