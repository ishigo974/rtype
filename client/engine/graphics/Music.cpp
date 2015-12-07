#include "Music.hpp"

Music::Music()
{
}

Music::~Music()
{
}

bool	Music::setSound(const std::string &filename, bool loop)
{
	if (!_music.openFromFile(filename))
		return false;
	setLoop(loop);
	return true;
}

bool	Music::isPlaying()
{
	return _music.getStatus() == sf::Sound::Playing;
}

void	Music::setLoop(bool loop)
{
	_music.setLoop(loop);
}

void	Music::play()
{
	_music.play();
}

void	Music::stop()
{
	_music.stop();
}