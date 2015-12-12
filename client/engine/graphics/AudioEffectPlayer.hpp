#ifndef AUDIOEFFECTPLAYER_HPP_
# define AUDIOEFFECTPLAYER_HPP_

#include <list>
#include <SFML\Audio.hpp>
#include "GameObject.hpp"

class AudioEffectPlayer
{
public:
	AudioEffectPlayer() {};
	~AudioEffectPlayer() {};

public:
	void	play(const GameObject&);
	void	refreshSoundList();

private:
	std::list<sf::Sound>	_sounds;
};

#endif // !AUDIOEFFECTPLAYER_HPP_