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

#pragma once

#include "idlib/platform.hpp"
#include <string>
#include <memory>

#include "idlib/file_system/header.in"

namespace internal
{	

// pimpl wrapper.
struct directory_stream
{
	directory_stream(const directory_stream&) = delete;
	
	directory_stream& operator=(const directory_stream&) = delete;
	
	directory_stream();
	
	~directory_stream();

	void open(const std::string& pathname);

	bool has_value() const;
	
	std::string get_value() const;
	
	void next();

private:
	void *m_pimpl;

}; // struct directory_stream

} // namespace internal

/// @InputIterator
/// @warning The ++ operator is not equality preserving i.e. i == j does not imply i++ == j++.
struct directory_iterator
{
	using iterator_category = std::input_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = std::string;
	using reference = std::string&;
	using pointer = std::string*;
	
	directory_iterator()
		: m_directory_stream(std::make_shared<internal::directory_stream>()),
		  m_file_name()
	{}
	
	directory_iterator(const std::string& pathname)
		: m_directory_stream(std::make_shared<internal::directory_stream>()),
		  m_file_name()
	{
		m_directory_stream->open(pathname);
		if (m_directory_stream->has_value())
		{
			m_file_name = m_directory_stream->get_value();
		}
	}
	
	directory_iterator(const directory_iterator& other)
		: m_directory_stream(other.m_directory_stream),
		  m_file_name(other.m_file_name)
	{}
	
	directory_iterator& operator=(const directory_iterator& other)
	{ m_directory_stream = other.m_directory_stream; m_file_name = other.m_file_name; return *this; }
	
	~directory_iterator()
	{}

	bool operator==(const directory_iterator& other) const
	{ return (m_directory_stream == other.m_directory_stream)
	      || (!m_directory_stream->has_value() && !other.m_directory_stream->has_value()); 
	}
	
	bool operator!=(const directory_iterator& other) const
	{ return !(*this == other); }
	
	directory_iterator operator++(int) const
	{
		auto t = *this;
		++t;
		return t;
	}
	
	directory_iterator& operator++()
	{
		m_directory_stream->next();
		if (m_directory_stream->has_value()) m_file_name = m_directory_stream->get_value();
		return *this;		
	}
	
	const std::string& operator*() const
	{ return m_file_name; }
	
	const std::string* operator->() const
	{ return &m_file_name; }
	
private:
    std::shared_ptr<internal::directory_stream> m_directory_stream;
	std::string m_file_name;
	
}; // struct directory_iterator

#include "idlib/file_system/footer.in"

namespace std
{

template <>
struct iterator_traits<id::file_system::directory_iterator> 
{
	using iterator_category = id::file_system::directory_iterator::iterator_category;
	using difference_type = id::file_system::directory_iterator::difference_type;
	using value_type = id::file_system::directory_iterator::value_type;
	using reference = id::file_system::directory_iterator::reference;
	using pointer = id::file_system::directory_iterator::pointer;
}; // struct iterator_traits

} // namespace std
