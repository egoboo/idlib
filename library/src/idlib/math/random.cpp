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

#include "idlib/math/random.hpp"

namespace id {
	
struct rng_implementation
{
	rng_implementation() :
		generator(time(nullptr))
	{}
	
    single next(const interval<single>& interval)
    {
        auto min = interval.lower();
        auto max = std::nextafter(interval.upper(), std::numeric_limits<single>::max());
        std::uniform_real_distribution<single> distribution(min, max);
        return distribution(generator);
    }

    double next(const interval<double>& interval)
    {
        auto min = interval.lower();
        auto max = std::nextafter(interval.upper(), std::numeric_limits<double>::max());
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(generator);
    }
	
	quadruple next(const interval<quadruple>& interval)
	{
        auto min = interval.lower();
        auto max = std::nextafter(interval.upper(), std::numeric_limits<quadruple>::max());
        std::uniform_real_distribution<quadruple> distribution(min, max);
        return distribution(generator);		
	}
	
	int next(const interval<int>& interval)
	{
        auto min = interval.lower();
        auto max = interval.upper();
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }
	
private:
    /// @brief Mersenne Twister randomizer.
    std::mt19937 generator;
	
}; // rng_implementation

rng::rng() :
	m_implementation(std::make_unique<rng_implementation>())
{}

rng::~rng()
{}

rng::rng(rng&& other) :
	m_implementation(std::move(other.m_implementation))
{}

rng& rng::operator=(rng&& other)
{ 
	m_implementation = std::move(other.m_implementation);
	return *this;
}

single rng::next(const interval<single>& interval)
{ return m_implementation->next(interval); }

double rng::next(const interval<double>& interval)
{ return m_implementation->next(interval); }

quadruple rng::next(const interval<quadruple>& interval)
{ return m_implementation->next(interval); }

int rng::next(const interval<int>& interval)
{ return m_implementation->next(interval); }
    
} // namespace id
