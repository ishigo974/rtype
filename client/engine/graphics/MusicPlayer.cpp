#include "MusicPlayer.hpp"
#include "Music.hpp"

void	MusicPlayer::play(const GameObject &obj)
{
	Music *m = obj.getComponent<Music>();
	
	std::cout << m->toString() << std::endl;
	m->play();
}

void	MusicPlayer::stop(const GameObject &obj)
{
	Music *m = obj.getComponent<Music>();

	std::cout << m->toString() << std::endl;
	m->stop();
}