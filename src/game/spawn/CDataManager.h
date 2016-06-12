#ifndef CDATAMANAGER_H_INCLUDED
#define CDATAMANAGER_H_INCLUDED

#include "IDataManager.h"
#include "Definitions.h"
#include "SComponent.h"
#include "SHull.h"
#include "SShip.h"
#include "SProjectile.h"
#include "util/multi_type_map.h"
#include <unordered_map>

namespace game
{
	namespace spawn
	{
		class CDataManager : public IDataManager
		{
		public:
			const SComponent& getComponentData( const std::string& type ) const final;
			const SHull& getHullData( const std::string& type ) const final;
			const SShip& getShipData( const std::string& type ) const final;
			const SProjectile& getProjectileData( const std::string& type ) const final;

			void loadFile( const std::string& filename ) final;

		private:
			MultiTypeMap<std::unordered_map, std::string, SComponent, SHull, SShip, SProjectile> mData;
		};
	}
}

#endif // CDATAMANAGER_H_INCLUDED
