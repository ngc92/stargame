#include "MicroAI.h"
#include "game/IGameObject.h"
#include "game/object_module/IPropulsionSystem.h"
#include "game/object_module/IFlightModel.h"
#include "micro_behaviour.h"
#include "locomotion_solvers.h"
#include "locomotion_control.h"

namespace game
{
namespace ai
{
	class MicroAI::Registrator
	{
	public:
		Registrator(MicroAI& ai) : mMicroAI(ai) {}
		static auto reg( const std::shared_ptr<Registrator>& registrator, IPropulsionSystem& propsys )
		{
			std::weak_ptr<Registrator> weak_reg = registrator;
			return std::shared_ptr<void>(nullptr, [&propsys, registrator = std::move(weak_reg)](void*)
			{
				auto lck = registrator.lock();
				if(lck) { lck->mMicroAI.removePropulsionSystem(propsys); }
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
		mCurrentBehaviour = micro_behaviours::MoveTo{pos};
		mActive = true;
	}


	void MicroAI::act( const IGameObject& object )
	{
		if(!mActive)
			return;

		// update info
		for(const auto& s : mPropulsionSystems)
		{
			mShipInfo->mMaxThrust += s->getMaxThrust();
			mShipInfo->mMaxTorque += s->getMaxTorque();
		}

		/// \todo we're mucking about with const here, that is not nice
		IFlightModel& model = *const_cast<IGameObject&>(object).getModuleAsType<IFlightModel>();
		mShipInfo->mMaxVelocity = model.getTerminalVelocity( mShipInfo->mMaxThrust );

		Control control = apply(mCurrentBehaviour, object, *mShipInfo);

		auto steering = steer(mPropulsionSystems, control, object.body());
		for(unsigned i = 0; i < steering.size(); ++i )
		{
			mPropulsionSystems[i]->thrust( steering[i].steer.get() );
			mPropulsionSystems[i]->rotate( steering[i].rotate.get() );
		}
	}

	std::shared_ptr<void> MicroAI::registerPropulsionSystem( IPropulsionSystem& propsys )
	{
		mPropulsionSystems.push_back( &propsys );
		return Registrator::reg(mRegistrator, propsys);
	}

	void MicroAI::removePropulsionSystem( IPropulsionSystem& propsys )
	{
		auto found = std::find(begin(mPropulsionSystems), end(mPropulsionSystems), &propsys);
		if(found != end(mPropulsionSystems))
			mPropulsionSystems.erase( found );
		else
			assert(0);
	}
}
}
