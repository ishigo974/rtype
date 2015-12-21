#ifndef RTYPEGAME_HPP_
# define RTYPEGAME_HPP_

# include <string>
# include "EntityManager.hpp"
# include "Behaviour.hpp"
# include "Input.hpp"
# include "Event.hpp"
# include "Renderer.hpp"
# include "BehaviourSystem.hpp"
# include "CommandSystem.hpp"
# include "Menu.hpp"
# include "NetworkSystem.hpp"
# include "UDPSystem.hpp"

class RTypeGame
{
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

public:
    static const double         defaultFixedStep;
    static const std::string    defaultAddr;
    static const short          defaultPort;

protected:
    std::string             _addr;
    short                   _port;
    bool                    _quit;
    bool                    _isPlaying;
    EntityManager           _em;
    Renderer                _renderer;
    Input                   _input;
    BehaviourSystem         _bs;
    CommandSystem           _cs;
    RType::NetworkSystem    _tcpsys;
    RType::UDPSystem        _udpsys;
    cu::Event               _event;
    Menu*                   _menu;
    double                  _lag;
    double                  _fixedStep;
};

#endif /* !RTYPEGAME_HPP_ */
