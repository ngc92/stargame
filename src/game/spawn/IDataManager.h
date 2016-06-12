#ifndef DATAMANAGER_H_INCLUDED
#define DATAMANAGER_H_INCLUDED

#include <string>

namespace game
{
	namespace spawn
	{
		class SComponent;
		class SHull;
		class SShip;
		class SProjectile;

		/*! \class IDataManager
			\brief This class is responsible for containing all the data on all game objects.
			\details Provides a function for loading such data from a file, an functions for
					getting the data for the specified type.
					All functions throw exceptions if the type is not found.
		*/
		class IDataManager
		{
		public:
			virtual ~IDataManager() = default;
			virtual const SComponent& getComponentData( const std::string& type ) const = 0;
			virtual const SHull& getHullData( const std::string& type ) const = 0;
			virtual const SShip& getShipData( const std::string& type ) const = 0;
			virtual const SProjectile& getProjectileData( const std::string& type ) const = 0;

			virtual void loadFile( const std::string& filename ) = 0;
		};
	}
}

#endif // DATAMANAGER_H_INCLUDED
