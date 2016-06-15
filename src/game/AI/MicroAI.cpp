#include "MicroAI.h"
#include "game/IGameObject.h"
#include "game/object_module/IFlightModel.h"
#include "IPropulsionSystem.h"
#include "IWeaponSystem.h"
#include "micro_behaviour.h"
#include "locomotion_solvers.h"
#include "locomotion_control.h"
#include <iostream>
#include "util/io.h"

namespace game
{
namespace ai
{
	class MicroAI::Registrator
	{
	public:
		Registrator(MicroAI& ai) : mMicroAI(ai) {}

		template<class System>
		static auto reg( const std::shared_ptr<Registrator>& registrator, System& sys )
		{
			std::weak_ptr<Registrator> weak_reg = registrator;
			return std::shared_ptr<void>(nullptr, [&sys, registrator = std::move(weak_reg)](void*)
			{
				auto lck = registrator.lock();
				if(lck) { lck->mMicroAI.removeSystem(sys); }
			});
		}
	private:
		MicroAI& mMicroAI;
	};

	MicroAI::MicroAI(  ) : mRegistrator( std::make_shared<Registrator>(*this) ),
							mShipInfo( std::make_unique<ShipInfo>() )
	{
	}

	MicroAI::~MicroAI()
	{
	}

	void MicroAI::move_to(b2Vec2 pos)
	{
		mCurrentBehaviours.clear();
		mCurrentBehaviours.push_back(micro_behaviours::MoveTo{pos});
	}


	void MicroAI::act( const IGameObject& object )
	{
		assert( object.isAlive() );

		// update info
		for(const auto& s : mPropulsionSystems)
		{
			mShipInfo->mMaxThrust += s->getMaxThrust();
			mShipInfo->mMaxTorque += s->getMaxTorque();
		}

		/// \todo we're mucking about with const here, that is not nice
		IFlightModel& model = *const_cast<IGameObject&>(object).getModuleAsType<IFlightModel>();
		mShipInfo->mMaxVelocity = model.getTerminalVelocity( mShipInfo->mMaxThrust );

		Control control(b2Vec2(0,0), 0.f, 0.f);
		for(auto& behaviour : mCurrentBehaviours)
		{
			Control ctrl = apply(behaviour, object, *mShipInfo);
			if(ctrl.steer)
				control.steer = ctrl.steer.get();
			if(ctrl.rotate)
				control.rotate = ctrl.rotate.get();
		}

		auto steering = steer(mPropulsionSystems, control, object.body());
		for(unsigned i = 0; i < steering.size(); ++i )
		{
			mPropulsionSystems[i]->thrust( steering[i].steer.get() );
			mPropulsionSystems[i]->rotate( steering[i].rotate.get() );
		}

		for(auto& wpn : mWeaponSystems)
			wpn->fire();
	}

	std::shared_ptr<void> MicroAI::registerPropulsionSystem( IPropulsionSystem& propsys )
	{
		mPropulsionSystems.push_back( &propsys );
		return Registrator::reg(mRegistrator, propsys);
	}

	std::shared_ptr<void> MicroAI::registerWeaponSystem( IWeaponSystem& ws )
	{
		mWeaponSystems.push_back( &ws );
		return Registrator::reg(mRegistrator, ws);
	}

	void MicroAI::removeSystem( IPropulsionSystem& propsys )
	{
		auto found = std::find(begin(mPropulsionSystems), end(mPropulsionSystems), &propsys);
		if(found != end(mPropulsionSystems))
			mPropulsionSystems.erase( found );
		else
			assert(0);
	}

	void MicroAI::removeSystem( IWeaponSystem& propsys )
	{
		auto found = std::find(begin(mWeaponSystems), end(mWeaponSystems), &propsys);
		if(found != end(mWeaponSystems))
			mWeaponSystems.erase( found );
		else
			assert(0);
	}
}
}
