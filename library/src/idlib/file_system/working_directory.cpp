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

/// @file idlib/file_system/working_directory.cpp
/// @brief Determine the working directory.
/// @author Michael Heilmann

#include "idlib/file_system/working_directory.hpp"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#else
#include <unistd.h>
#endif

#if defined(_WIN32)
std::string wstrtostr(const std::wstring &wstr)
{
	// Convert a Unicode string to an ASCII string
	std::string strTo;
	auto szTo = std::make_unique<char[]>(wstr.length() + 1);
	szTo[wstr.size()] = '\0';
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo.get(), (int)wstr.length(), NULL, NULL);
	strTo = szTo.get();
	return strTo;
}
#endif

#if defined(_WIN32)
std::wstring strtowstr(const std::string &str)
{
	// Convert an ASCII string to a Unicode String
	std::wstring wstrTo;
	auto wszTo = std::make_unique<wchar_t[]>(str.length() + 1);
	wszTo[str.size()] = L'\0';
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wszTo.get(), (int)str.length());
	wstrTo = wszTo.get();
	return wstrTo;
}
#endif

#include "idlib/file_system/header.in"

std::string get_working_directory()
{
#if defined(_WIN32)
    auto length = GetCurrentDirectoryW(0, NULL);
    if (!length)
    {
        throw std::runtime_error("unable to obtain working directory");
    }
    auto buffer = std::make_unique<wchar_t[]>(length + 1);
    length = GetCurrentDirectoryW(length + 1, buffer.get());
    if (!length)
    {
        throw std::runtime_error("unable to obtain working directory");
    }
#if defined(UNICODE) || defined(_UNICODE)
	return std::string(wstrtostr(std::wstring(buffer.get())));
#else
    return std::string(buffer.get());
#endif
#else
	std::unique_ptr<char, decltype(std::free) *> path{get_current_dir_name(), std::free };
	if (!path)
	{
		throw std::runtime_error("unable to obtain working directory");
	}
	return std::string(path.get());
#endif
}

#include "idlib/file_system/footer.in"
