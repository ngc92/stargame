#include "CDataManager.h"
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

namespace game
{
namespace spawn
{
	// ---------------------------------------------------------------------------
	//		get functions - trivial implementation
	// ---------------------------------------------------------------------------
	const SComponent& CDataManager::getComponentData( const std::string& type) const
	{
		return mData.at<SComponent>(type);
	}

	const SHull& CDataManager::getHullData( const std::string& type ) const
	{
		return mData.at<SHull>(type);
	}

	const SShip& CDataManager::getShipData( const std::string& type ) const
	{
		return mData.at<SShip>(type);
	}

	const SProjectile& CDataManager::getProjectileData( const std::string& type ) const
	{
		return mData.at<SProjectile>(type);
	}

	// ------------------------------------------------------------
	//			load function
	// ------------------------------------------------------------

	// helper function that constructs an object from a ptree and
	// adds it to the Map \p map.
	template<class Read, class Map>
	void addData(const boost::property_tree::ptree& data, Map& map)
	{
		map.insert(data.template get<std::string>("name"), Read(data));
	}

	void CDataManager::loadFile( const std::string& filename )
	{
		using namespace boost::property_tree;
		ptree tree;
		read_xml(filename, tree);
		for(auto& data : tree)
		{
			/// \todo can we automate this code further?
			if(data.first == "component") addData<SComponent>(data.second, mData);
			else if (data.first == "hull") addData<SHull>(data.second, mData);
			else if (data.first == "ship") addData<SShip>(data.second, mData);
			else if (data.first == "projectile") addData<SProjectile>(data.second, mData);
		}
	}

}}
