#include "SoundEffectPlayer.hpp"
#include "SoundEffect.hpp"

void	SoundEffectPlayer::play(const GameObject &obj)
{
	SoundEffect *s = obj.getComponent<SoundEffect>();

	std::cout << s->toString() << std::endl;
	s->play();
}

void	SoundEffectPlayer::stop(const GameObject &obj)
{
	SoundEffect *s = obj.getComponent<SoundEffect>();

	std::cout << s->toString() << std::endl;
	s->stop();
}
