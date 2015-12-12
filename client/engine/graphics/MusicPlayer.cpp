#include "MusicPlayer.hpp"
#include "Music.hpp"

void	MusicPlayer::play(const GameObject &obj, const std::string &path, bool loop)
{
	obj.getComponent<Music>()->play(path, loop);
}

bool MusicPlayer::isPlaying(const GameObject &obj)
{
	return obj.getComponent<Music>()->isPlaying();
}

void	MusicPlayer::stop(const GameObject &obj)
{
	obj.getComponent<Music>()->stop();
}