#include "AudioResources.hpp"

AudioResources::AudioResources()
{
	_buffs["../client/res/0NoSound.wav"] = sf::SoundBuffer();
	if (!_buffs["../client/res/NoSound.wav"].loadFromFile("../client/res/NoSound.wav"))
		std::cout << "Fail init NoSound" << std::endl;
	//throw std::runtime_error("../res/NoSound.png not found");
}

AudioResources::~AudioResources()
{ }

const sf::SoundBuffer &AudioResources::getBuffer(const std::string& path) const
{
	if (_buffs.find(path) != _buffs.end())
		return _buffs.at(path);
	else
		return _buffs.at("../client/res/NoSound.wav");
}

const sf::SoundBuffer &AudioResources::operator[](const std::string& path) const
{
	return getBuffer(path);
}

bool    AudioResources::addSound(const std::string& path)
{
	_buffs[path] = sf::SoundBuffer();
	if (!_buffs[path].loadFromFile(path))
	{
		_buffs.erase(path);
		return false;
	}
	return true;
}
