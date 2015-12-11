#include "AudioEffect.hpp"

AudioEffect::AudioEffect(unsigned id, std::string const &name)
	: Component(id, name)
{}

AudioEffect::AudioEffect(AudioEffect const &other)
	: Component(other)
{}

AudioEffect::AudioEffect(AudioEffect &&other)
	: AudioEffect(other)
{
	swap(*this, other);
}

AudioEffect &AudioEffect::operator=(AudioEffect other)
{
	swap(*this, other);

	return *this;
}

AudioEffect::~AudioEffect()
{
}

bool AudioEffect::operator==(AudioEffect const &other)
{
	return Object::operator==(other)
		&& _sounds == other._sounds;
}

bool AudioEffect::operator!=(AudioEffect const &other)
{
	return !AudioEffect::operator==(other);
}

void AudioEffect::swap(AudioEffect &lhs, AudioEffect &rhs)
{
	std::swap(lhs._sounds, rhs._sounds);
}

std::string AudioEffect::toString() const
{
	std::string ret = std::string("AudioEffect {") +
		"\n\tid: " + std::to_string(_id) +
		"\n\tname: " + _name + "\n";
	for (std::map<std::string, bool>::const_iterator s = _sounds.begin(); s != _sounds.end(); ++s)
	{
		ret += "\ttrack: " + s->first + "\n";
	}
	return (ret + "}");
}

sf::SoundBuffer const * AudioEffect::soundToPlay() const
{
	std::string	selected;

	for (std::map<std::string, bool>::const_iterator s = _sounds.begin(); s != _sounds.end(); ++s)
	{
		if (s->second == true)
			selected = s->first;
	}
	return _res[selected];
}

bool AudioEffect::addSound(std::string const &path)
{
	if (!_res.addSound(path))
		return false;
	_sounds[path] = false;
	return true;
}

void AudioEffect::setSoundToPlay(std::string const &path)
{
	try
	{
		clearSounds();
		_sounds[path] = true;
 	}
	catch (const std::out_of_range& exc)
	{
		std::cerr << exc.what() << std::endl;
		_sounds["NoSound"] = true;
	}
}

void	AudioEffect::clearSounds()
{
	for (std::map<std::string, bool>::iterator s = _sounds.begin(); s != _sounds.end(); ++s)
	{
		s->second = false;
	}
}