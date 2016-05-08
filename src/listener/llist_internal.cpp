#include "llist_internal.h"
#include <algorithm>

namespace listener
{
	// this mutex is locked whenever we access the add queue
	std::size_t ListenerListBase::size() const
	{ 
		return mListeners.size(); 
	};
	
	void ListenerListBase::addListenerInternal(genlist_t lst)
	{
		std::lock_guard<std::mutex> lock(mChangeMutex);
		mAddQueue.push_back( std::move(lst) );
	}
	
	void ListenerListBase::update() const
	{
		const_cast<ListenerListBase*>(this)->update_impl();
	}
	
	void ListenerListBase::update_impl()
	{
		using namespace std;
		lock_guard<mutex> lock(mChangeMutex);
		
		// remove expired listeners
		auto nend = remove_if(begin(mListeners), end(mListeners), [](const genlist_t& ptr) { return ptr.expired(); });
		mListeners.resize( distance(begin(mListeners), nend) );
		
		// and add from queue
		mListeners.insert( end(mListeners), begin(mAddQueue), end(mAddQueue) );
		mAddQueue.clear();
	}
}
