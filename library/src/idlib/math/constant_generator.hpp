#pragma once

#include "idlib/math/generator.hpp"

namespace id {

/// @brief A generator returning a constant value.
/// @tparam R the result type
template <typename R>
struct constant_generator : generator
{
    using result_type = R;

    constant_generator(const result_type& c = result_type())
        : m_c(c)
	{}

#if defined(_MSC_VER) // Disable sickening flood of warnings.
    #pragma warning(push)
    #pragma warning(disable: 4100)
#endif

    result_type operator()(size_t index) const
	{ return m_c; }

#if defined(_MSC_VER)
	#pragma warning(pop)
#endif

private:
    const result_type m_c;
}; // struct constant_generator

} // namespace id
