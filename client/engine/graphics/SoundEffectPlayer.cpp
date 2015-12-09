#include "SoundEffectPlayer.hpp"
#include "SoundEffect.hpp"

void	SoundEffectPlayer::play(const GameObject &obj)
{
	obj.getComponent<SoundEffect>()->play();
}