#ifndef LISTENERLIST_H_INCLUDED
#define LISTENERLIST_H_INCLUDED

#include "llist_internal.h"

namespace listener
{
	/// this is a type safe interface to ListenerListBase
	template<class... Args>
	class ListenerList : public ListenerListBase
	{
		using listener_f = std::function<void(Args...)>;
		using listener_t = Listener<void(Args...)>;
	public:
		/// strictly typed listener adding.
		/// \note this method can be safely called from another thread or from a listener callback.
		ListenerRef addListener(listener_f lstf)
		{
			auto lst = std::make_shared<listener_t>( std::move(lstf) );
			addListenerInternal(std::static_pointer_cast<ListenerBase>(lst));
			return lst;
		}

		template<class... PArgs>
		void notify(PArgs&&... args) const
		{
			// update the listener list. This call is protected against thread interference.
			update();
			
			// then notify all listeners, without any locking.
			for(auto& lst : mListeners)
			{
				auto fob = std::dynamic_pointer_cast<listener_t>(lst.lock());
				if(fob)
					fob->notify(std::forward<PArgs>(args)...);
				/// \todo can we catch argument errors here with a static assert to improve error msg?
			}
		}
	};
}

using listener::ListenerList;

#endif // LISTENERLIST_H_INCLUDED
