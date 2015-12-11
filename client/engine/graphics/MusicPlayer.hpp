#include <SFML\Audio.hpp>
#include "GameObject.hpp"

class MusicPlayer
{
public:
	MusicPlayer() {};
	~MusicPlayer() {};

public:
	void	play(const GameObject&);
	void	stop(const GameObject&);
};