#pragma once

#include <string>

namespace idlib {

template <typename Character>
struct text_parser
{
	using character_type = Character;
	using string_type = std::basic_string<character_type>;
	using iterator_type = typename string_type::const_iterator;
	
	/// @param predicate function which gets if an input character is delimiter
	/// @param receiver receiving iterator pair [begin, end) denoting the span of a token 
	void
	operator()
		(
			const string_type& string,
			std::function<bool(const character_type&)> predicate,
			std::function<void(iterator_type, iterator_type, iterator_type, iterator_type)> receiver
		) const
	{
		auto begin = string.cbegin(), end = string.cend();
		auto old = begin, current = begin;
		
		while (current != end)
		{
			if (predicate(*current)) // predicate is true
			{
				if (old != current) // implies old < current
				{
					receiver(begin, end, old, current); // [old, current)
				}
				auto next = current + 1;
				receiver(begin, end, current, next); // [current, next)
				current = next;
				old = next;
			}
			else
			{
				current++;
			}
		}
		if (old != current) // implies old < current
		{
			receiver(begin, end, old, current); // [old, current)
		}
	}	
}; // struct text_parser

} // namespace idlib
