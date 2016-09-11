# TODO GLOB
SET(DATA_SRC
    data/Body.cpp
    data/Fixture.cpp
    data/Shape.cpp
)

SET(SIMULATION_SRC
    simulation/CSimulation.cpp
    simulation/CSpawner.cpp
    simulation/SUnitConverter.cpp
)

SET(LIB_SOURCE
    ${DATA_SRC}
    ${SIMULATION_SRC}
    CPhysicsThread.cpp 
)

SET(TEST_SOURCE 
    test/Data_test.cpp
    test/Simulation_test.cpp
    test/Spawner_test.cpp
    test/CPhysicsThread_test.cpp)


add_library(physics ${LIB_SOURCE})