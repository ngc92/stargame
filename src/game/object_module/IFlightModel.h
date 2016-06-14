#ifndef IFLIGHTMODEL_H_INCLUDED
#define IFLIGHTMODEL_H_INCLUDED

#include "common_includes.h"

namespace game
{
	class IPropulsionSystem;

	class IFlightModel : public IGameObjectModule
	{
	public:
		// physics functions
		/// change the physical state of the object to accelerate with force thrust_vector
		virtual void thrust( b2Vec2 thrust_vector ) = 0;
		/// change the physical state of the object to turn with \p torque,
		virtual void rotate( float torque )   = 0;

		/// returns a vector containing all registered propulsion systems.
		virtual const std::vector<IPropulsionSystem*>& getPropulsionSystems() const = 0;

		// auto pilot functions
		static auto registerPropulsionSystem( std::shared_ptr<IFlightModel> model, IPropulsionSystem& propsys );

		virtual float getTerminalVelocity( float thrust ) = 0;

//		virtual void pilot( const IGameObject& ship, const SFlightState& target_state ) = 0;
	private:
		// virtual part of the registration interface
		virtual void registerPropulsionSystem_( IPropulsionSystem& propsys ) = 0;
		virtual void removePropulsionSystem_( IPropulsionSystem& propsys ) = 0;
	};

	inline auto IFlightModel::registerPropulsionSystem( std::shared_ptr<IFlightModel> model, IPropulsionSystem& propsys )
	{
		model->registerPropulsionSystem_( propsys );
		std::weak_ptr<IFlightModel> weak_model = model;
		return std::shared_ptr<void>(nullptr, [&propsys, model = std::move(weak_model)](void*)
		{
			auto lck = model.lock();
			if(lck) { lck->removePropulsionSystem_(propsys); }
		});
	}
}

#endif // IFLIGHTMODEL_H_INCLUDED
