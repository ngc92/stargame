#ifndef ENGINEEXHAUSTCTRL_H_INCLUDED
#define ENGINEEXHAUSTCTRL_H_INCLUDED

#include <irrlicht/ISceneNodeAnimator.h>
#include "listener/listener.h"
#include <memory>
#include <vector>

namespace game
{
	class IGameObjectView;
}

class b2Vec2;

namespace gfx
{
	using namespace irr;
	using namespace scene;
	using namespace core;
	
	/*struct EngienExhaustEffectConfig
	{
		std::string 
	};*/

	/// animator that moves an irrlicht scene node according to an igameobjectview
	class EngineExhaustAnimator : public ISceneNodeAnimator
	{
		public:
			EngineExhaustAnimator(const game::IGameObjectView& view);
			EngineExhaustAnimator(const std::weak_ptr<const game::IGameObjectView> view);
			virtual ~EngineExhaustAnimator();

			void animateNode(ISceneNode* node, u32 timeMs) override;
			ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager = 0) override;
			bool hasFinished() const override;
		private:
			vector3df convert( const b2Vec2& source );
			vector3df convert_angle( float angle );

			const std::weak_ptr<const game::IGameObjectView> mView;
			std::vector<ListenerRef> mListeners;
	};

}

#endif // ENGINEEXHAUSTCTRL_H_INCLUDED
