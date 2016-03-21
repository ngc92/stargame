#include "CDebugConsole.h"

#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

CDebugConsole::CDebugConsole()
{

}

CDebugConsole::~CDebugConsole()
{
	*run_thread = false;
	mThread.detach();
}

void CDebugConsole::registerCommand(const std::string& name, command_fn func)
{
	mCommands[name] = func;
}

void CDebugConsole::startConsole()
{
	run_thread = new bool(true);
	mThread = std::thread(run, this);
}

void CDebugConsole::step()
{
	std::unique_lock<std::mutex> lock(mFunctionQueueMutex);
	while(!mFunctionQueue.empty())
	{
		mFunctionQueue.front()();
		mFunctionQueue.pop();
	}
}

void CDebugConsole::run(CDebugConsole* console)
{
	auto run_thread = console->run_thread;
	while(*run_thread)
	{
		std::string command;
		std::getline(std::cin, command);
		if(run_thread)
			console->executeCommand(command);
	}

	delete run_thread;
}

void CDebugConsole::executeCommand(const std::string& command)
{
	std::vector<std::string> cnp;
	boost::split( cnp, command, boost::is_any_of(" "), boost::token_compress_on );

	std::string command_name = cnp.at(0);

	// find that command
	auto cmd = mCommands.find(command_name);
	if( cmd == mCommands.end())
	{
		std::cerr << "invalid command " << command_name << "\n";
		return;
	}

	auto cfunc = cmd->second;
	std::unique_lock<std::mutex> lock(mFunctionQueueMutex);
	auto func = [cfunc, cnp]() -> void
	{
		cfunc( cnp );
	};

	mFunctionQueue.push(func);

}
