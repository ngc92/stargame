#include "physics/CPhysicsThread.h"
#define BOOST_TEST_MODULE Physics
#include <boost/test/included/unit_test.hpp>

using namespace physics::detail;

BOOST_AUTO_TEST_SUITE(PhysicsThread)

BOOST_AUTO_TEST_CASE(Constructor)
{
	CPhysicsThread thread;
	BOOST_TEST( thread.is_running() == false );
}

BOOST_AUTO_TEST_CASE(StartStop)
{
	CPhysicsThread thread;
	BOOST_TEST( thread.is_running() == false );
	thread.start();
	BOOST_TEST( thread.is_running() == true );
	thread.stop();
	BOOST_TEST( thread.is_running() == false );
}

BOOST_AUTO_TEST_SUITE_END()
