#include "GameObjectAnimator.h"
#include "game/IGameObjectView.h"
#include "irrlicht/ISceneNode.h"

namespace gfx
{

	GameObjectAnimator::GameObjectAnimator(const game::IGameObjectView& view) :
		mView( view.shared_from_this() )
	{
	}

	GameObjectAnimator::GameObjectAnimator(const std::weak_ptr<const game::IGameObjectView> view) :
		mView( std::move(view) )
	{

	}

	GameObjectAnimator::~GameObjectAnimator()
	{
	}

	bool GameObjectAnimator::hasFinished() const
	{
		return false;
	}

	void GameObjectAnimator::animateNode(ISceneNode* node, u32 timeMs)
	{
		auto view = mView.lock();
		if(!view)
		{

			node->removeAnimator( this );
			return;
		}
		node->setPosition( convert(view->position()) );
		node->setRotation( convert_angle( view->angle() ) );
	}

	ISceneNodeAnimator* GameObjectAnimator::createClone(ISceneNode* node, ISceneManager* newManager)
	{
		return new GameObjectAnimator(mView);
	}

	vector3df GameObjectAnimator::convert( const b2Vec2& source )
	{
		return irr::core::vector3df(source.x, 0, source.y);
	}

	vector3df GameObjectAnimator::convert_angle( float angle )
	{
		return irr::core::vector3df(0, -angle  * 180 / 3.1415, 0);
	}
}
