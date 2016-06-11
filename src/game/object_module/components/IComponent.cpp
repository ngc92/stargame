#include "IComponent.h"
#include <map>
#include <iostream>

namespace game
{
namespace components
{
	// implementation of non-virtual component functions
	float IComponent::damage(float dam)
	{
		float actual = onDamage(dam);
		getDamageListeners().notify(actual);
		return actual;
	}
	
	
	// implementation of component registration
	namespace detail
	{
		// put into anonymous namespace, so nobody else can fiddle with it.
		namespace
		{
			using ctor_fn = std::function<std::shared_ptr<IComponent>()>;
			// a function to wrap the static variable, so nothing can go wrong with initialization order.
			std::map<std::string, ctor_fn>& getCtorList()
			{
				static std::map<std::string, ctor_fn> ctors;
				return ctors;
			}
		}
		
		void registerComponentConstructor( std::string name, ctor_fn fn )
		{
			std::cout << "REGISTER " << name << "\n";
			getCtorList().insert( {std::move(name), std::move(fn)} );
		}
	}
	
	std::shared_ptr<IComponent> construct(const std::string& type)
	{
		return detail::getCtorList().at(type)();
	}
}
}
