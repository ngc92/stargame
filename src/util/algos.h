#ifndef ALGOS_H_INCLUDED
#define ALGOS_H_INCLUDED

#include <algorithm>

template<class T, class F>
void remove_if(T& container, F&& predicate)
{
	auto nlast = std::remove_if(begin(container), end(container), predicate);
	container.resize(distance(begin(container), nlast));
}

template<class T>
void remove_expired(T& container)
{
	remove_if(container, [](const auto& o){ return o.expired(); });
}

#endif // ALGOS_H_INCLUDED
