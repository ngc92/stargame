#include "CSoundManager.h"

#include <map>
#include <iterator>
#include <iostream>

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>
using namespace irrklang;
using namespace irr;

//Hilfsfunktion irr::core::vector3df -> irrklang::vec3df
vec3df conv(const core::vector3df& v)
{
	return vec3df(v.X, v.Y, v.Z);
}

struct CSoundManager::EventContainer
{
	std::multimap<std::string, ISoundSource*> events;

	void addEvent(const std::string& event, ISoundSource* sound)
	{
		events.insert(std::pair<std::string, ISoundSource*>(event, sound));
	}

	ISoundSource* getSound(const std::string& event)
	{
		auto iterators = events.equal_range(event);
		int dis = std::distance(iterators.first, iterators.second);
		std::advance(iterators.first, rand() % dis);
		return iterators.first->second;
	}
};

CSoundManager::CSoundManager() :  engine(createIrrKlangDevice()),
								container(new EventContainer()),
								 music_loop(0), music_fade(0), listener(0), music_volume(0.33)
{
	// Sounds laden
	container->addEvent("music:battle", loadSound("music/battle.ogg"));
	container->addEvent("gun", loadSound("gun.ogg"));
	container->addEvent("explosion", loadSound("exp.ogg"));
	container->addEvent("missile", loadSound("missile.ogg"));
	container->addEvent("engine", loadSound("engine.ogg"));
	container->addEvent("hit", loadSound("hit1.ogg"));
	container->addEvent("hit", loadSound("hit2.ogg"));
	engine->setRolloffFactor(2.0);
}

CSoundManager::~CSoundManager() {
	if(engine)
		engine->drop();

	delete container;
}

// *********************************************************************************
//   PLAY - FUNCTIONS
// --------------------
bool CSoundManager::play(const core::vector3df& origin, const std::string& event)
{
	ISoundSource* sound = container->getSound(event);
	if(!sound)	//! \todo weitere errormöglichkeiten!
		return false;

	sound->setDefaultVolume(1.0);
	sound->setDefaultMinDistance(250);
	engine->play3D(sound, conv(origin));
	return true;
}

irrklang::ISound* CSoundManager::playWithFeedback( const core::vector3df origin, const std::string& event )
{
	ISoundSource* sound = container->getSound(event);
	if(!sound)	//! \todo weitere errormöglichkeiten!
		return nullptr;

	sound->setDefaultVolume(0.0);
	sound->setDefaultMinDistance(250);
	return engine->play3D(sound, conv(origin), false, false, true);
}

void CSoundManager::playMusic(const std::string& type)
{
	if(type != music_type) {
		music_type = type;
		timer = -1;
	}
}


void CSoundManager::setListener(const scene::ICameraSceneNode* cam)
{
	listener = cam;
}

void CSoundManager::update(float time_sec)
{
	if(listener)
		engine->setListenerPosition(conv(listener->getPosition()), conv(listener->getTarget() - listener->getPosition()));

	// Neue Schleife starten
	if(timer < 0 ){
		if(music_type != "") {

			if(!music_fade) {
				irrklang::ISoundSource* newsound = container->getSound(music_type);
				music_fade = engine->play2D(newsound, true, false, true);
				music_fade->setVolume(0.25);
			}
			float vol = music_fade->getVolume() / music_volume;	// relative volume
			if(music_loop)
				music_loop->setVolume( (1.0 - vol) * music_volume );
			music_fade->setVolume( (vol + 0.25 * time_sec) * music_volume);
			if(vol >= 1){
				if(music_loop)
				{
					music_loop->stop();
					music_loop->drop();
				}
				music_loop = music_fade;
				music_loop->setVolume( music_volume );
				music_fade = 0;

				// timer für neustart
				timer = (rand() % 10 + 5) + 0.0001 * (rand() % 10 + 10) * music_loop->getPlayLength();
			}
		}else{
			// nur ausblenden
			if(music_loop)
				music_loop->setVolume(music_loop->getVolume() - 0.1 * music_volume * time_sec);
			music_fade = 0;
		}
	}
	engine->update();
}

ISoundSource* CSoundManager::loadSound(const std::string& file)
{
	//! \todo prüfen, ob auch wirklich im sfx Ordner
	std::cout << "load sound: " << ("sfx/"+file) << std::endl;
	return engine->addSoundSourceFromFile(("sfx/"+file).c_str(), ESM_AUTO_DETECT, true);
}
