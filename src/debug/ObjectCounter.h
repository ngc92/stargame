#ifndef OBJECTCOUNTER_H_INCLUDED
#define OBJECTCOUNTER_H_INCLUDED

#include <typeinfo>
#include <iosfwd>
/// \todo split this file -> move memory report function somewhere else
#include <functional>

// forward declarations of internally used functions
/// counts the creation of \p type
void count(const std::type_info& type);
/// counts the destruction of \p type
void uncount(const std::type_info& type);

/*! \class ObjectCounter
	\brief Base for dynamically allocated objects
	\details Every class \p T that is expected to have instances that are dynamically allocated should be derived
				by ObjectCounter<T>. This enables memory consumption tracking for this class. A report of total tracked
				memory can be written to a stream via the report function, for single object types use getTypeMemReport()
	\todo what about move c'tor and move assignment?
*/
template<class Base>
class ObjectCounter
{
	public:
		/// c'tor, counts the creation
		ObjectCounter()
		{
			count(typeid(Base));
		};

		/// d'tor, counts destruction
		~ObjectCounter()
		{
			uncount(typeid(Base));
		};

		/// copy c'tor, counts the creation
		ObjectCounter(const ObjectCounter&)
		{
			count(typeid(Base));
		}

		/// assingment, does nothing
		/// \todo do we need this method
		ObjectCounter& operator=(const ObjectCounter&)
		{
			return *this;
		}
};

/*! \struct CountingReport
	\brief contains counting info for a single type
*/
struct CountingReport
{
	CountingReport() : alive(0), created(0)
	{

	}
	///! how many object are currently alive
	int alive;
	///! how many object have been created in total
	int created;
};

/// writes a complete memory report to stream
void report(std::ostream& stream);

/// writes a custom report
void report( std::function<void(std::string, CountingReport)> f );

/// gets the memory report of a single type
CountingReport getMemoryReport(const std::type_info& type);

/// gets the memory report of a single type
template<class T>
CountingReport getTypeMemReport()
{
	return getMemoryReport(typeid(T));
}


#endif // OBJECTCOUNNER_H_INCLUDED
