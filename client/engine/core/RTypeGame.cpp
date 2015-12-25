#include <fstream>
#include <NetPlayerObject.hpp>
#include "RTypeGame.hpp"
#include "Menu.hpp"
#include "PlayerObject.hpp"
#include "ScrollingBackground.hpp"
#include "DLLoader.hpp"
#include "Mob.hpp"
#include "Collider.hpp"
#include "AudioEffect.hpp"
#include "MobSpawner.hpp"
#include "TCPView.hpp"
#include "UDPView.hpp"

/*
** Static variables
*/
const double        RTypeGame::defaultFixedStep = 0.006;
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
    _network(&_em, addr, port, port + 1), _cs(&_em, &_input, &_network, _chrono),
    _event(), _menu(nullptr), _lag(0), _fixedStep(defaultFixedStep),
    _physics(&_em), _audio(&_em)
{
    GameManager *gm = _em.createEntity<GameManager>("gm", 0);

    BigBen::getElapsedtime();
    loadMobTypesFromFile();
    loadMapsFromFile();


    _em.tagObject(gm, "GameManager");
    _em.attachComponent<TCPView>(gm, "TCP");
    _em.attachComponent<GameManagerBehaviour>(gm, "GMB");
    _gmb = gm->getComponent<GameManagerBehaviour>();

    _menu = _em.createEntity<Menu>("Niquez-vos-races-Type", 1, &_em, &_event);
    _em.attachComponent<TCPView>(_menu, "TCP");
    _em.attachComponent<UDPView>(_menu, "UDP");
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
            {
                _menu->update();
                _menu->move();
                _cs.processNetwork();
            }
            else
                handleGame();
        }
        if (_isPlaying)
            handleGame();
        else
        {
            _menu->update();
            _cs.processNetwork();
            if (_menu->done())
            {
                _isPlaying = true;
                _menu->setVisible(false);
                initGame();
            }
            else
            {
                _gmb->update(0);
            }
        }
        _renderer.render();
        _event.type = cu::Event::None;
    }
}

/*
** Protected member functions
*/
void        RTypeGame::initGame()
{
    GameObject *bg = _em.createEntity<GameObject>("bg", -10);
    GameObject *ds = _em.createEntity<GameObject>("ds", -5);
    GameObject *df = _em.createEntity<GameObject>("df", -4);
    GameObject *opm = _em.createEntity<GameObject>("opm", -3);
    GameObject *pr = _em.createEntity<GameObject>("pr", 2);
    GameObject *mobSpawn = _em.createEntity<GameObject>("mobSpawn", 10);
    AudioEffect*    audio;
    GameManager* gm = static_cast<GameManager*>(_em.getByTag("GameManager"));

    std::cout << "____ init game" << std::endl;
    std::cout << gm->toString() << std::endl;
    std::cout << "____ loop start" << std::endl;
    for (auto& entry: *gm)
    {
        if (entry.first == gm->getId())
        {
            std::cout << "init main player" << std::endl;
	        PlayerObject *player = _em.createEntity<PlayerObject>("Player", 1, &_em);
            player->init();
            entry.second = player;
    	    _em.attachComponent<AudioEffect>(player, "Audio");
    	    audio = player->getComponent<AudioEffect>();
    	    audio->addSound("../res/OnePunch.wav");
    	    audio->addSound("../res/laser1.wav");
    	    audio->addSound("../res/laser2.wav");
        }
        else
        {
            std::cout << "init other player" << std::endl;
            NetPlayerObject *player = _em.createEntity<NetPlayerObject>("NetPlayer", &_em);
            player->init();
            entry.second = player;
        }
    }
    std::cout << "____ loop end" << std::endl;
    if (_mobTypes.empty())
        throw std::runtime_error("No mobs types loaded");


    _em.tagObject(mobSpawn, "mobSpawn");

    _em.attachComponent<MobSpawner>(mobSpawn, "MobSpawner", &_em, &_mobTypes);
    _em.attachComponent<UDPView>(mobSpawn, "Spawner UDPView");
    mobSpawn->getComponent<MobSpawner>()->init();

    _em.attachComponent<SpriteRenderer>(ds, "ds", "deathstar", gu::Rect<int>(0, 0, 1280, 720));
    _em.attachComponent<ScrollingBackground>(ds, "DeathStar", 0.3);
    //
    _em.attachComponent<SpriteRenderer>(df, "df", "dogfight", gu::Rect<int>(0, 0, 1280, 720));
    _em.attachComponent<ScrollingBackground>(df, "Background", 0.3);

    _em.attachComponent<SpriteRenderer>(bg, "bg", "bg1", gu::Rect<int>(0, 0, 1280, 720));
    _em.attachComponent<ScrollingBackground>(bg, "Background", 0.27);

    _em.attachComponent<SpriteRenderer>(opm, "opm", "opm", gu::Rect<int>(0, 0, 1280, 720));
    _em.attachComponent<ScrollingBackground>(opm, "OPM", 0.55);

    _em.attachComponent<SpriteRenderer>(pr, "pr", "pr1", gu::Rect<int>(0, 0, 1280, 720));
    _em.attachComponent<ScrollingBackground>(pr, "Paralax", 0.60);

    if (_maps.empty())
        throw std::runtime_error("No maps loaded");
     _chrono.start();
}

void        RTypeGame::handleGame()
{
    _lag += (BigBen::getElapsedtime() / 1000000000);
    _cs.processInput();
    _cs.processNetwork();
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
        } catch (std::runtime_error const&) {
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
            std::cout << "load mob failed " << line << std::endl;
            // TODO throw ;
        }
    }
    file.close();
}
