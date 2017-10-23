#include "idlib/language/decoder-integer.hpp"

namespace id { namespace c {
	
bool decoder<int, void>::operator()(const std::string& s, int& v) const
{
	try
	{
		try
		{
			if (s.empty() || isspace(s[0]))
			{
				throw id::invalid_argument_error(__FILE__, __LINE__, "not a valid integer literal");
			}
			size_t pos;
			int t;
			try
			{
				t = stoi(s, &pos);
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
				throw out_of_bounds_error(__FILE__, __LINE__, "not a valid integer literal");
			}
			v = t;
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

bool decoder<long, void>::operator()(const std::string& s, long& v) const
{
    try
	{
        try
		{
            if (s.empty() || isspace(s[0]))
			{
                throw id::invalid_argument_error(__FILE__, __LINE__, "not a valid integer literal");
            }
            size_t pos;
            long t;
            try
			{
                t = stol(s, &pos);
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
                throw out_of_bounds_error(__FILE__, __LINE__, "not a valid integer literal");
            }
            v = t;
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

bool decoder<long long, void>::operator()(const std::string& s, long long& v) const
{
    try
	{
        try
		{
            if (s.empty() || isspace(s[0]))
			{
                throw id::invalid_argument_error(__FILE__, __LINE__, "not a valid integer literal");
            }
            size_t pos;
            long long t;
            try
			{
                t = stoll(s, &pos);
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
                throw out_of_bounds_error(__FILE__, __LINE__, "not a valid integer literal");
            }
            v = t;
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

bool decoder<signed char, void>::operator()(const std::string& s, signed char& v) const
{
    try
	{
		int t;
		if (!decoder<int>()(s, t))
		{
			return false;
		}
		if (t < std::numeric_limits<signed char>::min())
		{
			throw out_of_bounds_error(__FILE__, __LINE__, std::string("the value of the integer literal is smaller than the least value representable by the type `") + typeid(signed char).name() + "`");
		}
		if (t > std::numeric_limits<signed char>::max())
		{
			throw out_of_bounds_error(__FILE__, __LINE__, std::string("the value of the integer literal is bigger than the greatest value representable by the type `") + typeid(signed char).name() + "`");
		}
		v = t;
	}
	catch (out_of_bounds_error&)
	{
		return false;
	}
    return true;
}

bool decoder<short, void>::operator()(const std::string& s, short& v) const
{
    try
	{
		int t;
		if (!decoder<int>()(s, t))
		{
			return false;
		}
		if (t < std::numeric_limits<short>::min())
		{
			throw out_of_bounds_error(__FILE__, __LINE__, std::string("the value of the integer literal is smaller than the least value representable by the type `") + typeid(short).name() + "`");
		}
		if (t > std::numeric_limits<short>::max())
		{
			throw out_of_bounds_error(__FILE__, __LINE__, std::string("the value of the integer literal is bigger than the greatest value representable by the type `") + typeid(short).name() + "`");
		}
		v = t;
	}
	catch (out_of_bounds_error&)
	{
		return false;
	}
    return true;
}

} } // namespace id::c
