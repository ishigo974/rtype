#include "Music.hpp"

Music::Music(unsigned id, std::string const &name)
	: Component(id, name), _curMusic("none")
{}

Music::Music(Music const &other)
	: Component(other), _curMusic(other._curMusic)
{
}

Music::Music(Music &&other)
	: Music(other)
{
	swap(*this, other);
}

Music &Music::operator=(Music other)
{
	swap(*this, other);
	return *this;
}

Music::~Music()
{
}

bool Music::operator==(Music const &other)
{
	return Object::operator==(other) &&
		this->_curMusic == other._curMusic;
}

bool Music::operator!=(Music const &other)
{
	return !Music::operator==(other);
}

void Music::swap(Music &lhs, Music &rhs)
{
	std::swap(lhs._curMusic, rhs._curMusic);
}

std::string Music::toString() const
{
	return (std::string("Music {") +
		"\n\tid: " + std::to_string(_id) +
		"\n\tname: " + _name +
		"\n\tcurrent music: " + _curMusic +
		"\n}");
}

RTypes::my_uint16_t Music::getMask() const
{
	return Mask;
}

std::string Music::getCurMusic() const
{
	return _curMusic;
}

bool	Music::isPlaying() const
{
	return _music.getStatus() == sf::Sound::Playing;
}

bool	Music::play(std::string const &path, bool loop)
{
	if (!_music.openFromFile(path))
		return false;
	_curMusic = path;
	_music.setLoop(loop);
	_music.play();
	return true;
}

void	Music::stop()
{
	_music.stop();
}
