#include <fstream>
#include "RTypeGame.hpp"
#include "Menu.hpp"
#include "PlayerObject.hpp"
#include "ScrollingBackground.hpp"
#include "DLLoader.hpp"
#include "Mob.hpp"
#include "Collider.hpp"
#include "AudioEffect.hpp"
#include "TCPView.hpp"
#include "UDPView.hpp"

/*
** Static variables
*/
const double        RTypeGame::defaultFixedStep = 0.003;
const std::string   RTypeGame::defaultAddr      = "127.0.0.1";
const short         RTypeGame::defaultPort      = 6667;
const std::string   RTypeGame::mapsPath         = ".rtypemaps";
const std::string   RTypeGame::mobTypesPath     = ".rtypemobs";

/*
** Constructor/Destructor
*/
RTypeGame::RTypeGame(std::string const& addr, short port) :
    _addr(addr), _port(port),
    _quit(false), _isPlaying(false), _em(), _renderer(&_em),
    _input(_renderer.getWindow()), _bs(&_em),
    _network(&_em, addr, port), _cs(&_em, &_input, &_network),
    _event(), _menu(nullptr), _lag(0), _fixedStep(defaultFixedStep),
    _ms(&_em, &_chrono, &_mobTypes), _physics(&_em), _audio(&_em)
{
    BigBen::getElapsedtime();

    // tmp
//    RType::Request request;
//    request.setCode(RType::Request::CL_CREATEROOM);
//    request.push<std::string>("room_name", "BestRoomEver");
//    _network.pushTCP(request);
//    _network.pushTCP(RType::Request(RType::Request::CL_READY));
    // end tmp

    loadMobTypesFromFile();
    loadMapsFromFile();

    _menu = _em.createEntity<Menu>("Niquez-vos-races-Type", 1, &_em, &_event);
    _em.attachComponent<TCPView>(_menu, "TCP");
    _em.attachComponent<UDPView>(_menu, "UDP");
     _menu->init();
//     _menu->setVisible(false);
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
    initGameSample();
    while (!_quit)
    {
        while (_input.pollEvent(_event))
        {
            if (_event.type == cu::Event::Closed
                || _event.key == cu::Event::ESCAPE)
            {
                _quit = true;
                break ;
            }
            if (!_isPlaying)
                _menu->move();
            else
                handleGame();
        }
        if (_isPlaying)
            handleGame();
        _network.processTCP();
        _network.processUDP();
        _renderer.render();
        _event.type = cu::Event::None;
    }
}

/*
** Protected member functions
*/
void        RTypeGame::initGameSample()
{
    PlayerObject *player = _em.createEntity<PlayerObject>("Player", 1, &_em);
    player->init();
    GameObject *bg = _em.createEntity<GameObject>("bg", -1);
    GameObject *pr = _em.createEntity<GameObject>("pr", 2);
    AudioEffect*    audio;

    if (_mobTypes.empty())
        throw std::runtime_error("No mobs types loaded");

    _em.attachComponent<SpriteRenderer>(bg, "bg", "bg1", gu::Rect<int>(0, 0, 1280, 720));
    _em.attachComponent<ScrollingBackground>(bg, "Background", 0.25);
    _em.attachComponent<SpriteRenderer>(pr, "pr", "pr1", gu::Rect<int>(0, 0, 1280, 720));
    _em.attachComponent<ScrollingBackground>(pr, "Paralax", 0.75);
    _em.attachComponent<AudioEffect>(player, "Audio");

    audio = player->getComponent<AudioEffect>();
    audio->addSound("../res/music.wav");
    audio->addSound("../res/laser1.wav");
    audio->addSound("../res/laser2.wav");

    if (_maps.empty())
        throw std::runtime_error("No maps loaded");
    _ms.setMap(_maps[0].second);
    _chrono.start();
}

void        RTypeGame::handleGame()
{
    _lag = BigBen::getElapsedtime();
    _cs.processInput();
    _cs.processNetwork();
    _ms.process();
    _physics.process(_fixedStep);
    _audio.process();
    while (_lag >= _fixedStep)
    {
        _bs.process(_lag / _fixedStep);
        _lag -= _fixedStep;
    }
}

void            RTypeGame::loadMapsFromFile()
{
    std::ifstream   file(mapsPath.c_str());
    std::string     line;

    if (!file)
    {
        std::cerr << "Warning: Map configuration file wasn't found"
                  << std::endl;
        return ;
    }
    while (std::getline(file, line))
    {
        std::ifstream       mapFile(line.c_str());

        if (line.empty())
            continue ;
        try {
            if (mapFile.good())
            {
               RType::Map::Parser         parser(line);
               RType::Map::Parser::Map    map;

               map = parser.parse();
               _maps.push_back(map);
               std::cout << "Map '" << map.first
                         << "' loaded" << std::endl;
            }
            else
            {
                std::cerr   << "Can't load map: no such file: "
                            << line << std::endl;
                mapFile.close();
            }
        } catch (std::runtime_error const& e) {
            mapFile.close();
            file.close();
            throw ;
        }
        mapFile.close();
    }
    file.close();
}

void            RTypeGame::loadMobTypesFromFile()
{
    std::ifstream   file(mobTypesPath.c_str());
    std::string     line;

    if (!file)
    {
        std::cerr << "Warning: Mob types configuration file wasn't found"
                  << std::endl;
        return ;
    }
    while (std::getline(file, line))
    {
        std::ifstream       mobFile(line.c_str());
        RType::MobType::IMobType*  mobType = nullptr;

        if (line.empty())
            continue ;
        try {
            if (mobFile.good())
            {
                mobType =
                    DLLoader<RType::MobType::IMobType*>::getInstanceOf(line,
                                                                "getMobType");
                std::cout << "Mob '" << mobType->getName()
                          << "' loaded" << std::endl;
                _mobTypes[mobType->getId()] = UniqueMobType(mobType);
            }
            else
            {
                std::cerr   << "Can't load mob type: no such file: "
                            << line << std::endl;
                mobFile.close();
            }
        } catch (std::runtime_error const&) {
            mobFile.close();
            file.close();
            throw ;
        }
    }
    file.close();
}
