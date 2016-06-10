#ifndef GAMEOBJECTANIMATOR_H_INCLUDED
#define GAMEOBJECTANIMATOR_H_INCLUDED

#include <irrlicht/ISceneNodeAnimator.h>
#include <memory>

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

	/// animator that moves an irrlicht scene node according to an igameobjectview
	class GameObjectAnimator : public ISceneNodeAnimator
	{
		public:
			GameObjectAnimator(const game::IGameObjectView& view);
			GameObjectAnimator(const std::weak_ptr<const game::IGameObjectView> view);
			virtual ~GameObjectAnimator();

			void animateNode(ISceneNode* node, u32 timeMs) override;
			ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager = 0) override;
			bool hasFinished() const override;
		private:
			vector3df convert( const b2Vec2& source );
			vector3df convert_angle( float angle );

			const std::weak_ptr<const game::IGameObjectView> mView;
	};

}

#endif // GAMEOBJECTANIMATOR_H_INCLUDED
