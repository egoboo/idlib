///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Idlib: A C++ utility library
// Copyright (C) 2017-2018 Michael Heilmann
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/range.hpp` instead)
#endif

#include "idlib/utility/platform.hpp"

#include "idlib/iterator/header.in"

// Forward declaration.
template <typename UnaryFunctor, typename Iterator>
struct transform_iterator;

#include "idlib/iterator/footer.in"

namespace std {
// std::iterator_traits specialization.
template <typename UnaryFunctor,
	      typename Iterator>
struct iterator_traits<idlib::transform_iterator<UnaryFunctor, Iterator>> {
	using reference = typename invoke_result<const UnaryFunctor, typename iterator_traits<Iterator>::reference>::type;
	using value_type = typename remove_cv<reference>::type;
	using pointer = value_type *;
	using difference_type = typename iterator_traits<Iterator>::difference_type;
	using iterator_category = typename iterator_traits<Iterator>::iterator_category;
}; // struct iterator_traits

} // namespace std

#include "idlib/iterator/header.in"

/// @brief An iterator wrapping another iterator and subjecting the value of the other iterator to a tranformation function before returning it.
/// @tparam Transformer the type of a transformer functor. Must provide the @code{TargetReferenceType operator()(SourceReferenceType&)} operator.
template <typename UnaryFunctor, typename Iterator>
struct transform_iterator
{
	using my_type = transform_iterator<UnaryFunctor, Iterator>;
	using my_iterator_traits = std::iterator_traits<my_type>;


	using value_type = typename my_iterator_traits::value_type;
	using reference = typename my_iterator_traits::reference;
	using pointer = typename my_iterator_traits::pointer;
	using difference_type = typename my_iterator_traits::difference_type;

	/*
	using source_value_type = typename std::iterator_traits<Iterator>::value_type;
	using source_reference = typename std::iterator_traits<Iterator>::reference;
	using source_pointer = typename std::iterator_traits<Iterator>::pointer;
	*/
	using iterator_type = Iterator;
	using unary_functor_type = UnaryFunctor;

	using source_iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
	
	iterator_type m_it;
	unary_functor_type m_fn;

	/// @brief Default-construct this transforming iterator.
	transform_iterator() :
		m_it(), m_fn()
	{}

	/// @brief Construct this transforming iterator.
	/// @param it the source iterator
	/// @param fn the transform functor
	transform_iterator(iterator_type it, unary_functor_type fn) :
		m_it(it), m_fn(fn)
	{}
	
private:
	/// @internal
	/// @brief Increment the wrapped iterator.
	void increment()
	{
		++m_it;
	}
	
	/// @internal
	/// @brief Decrement the wrapped iterator.
	/// @remark Enabled iff the wrapped iterator is a bidirectional iterator.
	std::enable_if_t<
		std::is_base_of<
			std::bidirectional_iterator_tag,
			source_iterator_category>::value, void>
	decrement()
	{
		--m_it;
	}

	/// @internal
	/// @brief Increment the wrapped iterator.
	/// @remark Enabled iff the wrapped iterator is a random access iterator.
	std::enable_if_t<
		std::is_base_of<
		std::random_access_iterator_tag,
		source_iterator_category>::value, void>
	increment(difference_type n)
	{
		m_it += n;
	}

	/// @internal
	/// @brief Decrement the wrapped iterator.
	/// @remark Enabled iff the wrapped iterator is a random access iterator.
	std::enable_if_t<
		std::is_base_of<
		std::random_access_iterator_tag,
		source_iterator_category>::value, void>
	decrement(difference_type n)
	{
		m_it -= n;
	}
	
	/// @internal
	/// @brief Compare this transform iterator with another transform iterator for equality.
	/// @param other the other transform iterator
	/// @return @a true if this transform iterator is equal to the other transform iterator
	bool equal(const transform_iterator& other) const
	{
		return m_it == other.m_it;
	}
	
public:
	transform_iterator(const transform_iterator&) = default;
	transform_iterator& operator=(const transform_iterator&) = default;

public:
	/// @brief Get if this transform iterator is equal to another transform iterator.
	/// @param other the other transform iterator
	/// @return @a true if this transform iterator is equal to the other transform iterator
    bool operator==(const transform_iterator& other) const
    {
        return equal(other);
    }

	/// @brief Get if this transform iterator is not equal to another transform iterator.
	/// @param other the other transform iterator
	/// @return @a true if this transform iterator is not equal to the other transform iterator
    bool operator!=(const transform_iterator& other) const
    {
        return !(*this == other);
    }

	/// @brief Pre-decrement this iterator.
	/// @return reference to this iterator
	/// @remark Enabled iff the underlying iterator is a bidirectional iterator.
	std::enable_if_t<
		std::is_base_of<
		std::bidirectional_iterator_tag,
		source_iterator_category>::value, transform_iterator&>
	operator--()
	{ decrement(); return *this; }

	/// @brief Post-decrement this iterator.
	/// @return copy of this iterator before its decrement
	/// @remark Enabled iff the underlying iterator is a bidirectional iterator.
	std::enable_if_t<
		std::is_base_of<
		std::bidirectional_iterator_tag,
		source_iterator_category>::value, transform_iterator>
	operator--(int)
	{ auto it = *this; ++(*this); return it; }

	/// @brief Increment this iterator.
	/// @param n the amount to increment this iterator by
	/// @return a reference to this iterator
	/// @remark Enabled iff the underlying iterator is a bidirectional iterator.
	std::enable_if_t<
		std::is_base_of<
		std::random_access_iterator_tag,
		source_iterator_category>::value, transform_iterator&>
	operator+=(difference_type n)
	{
		increment(n);
		return *this;
	}

	/// @brief Decrement this iterator.
	/// @param n the amount to increment this iterator by
	/// @return a reference to this iterator
	/// @remark Enabled iff the underlying iterator is a bidirectional iterator.
	std::enable_if_t<
		std::is_base_of<
		std::random_access_iterator_tag,
		source_iterator_category>::value, transform_iterator&>
	operator-=(difference_type n)
	{
		decrement(n);
		return *this;
	}

	/// @brief Increment this iterator.
	/// @param n the amount to increment this iterator by
	/// @return a copy of this iterator incremented by @a n
	/// @remark Enabled iff the underlying iterator is a bidirectional iterator.
	std::enable_if_t<
		std::is_base_of<
		std::random_access_iterator_tag,
		source_iterator_category>::value, transform_iterator>
	operator+(difference_type n) const
	{
		auto it = *this;
		it.increment(n);
		return it;
	}

	/// @brief Decrement this iterator.
	/// @param n the amount to increment this iterator by
	/// @return a copy of this iterator incremented by @a n
	/// @remark Enabled iff the underlying iterator is a bidirectional iterator.
	std::enable_if_t<
		std::is_base_of<
		std::random_access_iterator_tag,
		source_iterator_category>::value, transform_iterator>
	operator-(difference_type n) const
	{
		auto it = *this;
		it.decrement(n);
		return it;
	}

	/// @brief Pre-increment this iterator.
	/// @return reference to this iterator
    transform_iterator& operator++()
	{ increment(); return *this; }
    
	/// @brief Post-increment this iterator.
	/// @return copy of this iterator before its increment
	transform_iterator operator++(int)
	{ auto it = *this; ++(*this); return it; }

	/// @brief Dereference this iterator.
	/// @return the reference_type value this iterator is pointing to
	reference operator*() const
	{ return m_fn(*m_it); }	

	iterator_type& get_it()
	{
		return m_it;
	}

	const iterator_type& get_it() const
	{
		return m_it;
	}
};

#include "idlib/iterator/footer.in"
