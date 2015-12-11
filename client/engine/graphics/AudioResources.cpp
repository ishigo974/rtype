#include "AudioResources.hpp"

AudioResources::AudioResources()
{
	_buffs["../res/NoSound.wav"] = new sf::SoundBuffer();
	if (!_buffs["../res/NoSound.wav"]->loadFromFile("../res/NoSound.wav"))
		std::cout << "Fail init NoSound" << std::endl;
	//throw std::runtime_error("../res/NoSound.png not found");
}

AudioResources::~AudioResources()
{
	for (auto it = _buffs.begin(); it != _buffs.end(); ++it)
		delete it->second;
}

const sf::SoundBuffer* AudioResources::getBuffer(const std::string& path) const
{
	try
	{
		return _buffs.at(path);
	}
	catch (std::out_of_range& e)
	{
		std::cerr << e.what() << std::endl;
		return _buffs.at("../res/NoSound.wav");
	}
}

const sf::SoundBuffer* AudioResources::operator[](const std::string& path) const
{
	return getBuffer(path);
}

bool    AudioResources::addSound(const std::string& path)
{
	try
	{
		std::cout << "Add de son: " << path << std::endl;
		_buffs[path] = new sf::SoundBuffer();
		std::cout << "Allocation finie" << std::endl;
		if (!_buffs[path]->loadFromFile(path))
		{
			delete _buffs[path];
			_buffs.erase(path);
			return false;
		}
	}
	catch (std::bad_alloc &e)
	{
		std::cout << "Alloc failed: " << e.what() << std::endl;
	}
	return true;
}
