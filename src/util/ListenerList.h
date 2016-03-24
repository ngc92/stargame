#ifndef LISTENERLIST_H_INCLUDED
#define LISTENERLIST_H_INCLUDED

#include <list>
#include <memory>
#include <functional>


class ListenerRef final
{
public:
	ListenerRef( std::function<void()>&& deleter ) :  mRegistered(true),
													mDeleter( deleter ) {};
	~ListenerRef() { remove(); };
	void remove()
	{
        if(mRegistered)
		{
			mRegistered = false;
			mDeleter();
		}
	}
private:
	bool mRegistered;
	std::function<void()> mDeleter;
};

template<class... Args>
class ListenerList final
{
public:
	/// add a new listener to the list.
	template<class T>
	ListenerRef addListener(T&& lst);

	/// notify all listeners in this list.
	void notify(Args&&... args);
private:
	std::list<std::function<void(Args...)>> mListenerList;
};

template<class... Args>
template<class T>
ListenerRef ListenerList<Args...>::addListener(T&& listener)
{
	std::function<void(Args...)> fun(std::forward<T>(listener));
	auto iter = mListenerList.insert(mListenerList.begin(), fun);
	auto del = [this, iter]() mutable
	{
		mListenerList.erase(iter);
	};
	return ListenerRef(del);
}

template<class... Args>
void ListenerList<Args...>::notify(Args&&... args)
{
	for(auto& lst : mListenerList)
		lst(std::forward<Args>(args)...);
}


template<>
class ListenerList<void> final
{
public:
	/// add a new listener to the list.
	template<class T>
	ListenerRef addListener(T&& lst)
	{
		std::function<void(void)> fun(std::forward<T>(lst));
		auto iter = mListenerList.insert(mListenerList.begin(), fun);
		auto del = [this, iter]() mutable
		{
			mListenerList.erase(iter);
		};
		return ListenerRef(del);
	}

	/// notify all listeners in this list.
	void notify()
	{
		for(auto& lst : mListenerList)	lst();
	}
private:
	std::list<std::function<void(void)>> mListenerList;
};

#endif // LISTENERLIST_H_INCLUDED
