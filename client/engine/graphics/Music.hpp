#ifndef MUSIC_HPP_
# define MUSIC_HPP_

# include <SFML\Audio.hpp>
# include "Component.hpp"

class Music : public Component
{
public:
	Music(unsigned _id, std::string const& _name,
		std::string const& path, bool = false);
	Music& operator=(Music other);
	Music(Music const& other);
	Music(Music&& other);
	~Music();

	bool                operator==(Music const& other);
	bool                operator!=(Music const& other);

	void swap(Music& lhs, Music& rhs);

	std::string toString() const;

	std::string const&	getPath() const;
	bool				getLoop() const;
	RTypes::my_uint16_t	getMask() const;

	bool	isPlaying() const;
	void	play();
	void	stop();

public:
	static RTypes::my_uint16_t const Mask = 0b0000000100000000;

protected:
	std::string		_path;
	bool			_loop;
	sf::Music		_music;


private:
	void init();

};

#endif // !MUSIC_HPP_