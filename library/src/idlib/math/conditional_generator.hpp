#pragma once

#include "idlib/math/generator.hpp"

namespace id {

/// @brief A generator which invokes one generator \f$a\f$ if the index is equal to a specified index and another generator \f$b\f$ if it is not.
/// @tparam R the result type
template <typename A, typename B>
struct conditional_generator : generator
{
	using a_type = A;
	using b_type = B;
    conditional_generator(size_t i = size_t(),
	                      const a_type& a = a_type(),
                          const b_type& b = b_type())
        : m_i(i), m_a(a), m_b(b)
	{}

	auto operator()(size_t i) const
	{ return i == m_i ? m_a(i) : m_b(i); }

private:
    const size_t m_i;
    const a_type m_a;
    const b_type m_b;
}; // struct conditional_generator

/// @brief Utility function to ease the creation of conditional generators.
/// @tparam A, B see \ref id::conditional_generator for more information
/// @tparam i, a, b see \ref id::conditional_generator::id::conditional_generator(size_t,const A&,const &B) for more information
/// @return the conditional generator
template <typename A, typename B>
auto make_conditional_generator(size_t i, const A& a, const B& b)
{
	return conditional_generator<A, B>(i, a, b);
}

} // namespace id
