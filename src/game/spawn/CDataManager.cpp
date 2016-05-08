#include "CDataManager.h"
#include <boost/property_tree/xml_parser.hpp>
#include <algorithm>
#include <iostream>

namespace game
{
namespace spawn
{
	const Component& CDataManager::getComponentData( const std::string& type) const
	{
		return mComponentData.at(type);
	}

	const Hull& CDataManager::getHullData( const std::string& type ) const
	{
		return mHullData.at(type);
	}

	const Ship& CDataManager::getShipData( const std::string& type ) const
	{
		return mShipData.at(type);
	}

	void CDataManager::add( std::string name, Component data )
	{
		mComponentData.insert({std::move(name), std::move(data)});
	}

	void CDataManager::add( std::string name, Hull data )
	{
		mHullData.insert( {std::move(name), std::move(data)} );
	}

	void CDataManager::add( std::string name, Ship data )
	{
		mShipData.insert( {std::move(name), std::move(data)} );
	}

	void CDataManager::loadFile( const std::string& filename )
	{
		using namespace boost::property_tree;
		ptree tree;
		read_xml(filename, tree);
		for(auto& data : tree)
		{
			if(data.first == "component")
			{
				std::string name = data.second.get<std::string>("name");
				add(std::move(name), Component(data.second));
			}
			else if (data.first == "hull")
			{
				std::string name = data.second.get<std::string>("name");
				add(std::move(name), Hull(data.second));
			}
			else if (data.first == "ship")
			{
				std::string name = data.second.get<std::string>("name");
				add(std::move(name), Ship(data.second));
			}
		}
	}

}}
