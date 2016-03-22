#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include "ISoundManager.h"

namespace irrklang
{
	class ISoundSource;
	class ISoundEngine;
}

class CSoundManager: public ISoundManager
{
	public:
		CSoundManager();
		~CSoundManager();

		void setListener(const irr::scene::ICameraSceneNode* cam) override;
		void update(float time_sec) override;

		// playback functions
		bool play(const irr::core::vector3df& origin, const std::string& event) override;
		irrklang::ISound* playWithFeedback( const irr::core::vector3df origin, const std::string& event ) override;
		void playMusic(const std::string& type) override;

	private:
		irrklang::ISoundSource* loadSound(const std::string& file);

		irrklang::ISoundEngine* engine;
		struct EventContainer;
		EventContainer* container;

		// Musikverwaltung
		irrklang::ISound* music_loop;
		irrklang::ISound* music_fade;
		float timer;
		std::string music_type;

		bool mute;
		double effect_volume;
		double music_volume;

		const irr::scene::ICameraSceneNode* listener;

};

#endif // SOUNDMANAGER_H_INCLUDED
