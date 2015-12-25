#include "GameManager.hpp"

#include <iostream>
#include "GameManagerBehaviour.hpp"
#include "GameManager.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Bullet.hpp"
#include "Mob.hpp"
#include "ObjectPool.hpp"
#include "AudioEffect.hpp"

GameManagerBehaviour::GameManagerBehaviour()
{
}

GameManagerBehaviour::GameManagerBehaviour(unsigned int _id, std::string const& _name) :
    Behaviour(_id, _name)
{
}

GameManagerBehaviour::GameManagerBehaviour(GameManagerBehaviour const& other) :
    Behaviour(other)
{
}

GameManagerBehaviour::GameManagerBehaviour(GameManagerBehaviour&& other) : GameManagerBehaviour(other)
{
    swap(other);
}

GameManagerBehaviour& GameManagerBehaviour::operator=(GameManagerBehaviour other)
{
    swap(other);

    return (*this);
}

GameManagerBehaviour::~GameManagerBehaviour()
{
}

bool GameManagerBehaviour::operator==(GameManagerBehaviour const& other)
{
    return (Behaviour::operator==(other));
}

bool GameManagerBehaviour::operator!=(GameManagerBehaviour const& other)
{
    return (!GameManagerBehaviour::operator==(other));
}

void                GameManagerBehaviour::swap(GameManagerBehaviour&)
{
}

namespace std
{
    template <>
    inline void swap<GameManagerBehaviour>(GameManagerBehaviour& a,
                                            GameManagerBehaviour& b)
    {
        a.swap(b);
    }
}

RTypes::my_uint16_t GameManagerBehaviour::getMask() const
{
    return Mask;
}

std::string         GameManagerBehaviour::toString() const
{
    return "GameManagerBehaviour {}";
}

void                GameManagerBehaviour::update(double)
{
    RType::Request::PlayersTab  players;
    GameManager*    goParent    = static_cast<GameManager *>(parent());
    TCPView*        tcp         = goParent->getComponent<TCPView>();
    unsigned int    id;

    std::cout << "fuck" << std::endl;
    while (tcp->sizeReceive() > 0)
    {
        std::cout << "YAYAYAYAYAYAY" << std::endl;
        RType::Request      request = tcp->popReceive();

        switch (request.getCode())
        {
            case RType::Request::SE_JOINROOM:
                (*goParent)[request.get<uint8_t>("player_id")] = nullptr;
                break ;
            case RType::Request::SE_QUITROOM:
                goParent->erasePlayer(request.get<uint8_t>("player_id"));
                break ;
            case RType::Request::SE_ROOMINFO:
                players =
                    request.get<RType::Request::PlayersTab>("players");
                id = request.get<uint8_t>("player_id");
                goParent->clearPlayers();
                (*goParent)[id] = nullptr;
                goParent->setPlayerId(id);
                for (auto& player: players)
                    (*goParent)[player.id] = nullptr;
                break ;
            default:
                break ;
        }
        std::cout << goParent->toString() << std::endl; // debug
    }
}
