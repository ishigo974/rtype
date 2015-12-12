#ifndef AUDIORESOURCES_HPP_
# define AUDIORESOURCES_HPP_

# include <iostream>
# include <SFML/Audio.hpp>
# include <map>

class AudioResources
{
public:
	AudioResources();
	~AudioResources();

	AudioResources(const AudioResources&) = delete;
	AudioResources& operator=(const AudioResources&) = delete;
	
public:
	const sf::SoundBuffer								&getBuffer(const std::string&) const;
	const sf::SoundBuffer								&operator[](const std::string&) const;
	bool												addSound(const std::string&);

private:
	std::map <const std::string, sf::SoundBuffer>		_buffs;
};

#endif // !AUDIORESOURCES_HPP_