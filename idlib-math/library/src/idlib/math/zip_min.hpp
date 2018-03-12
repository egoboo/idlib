#pragma once

namespace idlib {

template <typename A, typename B, typename Enabled = void>
struct zip_min_functor;

template <typename A, typename B>
auto zip_min(const A& a, const B& b) -> decltype(zip_min_functor<A, B>()(a, b))
{ return zip_min_functor<A, B>()(a, b); }

} // namespace idlib
