#pragma once

namespace id {

/// @tparam T the target typedef
/// @tparam S the source typedef
/// @tparam E for SFINAE
template <typename T, typename S, typename E = void>
struct semantic_cast_functor {};

/// @brief Default implementation for identity conversion.
/// @tparam T the source and the target type
template <typename T>
struct semantic_cast_functor<T, T, void>
{
	auto operator()(const T& v) const
	{ return v; }
}; // struct semantic_cast_functor

template <typename T, typename S>
auto semantic_cast(const S& s)
{ return semantic_cast_functor<T, S, void>()(s); }

} // namespace id
