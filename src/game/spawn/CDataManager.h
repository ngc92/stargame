#ifndef CDATAMANAGER_H_INCLUDED
#define CDATAMANAGER_H_INCLUDED

#include "IDataManager.h"
#include "Definitions.h"
#include <unordered_map>

namespace game
{
	namespace spawn
	{
		class CDataManager : public IDataManager
		{
		public:
			const Component& getComponentData( const std::string& type ) const final;
			const Hull& getHullData( const std::string& type ) const final;
			const Ship& getShipData( const std::string& type ) const final;

			void loadFile( const std::string& filename ) final;
		private:
			void add( std::string name, Component data );
			void add( std::string name, Hull data );
			void add( std::string name, Ship data );

			std::unordered_map<std::string, Component> mComponentData;
			std::unordered_map<std::string, Hull> mHullData;
			std::unordered_map<std::string, Ship> mShipData;
		};
	}
}

#endif // CDATAMANAGER_H_INCLUDED
