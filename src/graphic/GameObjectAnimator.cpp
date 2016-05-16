#include "GameObjectAnimator.h"
#include "game/IGameObjectView.h"
#include "irrlicht/ISceneNode.h"

namespace gfx
{

	GameObjectAnimator::GameObjectAnimator(const game::IGameObjectView* view) :
		mView( view )
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
		node->setPosition( convert(mView->position()) );
		node->setRotation( convert_angle( mView->angle() ) );
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
