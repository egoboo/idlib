#pragma once

#include "idlib/platform.hpp"

#if defined (ID_POSIX)

#include <errno.h>
#include <dirent.h>
#include <string>
#include <stdexcept>

#include "idlib/file_system/header.in"

namespace internal {

// Two implementations are equal if they have the same state.
// If the common state is "open" then they are equal if they point to the same entry.
struct directory_stream_posix
{
	enum class state
	{
		open,
		closed,
		end,
		error,
	};
	
	directory_stream_posix()
		: m_state(state::closed),
		  m_dir(nullptr),
		  m_dirent(nullptr)
	{}
		
	~directory_stream_posix()
	{
		close();
	}
	
	bool has_value() const
	{ return state::open == m_state; }
	
	std::string get_value() const
	{ if (!has_value()) throw std::runtime_error("enumerator has no value");
	  return m_dirent->d_name; }
	
	void close()
	{
		if (state::closed != m_state)
		{
			if (m_dir)
			{
				m_dirent = nullptr;
				closedir(m_dir);
				m_dir = nullptr;
			}
			m_state = state::closed;
		}
	}
	
	void open(const std::string& pathname)
	{
		close();
		errno = 0;
		m_dir = opendir(pathname.c_str());
		if (nullptr == m_dir)
		{
			m_state = state::error;
			errno = 0;
		}
		m_dirent = readdir(m_dir);
		if (nullptr == m_dirent)
		{
			if (errno != 0)
			{
				m_state = state::error;
				errno = 0;
			}
			else
			{
				m_state = state::end;
			}
		}
		m_state = state::open;

		// Skip '.' and '..'.
		if (state::open == m_state)
		{
			if (is_dot_or_dot_dot())
			{
				next();
			}
		}
	}
	
	void next()
	{
		if (state::error == m_state || state::end == m_state)
		{ return; }

		errno = 0;
		m_dirent = readdir(m_dir);
		if (nullptr == m_dirent)
		{
			if (errno != 0)
			{
				m_state = state::error;
				errno = 0;
			}
			else
			{
				m_state = state::end;
			}
		}

		// Skip '.' and '..'.
		if (state::open == m_state && is_dot_or_dot_dot())
		{
     		next();
		}
	}
	
	bool is_dot_or_dot_dot()
	{
		const char *name = m_dirent->d_name;
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

	DIR *m_dir;

	struct dirent *m_dirent;	

}; // struct directory_stream_posix

} // internal

#include "idlib/file_system/footer.in"

#endif
