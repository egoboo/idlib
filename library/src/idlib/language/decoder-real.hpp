#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#if !defined(IDLIB_PRIVATE)
#define IDLIB_PRIVATE 1
#endif

#include "idlib/language/decoder.hpp"
#include "idlib/language/classify.hpp"

#include "idlib/utility/out_of_bounds_error.hpp"
#include "idlib/utility/invalid_argument_error.hpp"


#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace id { namespace c {

namespace internal {

// Helper functor for string to floating-point conversion.
template <typename X>
struct to_floating_point;

template <>
struct to_floating_point<single>
{
	single operator()(const std::string& x, std::size_t* n) const
	{ return std::stof(x, n); }
};

template <>
struct to_floating_point<double>
{
	double operator()(const std::string& x, std::size_t* n) const
	{ return std::stod(x, n); }
};

template <>
struct to_floating_point<quadruple>
{
	quadruple operator()(const std::string& x, std::size_t *n) const
	{ return std::stold(x, n); }
};

} // namespace internal
	
/// @brief Specialization of id::c::decoder for decoding <c>real</c> literals.
/// @tparam V the type of the values to decode the <c>real</c> literal to
template <typename T>
struct decoder<T, std::enable_if_t<internal::is_real<T>::value>>
{
    bool operator()(const std::string& source, T& target) const
	{
        static_assert(internal::is_real<T>::value,
                      "T must be a real type");
        try
		{
            try
			{
                if (source.empty() || isspace(source[0]))
				{
                    throw invalid_argument_error(__FILE__, __LINE__, "not a valid real literal");
                }
                size_t pos;
                T x;
                try
				{
                    x = internal::to_floating_point<T>()(source, &pos);
                } 
				catch (const std::invalid_argument&)
				{
                    throw invalid_argument_error(__FILE__, __LINE__, "conversion failed");
                }
				catch (const std::out_of_range&)
				{
                    throw out_of_bounds_error(__FILE__, __LINE__, "conversion failed");
                }
                if (pos != source.length())
				{
                    throw invalid_argument_error(__FILE__, __LINE__, "not a valid real literal");
                }
                target = x;
            }
			catch (const out_of_bounds_error&)
			{
                return false;
            }
			catch (const invalid_argument_error&)
			{
                return false;
            }
        }
		catch (...)
		{
            return false;
        }
        return true;
    }
}; // struct decoder
	
} } // namespace id::c
