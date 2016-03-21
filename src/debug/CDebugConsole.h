#ifndef CDEBUGCONSOLE_H_INCLUDED
#define CDEBUGCONSOLE_H_INCLUDED

#include "IDebugConsole.h"
#include <thread>
#include <mutex>
#include <unordered_map>
#include <queue>

class CDebugConsole : public IDebugConsole
{
	public:
		CDebugConsole();
		virtual ~CDebugConsole();

		void registerCommand(const std::string& name, command_fn) override;
		void startConsole() override;
		void step() override;

	private:
		static void run(CDebugConsole* console);

		void executeCommand(const std::string& command);

		std::thread mThread;
		std::unordered_map<std::string, command_fn> mCommands;
		std::queue<std::function<void()>> mFunctionQueue;
		std::mutex mFunctionQueueMutex;
		bool* run_thread;
};

#endif // CDEBUGCONSOLE_H_INCLUDED
