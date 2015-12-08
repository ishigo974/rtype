#ifndef SOUNDEFFECT_HPP_
# define SOUNDEFFECT_HPP_

# include <SFML/Audio.hpp>
# include "Component.hpp"

class SoundEffect : public Component
{
public:
	SoundEffect(unsigned _id, std::string const& _name,
		std::string const& path);
	SoundEffect& operator=(SoundEffect other);
	SoundEffect(SoundEffect const& other);
	SoundEffect(SoundEffect&& other);
	~SoundEffect();

	bool                operator==(SoundEffect const& other);
	bool                operator!=(SoundEffect const& other);

	void swap(SoundEffect& lhs, SoundEffect& rhs);

	std::string toString() const;

	std::string const&	getPath() const;
	RTypes::my_uint16_t	getMask() const;

	bool	isPlaying() const;
	void	play();

public:
	static RTypes::my_uint16_t const Mask = 0b0000000100000000;

protected:
	std::string		_path;
	sf::SoundBuffer	_buff;
	sf::Sound		_sound;

private:
	void init();

};

#endif // !SOUNDEFFECT_HPP_