#pragma once

#include "idlib/platform.hpp"
#include <string>
#include <stdexcept>

#if defined (ID_WINDOWS)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include <vector>

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE 1
#include "idlib/utility/suffix.hpp"
#include "idlib/utility/runtime_error.hpp"
#pragma pop_macro("IDLIB_PRIVATE")

#include "idlib/file_system/header.in"

namespace internal {

struct directory_stream_windows
{
	enum class state
	{
		open,
		closed,
		end,
		error,
	};

	directory_stream_windows()
		: m_state(state::closed),
		  m_handle(INVALID_HANDLE_VALUE),
		  m_data()
	{}
	
	~directory_stream_windows()
	{
		close();
	}
	
	bool has_value() const
	{ return state::open == m_state; }

	std::string get_value() const
	{ if (!has_value()) throw std::runtime_error("enumerator has no value"); 
      return m_data.cFileName; }
	
	void close()
	{
		if (state::error == m_state || state::error == m_state || state::open == m_state)
		{
			FindClose(m_handle);
			m_handle = INVALID_HANDLE_VALUE;
			m_state = state::closed;
		}
	}
	
	std::string make_search_string(const std::string& pathname)
	{
		// must not be empty
		// must not end with / or \
		// must not contain wildcards
		static const std::vector<char> forbidden = 
		{
			'?',
			'*',
		};
		if (pathname.empty() ||
			is_suffix(pathname, std::string("/")) ||
			is_suffix(pathname, std::string("\\")) ||
            pathname.cend() != std::find_first_of(pathname.cbegin(), pathname.cend(), forbidden.cbegin(), forbidden.cend()))
		{
			throw runtime_error(__FILE__, __LINE__, "invalid pathname");
		}
		return pathname + "/*";
	}
	
	void open(const std::string& pathname)
	{
		close();
		SetLastError(0);
		m_handle = FindFirstFileA(make_search_string(pathname).c_str(), &m_data);
		if (INVALID_HANDLE_VALUE == m_handle)
		{
			if (GetLastError() == ERROR_FILE_NOT_FOUND) m_state = state::end;
			else m_state = state::error;
			SetLastError(0);
		}
		m_state = state::open;
		// Skip '.' and '..'.
		if (state::open == m_state && is_dot_or_dot_dot())
		{
			next();
		}
	}

	void next()
	{
		if (state::error == m_state || state::end == m_state)
		{ return; }

		SetLastError(0);
		BOOL result = FindNextFileA(m_handle, &m_data);
		if (!result)
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) m_state = state::end;
			else m_state = state::error;
			SetLastError(0);
		}
		// Skip '.' and '..'.
		if (state::open == m_state && is_dot_or_dot_dot())
		{
			next();
		}
	}
	
	bool is_dot_or_dot_dot()
	{
		const char *name = m_data.cFileName;
		if (name[0] == '.')
		{
			if (name[1] == '\0' || (name[1] == '.' && name[2] == '\0'))
			{
				return true;
			}
		}
		return false;
	}
	
	state m_state;

	HANDLE m_handle;

	WIN32_FIND_DATAA m_data;
	
}; // struct directory_stream_windows

} // namespace internal

#include "idlib/file_system/footer.in"

#endif
