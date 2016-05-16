#ifndef IGAMEOBJECT_H_INCLUDED
#define IGAMEOBJECT_H_INCLUDED

#include "IGameObjectView.h"
#include <vector>

namespace game
{
	class IGameWorld;
	class IGameObjectModule;

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

		/// this function will be called every step by the game world, and should trigger
		/// the onStep listener.
		virtual void onStep(IGameWorld& world) = 0;

		/// this function is called whenever another game object hits the current one.
		virtual void onImpact(IGameObject* other, const ImpactInfo& info) = 0;

		/// get a pointer to the internal body, if any
		virtual const b2Body* body() const = 0;

		/// get a pointer to the internal body, if any
		virtual b2Body* getBody() = 0;

		/// marks this body for deletion.
		virtual void remove() = 0;

		// modules
		/// adds a module to this game object.
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
}

#endif // IGAMEOBJECT_H_INCLUDED
