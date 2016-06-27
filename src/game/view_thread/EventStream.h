#ifndef EVENTSTREAM_H_INCLUDED
#define EVENTSTREAM_H_INCLUDED

#include "util/buffered_thread_stream.h"
#include "UpdateEvent.h"
#include <vector>

namespace game
{
/// \todo rename namespace and folder!
namespace view_thread
{
	class IEventStreamWriter
	{
	public:
		virtual ~IEventStreamWriter() = default;
		virtual void push(Event) = 0;
		virtual std::size_t publish() = 0;
	};

	class IEventStreamReader
	{
	public:
		virtual ~IEventStreamReader() = default;
		virtual void update() = 0;
		virtual const std::vector<Event>& read() const = 0;
	};

	class EventStream : public IEventStreamWriter, public IEventStreamReader
	{
	public:
		// info
		std::size_t cache_size() const { return mStream.cache_size(); }
		std::size_t in_data_size() const { return mStream.in_data_size(); }
		std::size_t out_data_size() const { return mStream.out_data_size(); }
			
		// writer
		void push(Event e) override { return mStream.push(std::move(e)); }
		std::size_t publish() override { return mStream.publish(); }
		
		// reader
		void update() override { return mStream.update(); }
		const std::vector<Event>& read() const override { return mStream.read(); }
	private:
		BufferedThreadStream<std::vector<Event>> mStream;
	};
}
}

#endif // EVENTSTREAM_H_INCLUDED
