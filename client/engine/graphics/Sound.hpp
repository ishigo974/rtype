#include <SFML\Audio.hpp>

class Sound
{
public:
	Sound();
	~Sound();

public:
	bool	isPlaying();
	bool	setSound(const std::string &);
	void	play();

private:
	sf::Sound		_sound;
	sf::SoundBuffer _buff;
};