#include "EngineExhaustAnimator.h"
#include "EngineExhaust.h"
#include "game/IGameObjectView.h"
#include "irrlicht/ISceneNode.h"

namespace gfx
{

	EngineExhaustAnimator::EngineExhaustAnimator(const game::IGameObjectView& view) :
		EngineExhaustAnimator( view.shared_from_this() )
	{
	}

	EngineExhaustAnimator::EngineExhaustAnimator(const std::weak_ptr<const game::IGameObjectView> view) :
		mView( std::move(view) )
	{
		// set up listeners
		auto lock = mView.lock();
	}

	EngineExhaustAnimator::~EngineExhaustAnimator()
	{
	}

	bool EngineExhaustAnimator::hasFinished() const
	{
		return false;
	}

	void EngineExhaustAnimator::animateNode(ISceneNode* _node, u32 timeMs)
	{
		auto view = mView.lock();
		if(!_node || !view || _node->getType() != irr::scene::ESNT_UNKNOWN)
		{
			_node->removeAnimator( this );
			return;
		}
		
		/// target node needs to be engine exhaust node
		EngineExhaustNode& node = dynamic_cast<EngineExhaustNode&>(*_node);
		//node.
	}

	ISceneNodeAnimator* EngineExhaustAnimator::createClone(ISceneNode* node, ISceneManager* newManager)
	{
		return new EngineExhaustAnimator(mView);
	}

	
	/// \todo factor these functions out into some common code!
	vector3df EngineExhaustAnimator::convert( const b2Vec2& source )
	{
		return irr::core::vector3df(source.x, 0, source.y);
	}

	vector3df EngineExhaustAnimator::convert_angle( float angle )
	{
		return irr::core::vector3df(0, -angle  * 180 / 3.1415, 0);
	}
}
