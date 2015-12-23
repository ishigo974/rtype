#include <NotImplemented.hpp>
#include "AudioEffectPlayer.hpp"
#include "AudioEffect.hpp"

void    AudioEffectPlayer::play(GameObject *obj)
{
    for (std::list<sf::Sound>::iterator it = _sounds.begin();
         it != _sounds.end();)
    {
        if (it->getStatus() != sf::Sound::Playing)
            it = _sounds.erase(it);
        else
            ++it;
    }
    try
    {
        if ((!_sounds.empty()
            && _sounds.begin()->getStatus() == sf::Sound::Stopped
            && _backgroundStart) || _sounds.empty())
        {
            obj->getComponent<AudioEffect>()->setSoundToPlay("../res/music.wav");
            _sounds.push_front(obj->getComponent<AudioEffect>()->soundToPlay());
        }
        else
            _sounds.push_back(obj->getComponent<AudioEffect>()->soundToPlay());
    }
    catch (Exception::NotImplemented const&)
    {
        return;
    }
    _sounds.front().setVolume(5);
    if (_sounds.size() > 1)
        _sounds.back().setVolume(0.5);
    _sounds.back().play();
    obj->getComponent<AudioEffect>()->clearSounds();
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
