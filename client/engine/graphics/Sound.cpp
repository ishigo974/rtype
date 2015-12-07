#include <iostream>
#include "Sound.hpp"

Sound::Sound()
{
}

Sound::~Sound()
{
}

bool	Sound::isPlaying()
{
	return _sound.getStatus() == sf::Sound::Playing;
}

bool	Sound::changeSound(const std::string &filename)
{
	if (!_buff.loadFromFile(filename))
		return false;
	_sound.setBuffer(_buff);
	return true;
}

void	Sound::play()
{
	std::cout << "Je joue du son" << std::endl;
	_sound.play();
}