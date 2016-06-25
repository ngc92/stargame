#ifndef IGAMEOBJECT_H_INCLUDED
#define IGAMEOBJECT_H_INCLUDED

#include "IGameObjectView.h"
#include <vector>

class b2Body;

namespace game
{
	namespace physics
	{
		class Body;
	}
	using physics::Body;

	class IGameWorld;
	class IGameObjectModule;
	class WorldActionQueue;
	class Damage;

	/*! \class IGameObject
		\brief Base class for GameObjects.
		\details This class is the base for all Game Objects, i.e. objects that are present
				inside the game world. These objects implement a property object. Functions
				related to observing the game object are declare in IGameObjectView.
	*/
	class IGameObject : public IGameObjectView,
						public virtual property::IPropertyObject
	{
	protected:
		using module_vec = std::vector<std::shared_ptr<IGameObjectModule>>;
		using module_iter = module_vec::iterator;
	public:
		/// called just after the object is constructed and added to the world.
		virtual void onInit(IGameWorld& world) = 0;
		
		/// perform a step. 
		virtual void step(const IGameWorld& world, WorldActionQueue& push_action) = 0;

		/// this function will be called every step by the game world, and should trigger
		/// the onStep listener and notify any change listener.
		virtual void onStep(const IGameWorld& world) const = 0;

		/// this function is called whenever another game object hits the current one.
		virtual void onImpact(IGameObject& other, const ImpactInfo& info) = 0;

		/// call this function to deal damage to this game object.
		virtual void dealDamage( const Damage& damage, const b2Vec2& pos, const b2Vec2& dir ) = 0;

		/// get a pointer to the internal body, if any
		virtual const Body& body() const = 0;

		/// get a pointer to the internal body, if any
		virtual Body& getBody() = 0;

		/// marks this body for deletion.
		virtual void remove() = 0;

		/// collision filter data. This is currently very specialised, so maybe a more general
		/// interface would be nice. However, we need to ensure that this does not cost performance for objects
		/// that do not require special collision handling.
		/// Right now, we can set one specific body with which this object shall not collide.
		virtual const b2Body* ignoreCollisionTarget() const = 0;

		/// sets the body which shall be ignored upon collision checks
		virtual void setIgnoreCollisionTarget( const b2Body* ignore ) = 0;

		// modules
		/// adds a module to this game object. All modules have to be
		/// added before the call to onInit. Trying to add a module afterwards will
		/// trigger an assert or an exception.
		virtual void addModule( std::shared_ptr<IGameObjectModule> ) = 0;

		/// gets a module converted to a certain type.
		/// \return module dynamic_cast'ed to the correct type, or nullptr
		template<class T>
		std::shared_ptr<T> getModuleAsType();

		// iteration functions
		module_iter module_begin() { return getModules().begin(); }
		module_iter module_end() { return getModules().end(); }

	private:
		virtual module_vec& getModules() = 0;
	};

	// helper functions
	template<class T>
	std::shared_ptr<T> IGameObject::getModuleAsType()
	{
		for(auto& module : getModules())
		{
			// try to cast to desired type
			auto ptr = std::dynamic_pointer_cast<T>(module);
			if(ptr) return ptr;
		}
		return nullptr;
	}
	
	
	// constructor function
	/// creates an object of IGameObject using the default implementation.
	std::shared_ptr<IGameObject> createGameObject( uint64_t id, std::string type, ObjectCategory category, b2Body* b, std::string name = "object" );
}

#endif // IGAMEOBJECT_H_INCLUDED
