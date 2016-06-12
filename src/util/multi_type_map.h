#ifndef MULTI_TYPE_MAP_H_INCLUDED
#define MULTI_TYPE_MAP_H_INCLUDED

#include <tuple>
#include <type_traits>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>

namespace detail
{
	namespace mpl
	{
		using namespace boost::mpl;
	}

	template<template<typename...> class Map, class Key, class... Types>
	struct Config
	{
		using type_vec = mpl::vector<Types...>;
		using key_t = Key;

		template<class T>
        using map_t = Map<Key, T>;

        using map_tuple_t = std::tuple< map_t<Types>... >;
	};

	template<class Config>
	struct MTMStorage
	{
		// helper typedefs
		using type_vec = typename Config::type_vec;
		using key_t = typename Config::key_t;
		template<class T>
		using map_t = typename Config::template map_t<T>;
		using data_t = typename Config::map_tuple_t;

		// index calculation function: in which tuple index can we
		// find the type T
		template<class T>
		static constexpr std::size_t index_of_type()
		{
			static_assert( mpl::contains<type_vec, T>::value, "type not present in MultiTypeMap" );
			return mpl::find<type_vec, T>::type::pos::value;
		}

		template<class T>
		map_t<T>& get_map()
		{
			return std::get<index_of_type<T>()>(mData);
		}

		template<class T>
		const map_t<T>& get_map() const
		{
			return std::get<index_of_type<T>()>(mData);
		}

		// here, we save all the data
		data_t mData;
	};


	// -------------------------------------------------------
	// 			user visible class
	// -------------------------------------------------------
	template<class Config>
	class MultiTypeMap
	{
		// helper typedefs
		using key_t = typename Config::key_t;

	public:

		// accessing data!
		// read accessor function to a key
		template<class T>
		const T& at(const key_t& key) const
		{
			return mData.template get_map<T>().at(key);
		}

		// r/w accessor function to a key
		template<class T>
		T& at(const key_t& key)
		{
			return mData.template get_map<T>().at(key);
		}

		// insert elements
		template<class T>
		auto insert(key_t key, T value)
			-> decltype(MTMStorage<Config>().template get_map<T>().insert({std::move(key), std::move(value)}))
		{
			return mData.template get_map<T>().insert({std::move(key), std::move(value)});
		}

	private:
		// here, we save all the data
		MTMStorage<Config> mData;
	};
}

template<template<typename...> class Map, class Key, class... Types>
using MultiTypeMap = detail::MultiTypeMap<detail::Config<Map, Key, Types...>>;

#endif // MULTI_TYPE_MAP_H_INCLUDED
