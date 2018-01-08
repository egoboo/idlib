#include "idlib/file_system/working_directory_windows.hpp"

#if defined(ID_WINDOWS)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

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

#include "idlib/file_system/header.in"

std::string get_working_directory_impl()
{
#if defined(UNICODE) || defined(_UNICODE)
	auto length = GetCurrentDirectory(0, NULL); // Alias for GetCurrentDirectoryW.
#else
	auto length = GetCurrentDirectory(0, NULL); // Alias for GetCurrentDirectorA.
#endif
	if (!length)
	{
		throw std::runtime_error("unable to obtain working directory");
	}
#if defined(UNICODE) || defined(_UNICODE)
	auto buffer = std::make_unique<wchar_t[]>(length + 1);
#else
	auto buffer = std::make_unique<char[]>(length + 1);
#endif
#if defined(UNICODE) || defined(_UNICODE)
	length = GetCurrentDirectory(length + 1, buffer.get()); // Alias for GetCurrentDirectoryW.
#else
	length = GetCurrentDirectory(length + 1, buffer.get()); // Alias for GetCurrentDirectoryA.
#endif
	if (!length)
	{
		throw std::runtime_error("unable to obtain working directory");
	}
#if defined(UNICODE) || defined(_UNICODE)
	return std::string(wstrtostr(std::wstring(buffer.get())));
#else
	return std::string(buffer.get());
#endif
}

#include "idlib/file_system/footer.in"

#endif
