#ifndef LISTENER_H_INCLUDED
#define LISTENER_H_INCLUDED

#include <memory>
#include <future>

namespace listener
{
	class ListenerBase
	{
	public:
		ListenerBase() = default;
		virtual ~ListenerBase() = default;
		ListenerBase(ListenerBase&&) = default;
		ListenerBase& operator=(ListenerBase&&) = default;
	};

	template<class T>
	struct Listener : public ListenerBase
	{
		Listener(std::function<T> f) : notify( std::move(f) ) {};
		std::function<T> notify;
	};

	/*! \brief typedef for references to listeners, returned by all addListener calls
		\details This is a reference to a listener that works as follows:
			It is a shared_ptr ot a ListenerBase Object. Inside the ListenerList,
			only a weak pointer is saved, so when the shared_ptr goes out of scope,
			the listener is automatically removed.
			This construct is wrapped into a std::future, as we cannot be sure that
			the Listener can be added immediately in a multi-threaded context.
	*/
	using ListenerRef = std::future<std::shared_ptr<ListenerBase>>;
}

using listener::ListenerRef;

#endif // LISTENER_H_INCLUDED
