#ifndef BUFFERED_THREAD_STREAM_H_INCLUDED
#define BUFFERED_THREAD_STREAM_H_INCLUDED

#include <mutex>
#include <boost/noncopyable.hpp>

/*! \brief Buffer stream to transfer data between two threads.
	\details This class allows it to transfer data between two threads
			in such a way that always complete chunks of data will be
			transferred.
	\todo Add tests
	\todo add statistics info.
*/
template<class C>
class BufferedThreadStream
{
	using container_t = C;
public:
	// info function
	std::size_t cache_size() const { return mIncomingCache.size(); }
	std::size_t in_data_size() const { return mIncomingData.size(); }
	std::size_t out_data_size() const { return mOutgoingData.size(); }


	// writer thread functions
	/// makes all things written to the buffer available to the
	/// reader threads in one go.
	/// \return the new size of the incoming data.
    std::size_t publish()
    {
        check_writer();
        std::lock_guard<std::mutex> lock(mLockIncoming);
        std::move(begin(mIncomingCache), end(mIncomingCache), std::back_inserter(mIncomingData));
        mIncomingCache.clear();
        return mIncomingData.size();
    }

    /// add things to the buffer
	template<class T>
	void push( T&& data )
	{
		check_writer();
        mIncomingCache.push_back( std::forward<T&&>(data) );
	}


	// reader thread functions
	/// update the readable data from the write cache,
	/// and clear the write cache.
	void update()
	{
		check_reader();
		std::lock_guard<std::mutex> lock(mLockIncoming);
		std::swap(mIncomingData, mOutgoingData);
        mIncomingData.clear();
	}

	/// read the outgoing data.
	/// \note call only from reader thread.
	const container_t& read() const
	{
		check_reader();
		return mOutgoingData;
	}
private:
	container_t mIncomingCache;
	container_t mIncomingData;
	container_t mOutgoingData;
	std::mutex mLockIncoming;

	// thread debugging functions
	void check_reader() const {}
	void check_writer() const {}

};

#endif // BUFFERED_THREAD_STREAM_H_INCLUDED
