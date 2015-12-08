#include <deque>
#include <SFML\Audio.hpp>
#include "GameObject.hpp"

class SoundEffectPlayer
{
public:
	SoundEffectPlayer();
	~SoundEffectPlayer();

public:
	void	play(const GameObject&);

public:
	//std::deque<sf::Sound>	_queue;
};