// Copyright Michael Heilmann 2016, 2017.
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
	
struct random_implementation
{
	random_implementation() :
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
	
}; // random_implementation

random::random() :
	m_implementation(std::make_unique<random_implementation>())
{}

random::~random()
{}

random::random(random&& other) :
	m_implementation(std::move(other.m_implementation))
{}

random& random::operator=(random&& other)
{ 
	m_implementation = std::move(other.m_implementation);
	return *this;
}

single random::next(const interval<single>& interval)
{ return m_implementation->next(interval); }

double random::next(const interval<double>& interval)
{ return m_implementation->next(interval); }

quadruple random::next(const interval<quadruple>& interval)
{ return m_implementation->next(interval); }

int random::next(const interval<int>& interval)
{ return m_implementation->next(interval); }
    
} // namespace id
