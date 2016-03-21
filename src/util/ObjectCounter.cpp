#include "ObjectCounter.h"
#include <string>
#include <unordered_map>
#include <typeindex>
#include <iostream>

// gets the map which contains all the counts. Implemented as a function to prevent
// uninitialized memory access when counting the creation of static object
std::unordered_map<std::type_index, CountingReport>& GetCounterMap()
{
	static std::unordered_map<std::type_index, CountingReport> CounterMap;
	return CounterMap;
}

void count(const std::type_info& type)
{
	// if not already counted, create a new record
	/// \todo this method could be optimized
	if(GetCounterMap().find(type) == GetCounterMap().end() )
	{
		GetCounterMap()[type] = CountingReport();
	}

	// increment created and alive
	GetCounterMap()[type].created++;
	GetCounterMap()[type].alive++;
}

void uncount(const std::type_info& type)
{
	// no check whether type exists, we assume these methods are only used as intended
	// decrement alive
	GetCounterMap()[type].alive--;
}

void report(std::ostream& stream)
{
	stream << "MEMORY REPORT\n";
	// iterate over all memory records
	for(auto i = GetCounterMap().begin(); i != GetCounterMap().end(); ++i)
	{
		stream << i->first.name() << "\n- - - - - - - - - -\n";
		stream << " alive:   " << i->second.alive << "\n";
		stream << " created: " << i->second.created << "\n\n";
	}
}

void report( std::function<void(std::string, CountingReport)> f )
{
	for(auto i = GetCounterMap().begin(); i != GetCounterMap().end(); ++i)
	{
		f(i->first.name(), i->second);
	}
}

CountingReport getMemoryReport(const std::type_info& type)
{
	return GetCounterMap()[type];
}
