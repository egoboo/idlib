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

#include "idlib/language/decoder-natural.hpp"

#pragma push_macro("IDLIB_PRIVATE")
#if !defined(IDLIB_PRIVATE)
#define IDLIB_PRIVATE 1
#endif

#include "idlib/language/classify.hpp"
#include "idlib/utility/invalid_argument_error.hpp"
#include "idlib/utility/out_of_bounds_error.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace id { namespace c {

bool decoder<unsigned long, void>::operator()(const std::string& s, unsigned long& v) const
{
	try
	{
		try
		{
			if (s.empty() || isspace(s[0]))
			{
				throw invalid_argument_error(__FILE__, __LINE__, "not a valid natural literal");
			}
			size_t pos;
			unsigned long x;
			try
			{
				x = stoul(s, &pos);
			}
			catch (const std::invalid_argument&)
			{
				throw invalid_argument_error(__FILE__, __LINE__, "conversion failed");
			}
			catch (const std::out_of_range&)
			{
				throw out_of_bounds_error(__FILE__, __LINE__, "conversion failed");
			}
			if (pos != s.length())
			{
				throw invalid_argument_error(__FILE__, __LINE__, "not a valid natural literal");
			}
			v = x;
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

bool decoder<unsigned long long, void>::operator()(const std::string& s, unsigned long long& v) const
{
	try
	{
		try
		{
			if (s.empty() || isspace(s[0]))
			{
				throw invalid_argument_error(__FILE__, __LINE__, "not a valid natural literal");
			}
			size_t pos;
			unsigned long long x;
			try
			{
				x = stoull(s, &pos);
			}
			catch (const std::invalid_argument&)
			{
				throw invalid_argument_error(__FILE__, __LINE__, "conversion failed");
			}
			catch (const std::out_of_range&)
			{
				throw out_of_bounds_error(__FILE__, __LINE__, "conversion failed");
			}
			if (pos != s.length())
			{
				throw invalid_argument_error(__FILE__, __LINE__, "not a valid natural literal");
			}
			v = x;
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

bool decoder<unsigned char, void>::operator()(const std::string& s, unsigned char& v) const
{
	try
	{
		unsigned long t;
		if (!decoder<unsigned long>()(s, t))
		{
			return false;
		}
		if (t > std::numeric_limits<unsigned char>::max())
		{
			throw out_of_bounds_error(__FILE__, __LINE__, std::string("the value of the natural literal is bigger than the greatest value representable by the `") + typeid(unsigned char).name() + "`");
		}
		v = t;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

//template <>
bool decoder<unsigned short, void>::operator()(const std::string& s, unsigned short& v) const
{
	try
	{
		unsigned long t;
		if (!decoder<unsigned long>()(s, t))
		{
			return false;
		}
		if (t > std::numeric_limits<unsigned short>::max())
		{
			throw out_of_bounds_error(__FILE__, __LINE__, std::string("the value of the natural literal is greater than the greatest value representable by the `") + typeid(unsigned short).name() + "`");
		}
		v = t;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

//template <>
bool decoder<unsigned int, void>::operator()(const std::string& s, unsigned int& v) const
{
	try
	{
		unsigned long t;
		if (!decoder<unsigned long>()(s, t))
		{
			return false;
		}
		if (t > std::numeric_limits<unsigned int>::max())
		{
			throw out_of_bounds_error(__FILE__, __LINE__, std::string("the value of the natural literal is greater than the greatest value representable by the type `") + typeid(unsigned int).name() + "`");
		}
		v = t;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

} } // namespace id::c
