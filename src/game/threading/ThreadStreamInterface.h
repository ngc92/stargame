#ifndef THREADSTREAMINTERFACE_H_INCLUDED
#define THREADSTREAMINTERFACE_H_INCLUDED

/*! \file
	This file defines the classes for streaming data safely between threads.
	There are two interfaces, one that is presented to the sending thread
	IThreadStreamWriter that allows writing to the buffer, and one that is
	to be presented to the reading thread, IThreadStreamReader.
*/

#include "util/buffered_thread_stream.h"
#include <vector>

namespace game
{
	namespace threading
	{
		/*! Interface of ThreadStream that is
			visible to the writing thread. Allows pushing 
			data and publishing it to the reader.
		*/
		template<class T>
		class IThreadStreamWriter
		{
		public:
			virtual ~IThreadStreamWriter() = default;
			/// adds a new object to the internal buffer. This will not 
			/// be visible to the reading thread until publish has been called.
			virtual void push(T) = 0;
			
			/// this makes everything that was pushed up until now available to the 
			/// reading thread. Returns the number of elements that were published.
			virtual std::size_t publish() = 0;
		};

		/*! Interface of ThreadStream that is
			visible to the reading thread. Allows 
			retrieving data.
		*/
		template<class T>
		class IThreadStreamReader
		{
		public:
			virtual ~IThreadStreamReader() = default;
			/// updates the current data with whatever is available in the buffer
			/// from the writing thread. Discards all current data.
			virtual std::size_t update() = 0;
			
			/// gets a reference to the vector containing the current data.
			virtual const std::vector<T>& read() const = 0;
		};

		/*! combination of IThreadStreamWriter and IThreadStreamReader
		*/
		template<class T>
		class ThreadStream : public IThreadStreamReader<T>, public IThreadStreamWriter<T>
		{
		public:
			// writer
			void push(T e) override { return mStream.push(std::move(e)); }
			std::size_t publish() override { return mStream.publish(); }
			
			// reader
			std::size_t update() override { return mStream.update(); }
			const std::vector<T>& read() const override { return mStream.read(); }
		private:
			BufferedThreadStream<std::vector<T>> mStream;
		};
	}
}

#endif // THREADSTREAMINTERFACE_H_INCLUDED
