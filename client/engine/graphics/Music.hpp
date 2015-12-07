#include <SFML\Audio.hpp>

class Music
{
public:
	Music();
	~Music();

public:
	bool	setSound(const std::string &, bool = false);
	bool	isPlaying();
	void	setLoop(bool);
	void	play();
	void	stop();

private:
	sf::Music		_music;
};