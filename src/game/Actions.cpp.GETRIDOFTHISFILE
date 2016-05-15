#include "Actions.h"
#include "../FlightModel.h"
#include "IComponent.h"

namespace game
{
	namespace actions
	{
		// ------------------------------------------------------------
		// 						Thrust
		// ------------------------------------------------------------
		class Thrust : public IAction
		{
		public:
			Thrust( const IComponent& src, b2Vec2 t, float r );
			const IComponent& getSource() override { return mSource; };
			bool act( FlightModel& ) override;
		private:
			const IComponent& mSource;
			b2Vec2 mThrust;
			float mRotate;
		};

		Thrust::Thrust( const IComponent& src, b2Vec2 t, float r ) :
			mSource(src),
			mThrust(t),
			mRotate(r)
		{

		}

		bool Thrust::act( FlightModel& fm )
		{
			fm.thrust(mThrust);
			fm.rotate(mRotate);
			return true;
		}

		// ------------------------------------------------------------
		// 						Resource Request
		// ------------------------------------------------------------
		class ResourceRequest : public IAction
		{
		public:
			ResourceRequest( IComponent& src, const std::string& r );
			const IComponent& getSource() override { return mSource; };
			bool act( IComponent& ) override;
		private:
			IComponent& mSource;
			std::string mResource;
		};

		ResourceRequest::ResourceRequest( IComponent& src, const std::string& r ):
			mSource(src),
			mResource(r)
		{
		}

		bool ResourceRequest::act( IComponent& cmp )
		{
			if(cmp.canSupply( mResource ))
			{
				mSource.registerSupplier( mResource, &cmp );
			}
			// return false, so multiple components can be registered.
			return false;
		}
	}

	std::unique_ptr<IAction> makeThrustAction(const IComponent& src, b2Vec2 t, float r)
	{
		return make_unique<actions::Thrust>(src, t, r);
	}

	std::unique_ptr<IAction> makeResourceRequestAction(IComponent& src, const std::string& r)
	{
		return make_unique<actions::ResourceRequest>(src, r);
	}
}
