#include "idlib/file_system/directory_iterator.hpp"

#if defined (ID_WINDOWS)
	#include "idlib/file_system/directory_stream_windows.hpp"
#elif defined (ID_POSIX)
	#include "idlib/file_system/directory_stream_posix.hpp"
#endif

#include "idlib/file_system/header.in"

namespace internal {	

#if defined (ID_WINDOWS)
using impl = directory_stream_windows;
#elif defined (ID_POSIX)
using impl = directory_stream_posix;
#endif

directory_stream::directory_stream()
	: m_pimpl(new impl())
{}

directory_stream::~directory_stream()
{ 
    if (m_pimpl)
    { 
        delete static_cast<impl *>(m_pimpl); 
        m_pimpl = nullptr;
    } 
}

void directory_stream::open(const std::string& pathname)
{ static_cast<impl *>(m_pimpl)->open(pathname); }

bool directory_stream::has_value() const
{ return static_cast<const impl *>(m_pimpl)->has_value(); }
	
std::string directory_stream::get_value() const
{ return static_cast<const impl *>(m_pimpl)->get_value(); }

void directory_stream::next()
{ static_cast<impl *>(m_pimpl)->next(); }
	
} // namespace internal

#include "idlib/file_system/footer.in"
