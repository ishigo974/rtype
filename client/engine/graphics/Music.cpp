#include "Music.hpp"

Music::Music(unsigned id, std::string const &name, std::string const & path, bool loop)
	: Component(id, name), _path(path), _loop(loop)
{
	init();
}

Music::Music(Music const &other)
	: Component(other), _path(other.getPath()), _loop(other.getLoop())
{
	init();
}

void	Music::init()
{
	if (!_music.openFromFile(_path))
		throw std::runtime_error("Music not found");
	_music.setLoop(_loop);
}

Music::Music(Music &&other)
	: Music(other)
{
	swap(*this, other);
	init();
}

Music &Music::operator=(Music other)
{
	swap(*this, other);
	init();

	return *this;
}

Music::~Music()
{
}

bool Music::operator==(Music const &other)
{
	return Object::operator==(other)
		&& _path == other.getPath()
		&& _loop == other.getLoop();
}

bool Music::operator!=(Music const &other)
{
	return !Music::operator==(other);
}

void Music::swap(Music &lhs, Music &rhs)
{
	std::swap(lhs._path, rhs._path);
}

std::string Music::toString() const
{
	return (std::string("Music {") +
		"\n\tid: " + std::to_string(_id) +
		"\n\tname: " + _name +
		"\n\tpath: " + _path +
		"\n\tloop: " + (_loop ? "true" : "false") +
		"\n}");
}

std::string const &Music::getPath() const
{
	return _path;
}

bool	Music::getLoop() const
{
	return _loop;
}

RTypes::my_uint16_t Music::getMask() const
{
	return Mask;
}

bool	Music::isPlaying() const
{
	return _music.getStatus() == sf::Sound::Playing;
}

void	Music::play()
{
	_music.play();
}

void	Music::stop()
{
	_music.stop();
}