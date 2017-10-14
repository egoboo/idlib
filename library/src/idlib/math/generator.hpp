
#pragma once

namespace id {

/// @ingroup math
/// @brief Generator functor. Specializations of this functor satisfiy the requirements of the <em>Generator</em> concept.
/// They define an operator() hat accepts a single parameter of type @a size_t and return a value of type @a R.
/// Furthermore a generator needs to be 
/// - <a href="http://en.cppreference.com/w/cpp/concept/DefaultConstructible">DefaultConstructible</a>,
/// - <a href="http://en.cppreference.com/w/cpp/concept/CopyAssignable">CopyAssignable</a>,
/// - <a href="http://en.cppreference.com/w/cpp/concept/Swappable">Swappable</a> and
/// - <a href="http://en.cppreference.com/w/cpp/concept/Destructible">Destructible</a>.
/// @see id::constant_generator
/// @see id::conditional_generator
struct generator
{};

} // namespace id
