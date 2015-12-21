#include "RTypeGame.hpp"
#include "Menu.hpp"
#include "PlayerObject.hpp"
#include "ScrollingBackground.hpp"

/*
** Static variables
*/
const double        RTypeGame::defaultFixedStep = 0.003;
const std::string   RTypeGame::defaultAddr      = "127.0.0.1";
const short         RTypeGame::defaultPort      = 6667;

/*
** Constructor/Destructor
*/
RTypeGame::RTypeGame(std::string const& addr, short port) :
    _addr(addr), _port(port),
    _quit(false), _isPlaying(false), _em(), _renderer(&_em),
    _input(_renderer.getWindow()), _bs(&_em), _cs(&_em, &_input),
    _tcpsys(&_em, addr, port), _udpsys(&_em, addr, port + 1),
    _event(), _menu(nullptr), _lag(0), _fixedStep(defaultFixedStep)
{
    GameObject*     entity;

    BigBen::getElapsedtime();
    entity = _em.createEntity<GameObject>("Network", 1);

    _em.attachComponent<RType::NetworkTCP>(entity, "TCP");
    _em.attachComponent<RType::NetworkUDP>(entity, "UDP");

    _menu = _em.createEntity<Menu>("Niquez-vos-races-Type", 1, &_em, &_event,
                                    entity->getComponent<RType::NetworkTCP>());
    _menu->init();
    _renderer.init();

}

RTypeGame::~RTypeGame()
{
}

/*
** Public member functions
*/
void        RTypeGame::run()
{
    // initGameSample();
    while (!_quit)
    {
        if (!_isPlaying)
            _menu->move();
        else
            handleGame();
        _renderer.render();
        _tcpsys.process();
        _input.pollEvent(_event);
        if (_event.type == cu::Event::Closed
            || _event.key == cu::Event::ESCAPE)
        {
            _quit = true;
            break ;
        }
    }
}

/*
** Protected member functions
*/
void        RTypeGame::initGameSample()
{
    PlayerObject *player = _em.createEntity<PlayerObject>("Player", 1, &_em);
    player->init();
    GameObject *first = _em.createEntity<GameObject>("LePremier", 0);
    GameObject *bg = _em.createEntity<GameObject>("bg", -1);

    _em.attachComponent<SpriteRenderer>(first, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));

    _em.attachComponent<SpriteRenderer>(bg, "bg", "bg1", gu::Rect<int>(0, 0, 1280, 720));
    _em.attachComponent<ScrollingBackground>(bg, "Background", 0.25);
}

void        RTypeGame::handleGame()
{
    _lag = BigBen::getElapsedtime();
    _cs.process();
    while (_lag >= _fixedStep)
    {
        _bs.process(_lag / _fixedStep);
        _lag -= _fixedStep;
    }
}
