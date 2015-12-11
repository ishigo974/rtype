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

	sf::SoundBuffer const	*soundToPlay() const;
	bool					addSound(std::string const &);
	void					setSoundToPlay(std::string const &);

private:
	void					clearSounds();

protected:
	std::map<std::string, bool>		_sounds;
	AudioResources					_res;
};

#endif // !AUDIOEFFECT_HPP_