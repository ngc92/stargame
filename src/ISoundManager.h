#ifndef ISOUNDMANAGER_H_INCLUDED
#define ISOUNDMANAGER_H_INCLUDED

#include <string>
#include <irrlicht/vector3d.h>
#include "util.h"

namespace irr
{
	namespace scene
	{
		class ICameraSceneNode;
	}
}

namespace irrklang
{
	class ISound;
}

class ISoundManager : noncopyable
{
	public:
		ISoundManager() = default;
		virtual ~ISoundManager() = default;

		virtual void setListener(const irr::scene::ICameraSceneNode* cam) = 0;
		virtual void update(float time_sec) = 0;

		// playback functions
		virtual bool play(const irr::core::vector3df& origin, const std::string& event) = 0;
		virtual irrklang::ISound* playWithFeedback( const irr::core::vector3df origin, const std::string& event ) = 0;
		virtual void playMusic(const std::string& type) = 0;

};

#endif // ISOUNDMANAGER_H_INCLUDED
