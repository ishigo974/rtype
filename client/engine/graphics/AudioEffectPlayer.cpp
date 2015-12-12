#include "AudioEffectPlayer.hpp"
#include "AudioEffect.hpp"

void	AudioEffectPlayer::play(const GameObject &obj)
{
	AudioEffect *s = obj.getComponent<AudioEffect>();

	s->soundToPlay().play();
}

void	AudioEffectPlayer::stop(const GameObject &obj)
{
	AudioEffect *s = obj.getComponent<AudioEffect>();

	s->soundToPlay().play();
}
