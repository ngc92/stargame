#ifndef ACTIONSTREAM_H_INCLUDED
#define ACTIONSTREAM_H_INCLUDED


#include "util/buffered_thread_stream.h"
#include <vector>
#include <boost/variant.hpp>

namespace game
{
/// \todo rename namespace and folder!
namespace view_thread
{
	struct ObjectAction
	{
		uint64_t target_id;
		std::function<void(IGameObject&)> action;
	};
	//using Action = boost::variant<std::function<void(IGameWorld&)>, ObjectAction>;
	using Action = ObjectAction;
	
	class IActionStreamWriter
	{
	public:
		virtual ~IActionStreamWriter() = default;
		virtual void push(Action) = 0;
		virtual std::size_t publish() = 0;
	};

	class IActionStreamReader
	{
	public:
		virtual ~IActionStreamReader() = default;
		virtual void update() = 0;
        virtual const std::vector<Action>& read() const = 0;
	};

	class ActionStream : public IActionStreamWriter, public IActionStreamReader
	{
	public:
		// writer
		void push(Action e) override { return mStream.push(std::move(e)); }
		std::size_t publish() override { return mStream.publish(); }
		
		// reader
		void update() override { return mStream.update(); }
		const std::vector<Action>& read() const override { return mStream.read(); }
	private:
		BufferedThreadStream<std::vector<Action>> mStream;
	};
}
}

#endif // ACTIONSTREAM_H_INCLUDED
