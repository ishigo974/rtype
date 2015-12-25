//
// Created by fourdr_b on 23/12/15.
//

#ifndef RTYPE_GAMEMANAGER_HPP
# define RTYPE_GAMEMANAGER_HPP

# include <map>
# include "GameObject.hpp"

class GameManager : public GameObject
{
public:
    typedef std::map<unsigned int, GameObject *>    GameObjectMap;

public:
    GameManager();
    GameManager(unsigned int id, std::string const& name, int layer);
    GameManager(GameManager const& o);
    GameManager(GameManager&& o);
    GameManager&        operator=(GameManager o);

    void swap(GameManager &o);

public:
    GameObject*&        operator[](unsigned int id);

public:
    void                            clearPlayers();
    void                            erasePlayer(unsigned int id);
    GameObjectMap::const_iterator   begin() const;
    GameObjectMap::const_iterator   end() const;

public:
    unsigned int        getPlayerId() const;
    void                setPlayerId(unsigned int id);
    std::string         toString() const;

private:
    unsigned int        _playerId;
    GameObjectMap       _targets;
};


#endif //RTYPE_GAMEMANAGER_HPP
