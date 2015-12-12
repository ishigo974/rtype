#include <iostream>

#include "GameObject.hpp"
#include "EntityManager.hpp"

#include "AudioEffect.hpp"
#include "AudioEffectPlayer.hpp"
#include "Music.hpp"
#include "MusicPlayer.hpp"

MusicPlayer		musicPlayer; 
AudioEffectPlayer soundPlayer;
EntityManager	entity;

// Les sf::sleep sont la pour ne pas lancer les sons en meme temps car la sfml joue les sons
// dans un thread a part; Ils seraient lancés en même temps sinon...

int audioEffectPlayerTest(GameObject *gameObj)
{
	AudioEffect *audio = gameObj->getComponent<AudioEffect>();
	audio->setSoundToPlay("../res/laser1.wav");
	std::cout << audio->toString() << std::endl;
	soundPlayer.play(*gameObj);
	sf::sleep(sf::milliseconds(400));

	audio->setSoundToPlay("../res/laser2.wav");
	std::cout << audio->toString() << std::endl;
	soundPlayer.play(*gameObj);
	sf::sleep(sf::milliseconds(400));

	audio->setSoundToPlay("../res/laserKIKOOLOL.wav");
	std::cout << audio->toString() << std::endl;
	soundPlayer.play(*gameObj);
	sf::sleep(sf::milliseconds(2000));

	audio->setSoundToPlay("../res/laser1.wav");
	std::cout << audio->toString() << std::endl;
	soundPlayer.play(*gameObj);
	return 0;
}

int	musicPlayerTest(GameObject *gameObj)
{
	Music *music = gameObj->getComponent<Music>();

	std::cout << music->toString() << std::endl;
	musicPlayer.play(*gameObj, "../res/music.wav", false);
	std::cout << music->toString() << std::endl;

	return 0;
}

int main()
{
	GameObject		*gameObj = entity.createEntity<GameObject>("test", 1);

	entity.attachComponent<Music>(gameObj, "Music");
	entity.attachComponent<AudioEffect>(gameObj, "testAudio");

	AudioEffect *audio = gameObj->getComponent<AudioEffect>();
	audio->addSound("../res/laser1.wav");
	audio->addSound("../res/laser2.wav");
	audio->addSound("../res/laser2.wav");
	audio->addSound("DELAMERDE");
	audio->addSound("ENBOITE");

	musicPlayerTest(gameObj);
	sf::sleep(sf::milliseconds(1000));

	audioEffectPlayerTest(gameObj);
	while (gameObj->getComponent<Music>()->isPlaying());

	return (0);
}
