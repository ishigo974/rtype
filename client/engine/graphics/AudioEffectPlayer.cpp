#include <NotImplemented.hpp>
#include "AudioEffectPlayer.hpp"
#include "AudioEffect.hpp"

void    AudioEffectPlayer::play(GameObject *obj)
{
    try
    {
        if (!_sounds.empty()
            && _sounds.begin()->getStatus() == sf::Sound::Stopped
            && _backgroundStart)
        {
            obj->getComponent<AudioEffect>()->setSoundToPlay("../res/music.wav");
        }
        _sounds.push_back(obj->getComponent<AudioEffect>()->soundToPlay());
    }
    catch (Exception::NotImplemented const&e)
    {
        return;
    }
    _sounds.back().play();
    obj->getComponent<AudioEffect>()->clearSounds();
    for (std::list<sf::Sound>::iterator it = _sounds.begin();
         it != _sounds.end();)
    {
        if (it->getStatus() != sf::Sound::Playing)
            it = _sounds.erase(it);
        else
            ++it;
    }
    _backgroundStart = true;
}

void    AudioEffectPlayer::refreshSoundList()
{
    for (std::list<sf::Sound>::iterator it = _sounds.begin();
    it != _sounds.end();)
    {
        if (it->getStatus() != sf::Sound::Playing)
        it = _sounds.erase(it);
        else
        ++it;
    }
}

void AudioEffectPlayer::process()
{
    std::vector<Object *> sounds = _em->getByMask(SoundMask);
    for (auto obj: sounds)
    {
        play(static_cast<GameObject *>(obj));
    }
}

void AudioEffectPlayer::init()
{
}
