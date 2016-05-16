#ifndef DATAMANAGER_H_INCLUDED
#define DATAMANAGER_H_INCLUDED

#include <string>

namespace game
{
	namespace spawn
	{
		class Component;
		class Hull;
		class Ship;
		class Projectile;

		class IDataManager
		{
		public:
			virtual ~IDataManager() = default;
			virtual const Component& getComponentData( const std::string& type ) const = 0;
			virtual const Hull& getHullData( const std::string& type ) const = 0;
			virtual const Ship& getShipData( const std::string& type ) const = 0;
			virtual const Projectile& getProjectileData( const std::string& type ) const = 0;

			virtual void loadFile( const std::string& filename ) = 0;
		};
	}
}

#endif // DATAMANAGER_H_INCLUDED
