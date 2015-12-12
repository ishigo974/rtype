#ifndef AUDIOEFFECT_HPP_
# define AUDIOEFFECT_HPP_

# include <SFML/Audio.hpp>
# include "Component.hpp"
# include "AudioResources.hpp"

class AudioEffect : public Component
{
public:
	AudioEffect(unsigned _id, std::string const& _name);
	AudioEffect& operator=(AudioEffect other);
	AudioEffect(AudioEffect const& other);
	AudioEffect(AudioEffect&& other);
	~AudioEffect();

	bool                operator==(AudioEffect const& other);
	bool                operator!=(AudioEffect const& other);

	void swap(AudioEffect& lhs, AudioEffect& rhs);

	std::string toString() const;

	sf::Sound				&soundToPlay();
	bool					addSound(std::string const &);
	void					setSoundToPlay(std::string const &);

	RTypes::my_uint16_t getMask() const;

	static RTypes::my_uint16_t const Mask = 0b0000000100000000;
private:
	void					clearSounds();

protected:
	std::map<std::string, bool>		_sounds;
	AudioResources					_res;
	sf::Sound						_playSound;
};

#endif // !AUDIOEFFECT_HPP_