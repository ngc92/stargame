#include "CGameObject.h"
#include <cassert>
#include "property/IProperty.h"
#include "../IGameObjectModule.h"

namespace game
{
	CGameObject::CGameObject(uint64_t id, std::string type, ObjectCategory cateogry, std::string name) :
		 CPropertyObject( std::move(name) ),
		 mIsAlive(true),
		 mID(id),
		 mType( "type", this, std::move(type) ),
		 mCategory( "category", this, (int)cateogry),
		 mLastState( b2Vec2(0, 0) ) /// \todo this is bullshit
	{
	}

	CGameObject::~CGameObject()
	{
	}

	void CGameObject::remove()
	{
		mIsAlive = false;
		mRemoveListeners.notify(*this);
	}

	void CGameObject::onInit(IGameWorld& world)
	{
		for(auto& module : mModules)
			module->onInit(*this, world);

		mInitialized = true;
	}
	
	void CGameObject::step(const IGameWorld& world, WorldActionQueue& push_action)
	{
		for(auto& module : mModules)
		{
			// check that the object is still alive before each call,
			// in case one of the modules decides to kill the object
			// in this step.
			if(isAlive())
				module->onStep(*this, world, push_action);
		}
	}

	void CGameObject::onStep(const IGameWorld& world) const
	{
		// step listeners and modules
		/// \todo this should happen after the modules, I think?
		mStepListeners.notify(*this);
		
		// update property listeners
		notifyAll();
	}

	void CGameObject::onImpact(IGameObject& other, const ImpactInfo& info)
	{
		for(auto& module : mModules)
			module->onImpact(*this, other, info);

		mImpactListeners.notify(other, info);
	}

	void CGameObject::dealDamage( const Damage& damage, const b2Vec2& pos, const b2Vec2& dir )
	{
		for(auto& module : mModules)
			module->onDamage(*this, damage, pos, dir);
	}

	b2Vec2 CGameObject::position() const
	{
		return mLastState.position();
	}

	float CGameObject::angle() const
	{
		return std::fmod(mLastState.angle(), 2 * irr::core::PI);
	}

	b2Vec2 CGameObject::velocity() const
	{
		return mLastState.velocity();
	}

	float CGameObject::angular_velocity() const
	{
		return mLastState.angular_velocity();
	}

	/// gets the object type. This is the type that
	/// was used to get the spawn data for the object.
	const std::string& CGameObject::type() const
	{
		return mType;
	}
	
	/// the category of this object. 
	ObjectCategory CGameObject::category() const
	{	
		return (ObjectCategory)(int)mCategory;
	}

	ListenerRef CGameObject::addStepListener( std::function<void(const IGameObjectView&)> lst )
	{
		return mStepListeners.addListener( std::move(lst) );
	}

	ListenerRef CGameObject::addImpactListener( std::function<void(IGameObjectView&, const ImpactInfo&)> lst )
	{
		return mImpactListeners.addListener( std::move(lst) );
	}

	ListenerRef CGameObject::addRemoveListener( std::function<void(const IGameObjectView&)> lst )
	{
		return mRemoveListeners.addListener( std::move(lst) );
	}


	uint64_t CGameObject::id() const
	{
		return mID;
	}

	bool CGameObject::isAlive() const
	{
		return mIsAlive;
	}

	void CGameObject::addModule( std::shared_ptr<IGameObjectModule> module )
	{
		// this restriction ensures that after the spawner is finished, no
		// new modules can be added.
		assert(!mInitialized);
		mModules.push_back( std::move(module) );
		addChild( mModules.back() );
	}
	
	// -----------------------------------------------------------------------
	//						constructor function
	// -----------------------------------------------------------------------
	
	std::shared_ptr<IGameObject> createGameObject( uint64_t id, std::string type, ObjectCategory category, std::string name )
	{
		return std::make_shared<CGameObject>( id, std::move(type), category, std::move(name) );
	}
}
