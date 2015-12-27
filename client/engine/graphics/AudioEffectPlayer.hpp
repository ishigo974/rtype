#ifndef AUDIOEFFECTPLAYER_HPP_
# define AUDIOEFFECTPLAYER_HPP_

#include <list>
#include <SFML/Audio.hpp>
#include "EntityManager.hpp"
#include "GameObject.hpp"

class AudioEffectPlayer
{
public:
    AudioEffectPlayer(EntityManager *em)
    : _em(em)
    {
        _backgroundStart = false;
    }

    ~AudioEffectPlayer()
    { }

public:
    void play(GameObject*);
    void refreshSoundList();
    void process();
    void init();

public:
    static const std::string Background;
    static const std::string Shot1;
    static const std::string Shot2;
    static const std::string Explosion;
    static const std::string Death;
    static const std::string NoSound;

private:
    EntityManager *_em;
    std::list<sf::Sound> _sounds;
    bool                _backgroundStart;
};

#endif // !AUDIOEFFECTPLAYER_HPP_
