#ifndef IDEBUGCONSOLE_H_INCLUDED
#define IDEBUGCONSOLE_H_INCLUDED

#include <functional>
#include <string>
#include <vector>
#include "util.h"

class IDebugConsole : public noncopyable
{
	public:
	virtual ~IDebugConsole() {};

	typedef std::function<void(const std::vector<std::string>)> command_fn;

	virtual void registerCommand(const std::string& name, command_fn func) = 0;

	virtual void startConsole() = 0;

	virtual void step() = 0;
};

#endif // IDEBUGCONSOLE_H_INCLUDED
