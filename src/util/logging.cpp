#include "logging.h"
#include <iostream>

void LOG_MESSAGE(ELogCategory category, const std::string& message)
{
	std::cout << "message: " << message << "\n";
}

void LOG_WARNING(ELogCategory category, const std::string& message)
{
	std::cout << "warning: " << message << "\n";
}


void LOG_ERROR(ELogCategory category, const std::string& message)
{
	std::cerr << "error: " << message << "\n";
}

