#include "EngineExhaustAnimator.h"
#include "EngineExhaust.h"
#include "game/IGameObjectView.h"
#include "irrlicht/ISceneNode.h"
#include <regex>
#include <iostream>

namespace gfx
{

	EngineExhaustAnimator::EngineExhaustAnimator(const game::IGameObjectView& view, EngineExhaustAnimatorConfig config) :
		EngineExhaustAnimator( view.shared_from_this(), std::move(config) )
	{
	}

	EngineExhaustAnimator::EngineExhaustAnimator(const std::weak_ptr<const game::IGameObjectView> view, EngineExhaustAnimatorConfig config) :
		mView( std::move(view) ), mConfig( std::move(config) )
	{
		std::cout << "EEA\n";
		// set up listeners
		auto lock = mView.lock();
		std::cout << *lock << " - " << mConfig.mIntensitySource << "\n";
		//assert(lock->hasProperty( mConfig.mIntensitySource ));
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
		
		// target node needs to be engine exhaust node
		EngineExhaustNode& node = dynamic_cast<EngineExhaustNode&>(*_node);
		
		// get intensity from ship def
		auto intensity = boost::get<float>(view->getProperty( mConfig.mIntensitySource ).value());
		node.setIntensity( intensity );
		node.setShipVelocity( convert(view->velocity()) );
	}

	ISceneNodeAnimator* EngineExhaustAnimator::createClone(ISceneNode* node, ISceneManager* newManager)
	{
		return new EngineExhaustAnimator(mView, mConfig);
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
