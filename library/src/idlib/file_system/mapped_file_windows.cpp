#include "idlib/file_system/mapped_file_windows.hpp"

#if defined(ID_WINDOWS)
#include "idlib/file_system/header.in"

static const char dummy = 0;

void mapped_file_descriptor_impl::open_read(const std::string& pathname, create_mode create_mode) noexcept
{
    close();
    m_file_descriptor.open(pathname, id::file_system::access_mode::read, create_mode);
    if (!m_file_descriptor.is_open())
    {
        return;
    }
    m_reading = true;
    m_writing = false;
	m_size = m_file_descriptor.size();
    // If the size of the file is 0, then creating a mapping would fail.
    // We create a dummy mapping.
    if (m_size == 0)
    {
        m_file_mapping_handle = (void *)&dummy;
        m_data = (void *)&dummy;
    }
    else
    {
        m_file_mapping_handle = CreateFileMapping(*((HANDLE *)m_file_descriptor.handle()), 0, PAGE_READONLY, 0, 0, 0);
        if (NULL == m_file_mapping_handle)
        {
            m_reading = false;
            m_writing = false;
            m_file_descriptor.close();
            return;
        }
        m_data = MapViewOfFile(m_file_mapping_handle, FILE_MAP_READ, 0, 0, 0);
        if (NULL == m_data)
        {
            m_reading = false;
            m_writing = false;
            CloseHandle(m_file_mapping_handle);
            m_file_mapping_handle = NULL;
            m_file_descriptor.close();
        }
    }
}

void mapped_file_descriptor_impl::open_write(const std::string& pathname, create_mode create_mode, size_t size) noexcept
{
    close();
    m_file_descriptor.open(pathname, id::file_system::access_mode::read_write, create_mode);
    if (!m_file_descriptor.is_open())
    { 
		return;
	}
    m_reading = false;
    m_writing = true;
	m_size = size;
	// If the size is zero and the size of the file is non-zero, then the user basically said "truncate".
	if (m_size >0)
	{
		m_file_mapping_handle = CreateFileMapping(*((HANDLE *)m_file_descriptor.handle()), NULL, PAGE_READWRITE, 0, size, 0);
		if (NULL == m_file_mapping_handle)
		{
            m_reading = false;
            m_writing = false;
			m_file_descriptor.close();
			return;
		}
		m_data = MapViewOfFile(m_file_mapping_handle, FILE_MAP_WRITE, 0, 0, 0);
		if (NULL == m_data)
		{
            m_reading = false;
            m_writing = false;
			CloseHandle(m_file_mapping_handle);
			m_file_mapping_handle = NULL;
			m_file_descriptor.close();
		}
	}
}

bool mapped_file_descriptor_impl::is_open() const noexcept
{
    return NULL != m_data;
}

bool mapped_file_descriptor_impl::is_opened_for_reading() const noexcept
{
    return m_reading;
}

bool mapped_file_descriptor_impl::is_opened_for_writing() const noexcept
{
    return m_writing;
}

void mapped_file_descriptor_impl::close() noexcept
{
    if (NULL != m_data)
    {
        UnmapViewOfFile(m_data);
        m_data = NULL;
    }
    if (NULL != m_file_mapping_handle)
    {
        CloseHandle(m_file_mapping_handle);
        m_file_mapping_handle = NULL;
    }
	if (m_writing)
	{
        // When writing, adjust the size of the file.
		SetFilePointer(*((HANDLE *)m_file_descriptor.handle()), m_size, 0, FILE_BEGIN);
        SetEndOfFile(m_file_descriptor.handle());
	}
    m_file_descriptor.close();
    m_writing = false;
}

char *mapped_file_descriptor_impl::data()
{
    return (char *)m_data;
}

size_t mapped_file_descriptor_impl::size() const
{
    return m_size;
}

mapped_file_descriptor_impl::mapped_file_descriptor_impl() noexcept :
    m_file_descriptor(), m_file_mapping_handle(NULL), m_data(NULL)
{}

mapped_file_descriptor_impl::~mapped_file_descriptor_impl() noexcept
{
    close();
}

#include "idlib/file_system/footer.in"
#endif
