#include "AudioEffectPlayer.hpp"
#include "AudioEffect.hpp"

void	AudioEffectPlayer::play(const GameObject &obj)
{
	_sounds.push_back(obj.getComponent<AudioEffect>()->soundToPlay());
	_sounds.back().play();
	for (std::list<sf::Sound>::iterator it = _sounds.begin(); it != _sounds.end();)
	{
		if (it->getStatus() != sf::Sound::Playing)
			it = _sounds.erase(it);
		else
			++it;
	}
}

void	AudioEffectPlayer::refreshSoundList()
{
	for (std::list<sf::Sound>::iterator it = _sounds.begin(); it != _sounds.end();)
	{
		if (it->getStatus() != sf::Sound::Playing)
			it = _sounds.erase(it);
		else
			++it;
	}
}
