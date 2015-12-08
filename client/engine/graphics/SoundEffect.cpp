#include "SoundEffect.hpp"

SoundEffect::SoundEffect(unsigned id, std::string const &name, std::string const & path)
	: Component(id, name), _path(path)
{
	init();
}

SoundEffect::SoundEffect(SoundEffect const &other)
	: Component(other), _path(other.getPath())
{
}

void	SoundEffect::init()
{
	if (!_buff.loadFromFile(_path))
		throw std::runtime_error("Sound not found");
	_sound.setBuffer(_buff);
}

SoundEffect::SoundEffect(SoundEffect &&other)
	: SoundEffect(other)
{
	swap(*this, other);
	init();
}

SoundEffect &SoundEffect::operator=(SoundEffect other)
{
	swap(*this, other);
	init();

	return *this;
}

SoundEffect::~SoundEffect()
{
}

bool SoundEffect::operator==(SoundEffect const &other)
{
	return Object::operator==(other)
		&& _path == other.getPath();
}

bool SoundEffect::operator!=(SoundEffect const &other)
{
	return !SoundEffect::operator==(other);
}

void SoundEffect::swap(SoundEffect &lhs, SoundEffect &rhs)
{
	std::swap(lhs._path, rhs._path);
}

std::string SoundEffect::toString() const
{
	std::stringstream	ss;

	ss	<< "SoundEffect {" << std::endl
		<< "\tid: " << _id << std::endl
		<< "\tname: " << _name << std::endl
		<< "\tpath:" << _path << std::endl
		<< "}" << std::endl;
	return ss.str();
}

std::string const &SoundEffect::getPath() const
{
	return _path;
}

RTypes::my_uint16_t SoundEffect::getMask() const
{
	return Mask;
}

bool	SoundEffect::isPlaying() const
{
	return _sound.getStatus() == sf::Sound::Playing;
}

void	SoundEffect::play()
{
	_sound.play();
}