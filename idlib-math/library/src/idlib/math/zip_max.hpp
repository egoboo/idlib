#pragma once

namespace idlib {

template <typename A, typename B, typename Enabled = void>
struct zip_max_functor;

template <typename A, typename B>
auto zip_max(const A& a, const B& b) -> decltype(zip_max_functor<A, B>()(a, b))
{ return zip_max_functor<A, B>()(a, b); }

} // namespace idlib
