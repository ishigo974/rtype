#ifndef AUDIOEFFECTPLAYER_HPP_
# define AUDIOEFFECTPLAYER_HPP_

#include <SFML\Audio.hpp>
#include "GameObject.hpp"

class AudioEffectPlayer
{
public:
	AudioEffectPlayer() {};
	~AudioEffectPlayer() {};

public:
	void	play(const GameObject&);
	void	stop(const GameObject&);
};

#endif // !AUDIOEFFECTPLAYER_HPP_