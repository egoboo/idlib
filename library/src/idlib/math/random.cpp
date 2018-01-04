// Copyright Michael Heilmann 2016, 2017, 2018.
//
// This file is part of Idlib.
//
// Idlib is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Idlib is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Idlib. If not, see <http://www.gnu.org/licenses/>.

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
