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
    GameManager();
    GameManager(unsigned int id, std::string const& name, int layer);
    GameManager(GameManager const& o);
    GameManager(GameManager&& o);
    GameManager& operator=(GameManager o);

    void swap(GameManager &o);

public:
    GameObject *& operator[](unsigned int id);

private:
    std::map<unsigned int, GameObject *> _targets;
};


#endif //RTYPE_GAMEMANAGER_HPP
