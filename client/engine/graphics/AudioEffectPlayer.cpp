#include <NotImplemented.hpp>
#include "AudioEffectPlayer.hpp"
#include "AudioEffect.hpp"

const std::string AudioEffectPlayer::Background = "../client/res/OnePunch.wav";
const std::string AudioEffectPlayer::Shot1 = "../client/res/laser1.wav";
const std::string AudioEffectPlayer::Shot2 = "../client/res/laser2.wav";
const std::string AudioEffectPlayer::Explosion = "../client/res/bulletExplosion.wav";
const std::string AudioEffectPlayer::Death = "../client/res/mobDeath.wav";

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
            obj->getComponent<AudioEffect>()->setSoundToPlay(AudioEffectPlayer::Background);
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
        _sounds.back().setVolume(10);
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
