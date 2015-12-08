#include <iostream>
#include "SoundEffectPlayer.hpp"
#include "SoundEffect.hpp"

SoundEffectPlayer::SoundEffectPlayer()
{
}

SoundEffectPlayer::~SoundEffectPlayer()
{
}

void	SoundEffectPlayer::play(const GameObject &obj)
{
	SoundEffect *s = obj.getComponent<SoundEffect>();

	s->play();
}