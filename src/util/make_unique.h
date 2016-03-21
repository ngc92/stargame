#ifndef MAKE_UNIQUE_H_INCLUDED
#define MAKE_UNIQUE_H_INCLUDED

#include <memory>
#include <utility>
#include <cstddef>
#include <type_traits>

// -----------------------------------------------------------------------------------
//   make_unique
// ----------------

namespace helpers
{
	template<class T> struct _Unique_if {
		typedef std::unique_ptr<T> _Single_object;
	};

	template<class T> struct _Unique_if<T[]> {
		typedef std::unique_ptr<T[]> _Unknown_bound;
	};

	template<class T, size_t N> struct _Unique_if<T[N]> {
		typedef void _Known_bound;
	};
}
template<class T, class... Args>
typename helpers::_Unique_if<T>::_Single_object
make_unique(Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
typename helpers::_Unique_if<T>::_Unknown_bound
make_unique(size_t n) {
	typedef typename std::remove_extent<T>::type U;
	return std::unique_ptr<T>(new U[n]());
}

template<class T, class... Args>
typename helpers::_Unique_if<T>::_Known_bound
make_unique(Args&&...) = delete;

#endif // MAKE_UNIQUE_H_INCLUDED