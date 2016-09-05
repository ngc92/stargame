#include "physics/simulation/CSimulation.h"
#include "physics/simulation/CSpawner.h"
#include "physics/actions/SpawnObject.h"
#include "physics/events/SpawnEvent.h"
#include <boost/test/unit_test.hpp>
#include <FakeIt/single_header/boost/fakeit.hpp>

using namespace physics;
using namespace physics::simulation;

BOOST_AUTO_TEST_SUITE(Simulation_test)

struct Simulation_fixture
{
	Simulation_fixture() : simulation(std::unique_ptr<CSpawner>( new CSpawner ), getListenerMock())
	{
	}
	
	fakeit::Mock<ISimulationEventListener> listener_mock;
	CSimulation simulation;
	
	std::shared_ptr<ISimulationEventListener> getListenerMock()
	{
		using namespace fakeit;
		Fake(Method(listener_mock, onObjectStateUpdate));
		Fake(Method(listener_mock, onSpawn));
		return std::shared_ptr<ISimulationEventListener>(&listener_mock.get(), [](ISimulationEventListener*){});
	}
};

BOOST_AUTO_TEST_CASE(Constructor)
{
	CSimulation simu(std::unique_ptr<CSpawner>( new CSpawner ), nullptr);
	BOOST_TEST( simu.getBodyCount() == 0u );
}

BOOST_FIXTURE_TEST_CASE(Spawn, Simulation_fixture)
{
	using namespace fakeit;
	actions::SpawnObject spawn{data::BodyDef(b2Vec2(0,0))};
	simulation.spawn( spawn );
	
	BOOST_TEST( simulation.getBodyCount() == 1u );
	Verify(Method(listener_mock, onSpawn)).Once();
}

BOOST_FIXTURE_TEST_CASE(Step, Simulation_fixture)
{
	using namespace fakeit;
	actions::SpawnObject spawn{data::BodyDef(b2Vec2(0,0))};
	simulation.spawn( spawn );
	
	BOOST_TEST_REQUIRE( simulation.getBodyCount() == 1u );
	
	simulation.step(0.1);
	
	Verify(Method(listener_mock, onObjectStateUpdate)).Once();
}

BOOST_AUTO_TEST_SUITE_END()

