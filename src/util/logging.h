#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

#include <string>
#include <boost/lexical_cast.hpp>

enum class ELogCategory
{
	ELC_IRRLICHT,
	ELC_COLLISION,
	ELC_LEVEL,
	ELC_LUA,
	ELC_PHYSIC,
	ELC_GUI,
	STATE
};

enum class ELogLevel
{
	ELL_INFORMATION = 1,
	ELL_WARNING = 2,
	ELL_ERROR = 4
};

// free functions for logging
void LOG_MESSAGE(ELogCategory category, const std::string& message);
void LOG_WARNING(ELogCategory category, const std::string& message);
void LOG_ERROR(ELogCategory category, const std::string& message);

#endif // LOGGING_H_INCLUDED
