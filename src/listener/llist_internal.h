#ifndef LLIST_INTERNAL_H_INCLUDED
#define LLIST_INTERNAL_H_INCLUDED

#include <memory>
#include <vector>
#include <mutex>
#include "listener.h"

namespace listener
{
	class ListenerListBase
	{
		using genlist_t = std::weak_ptr<ListenerBase>;
	public:
		ListenerListBase() = default;
		ListenerListBase(ListenerListBase&&) = default;
		ListenerListBase& operator=(ListenerListBase&&) = default;

		/// gets the number of listeners currently active. (i.e. does not count the queue)
		std::size_t size() const noexcept;

		/// update the listener list. add from queue and remove expired ones.
		void update() const;

	protected:
		/// add a listener to the "add queue"
		void addListenerInternal(genlist_t lst);

		/// weak pointers to all listeners that are managed here
		std::vector<genlist_t> mListeners;

	private:
		void update_impl();

		/// queue of listeners waiting to be added
		std::vector<genlist_t> mAddQueue;

		/// this mutex will always be locked when we change mutexes.
		mutable std::mutex mChangeMutex;
	};
}

#endif // LLIST_INTERNAL_H_INCLUDED
