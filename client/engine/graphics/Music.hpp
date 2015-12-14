#ifndef MUSIC_HPP_
# define MUSIC_HPP_

# include <SFML/Audio.hpp>
# include "Component.hpp"

class Music : public Component
{
public:
	Music(unsigned _id, std::string const& _name);
	Music& operator=(Music other);
	Music(Music const& other);
	Music(Music&& other);
	~Music();

	bool                operator==(Music const& other);
	bool                operator!=(Music const& other);

	void swap(Music& lhs, Music& rhs);

	std::string toString() const;

	RTypes::my_uint16_t	getMask() const;
	std::string getCurMusic() const;

	bool	play(std::string const &, bool = false);
	bool	isPlaying() const;
	void	stop();

public:
	static RTypes::my_uint16_t const Mask = 0b000001000000000;

protected:
	sf::Music					_music;
	std::string					_curMusic;
};

#endif // !MUSIC_HPP_
