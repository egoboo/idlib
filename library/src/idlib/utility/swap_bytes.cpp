#include "idlib/utility/swap_bytes.hpp"

#if defined(__GNUC__)
#include <byteswap.h> 
#endif

#if defined (_MSC_VER)
#include <stdlib.h>
#endif

#include <algorithm>

#include "idlib/utility/header.in"
	
template <typename T>
union bytes
{
	char m_bytes[sizeof(T)];
	T m_value;

    constexpr const T& value() const
    { return m_value; }

    void value(const T& value)
    { m_value = value; }

	constexpr char *begin()
	{ return m_bytes + 0; }

	constexpr char *end()
	{ return m_bytes + size(); }

	constexpr size_t size() const
	{ return sizeof(T); }
};

int8_t swap_bytes(int8_t x)
{
	return x;
}

uint8_t swap_bytes(uint8_t x)
{
	return x;
}

int16_t swap_bytes(int16_t x)
{
#if defined(__GNUC__)
	return bswap_16(x);
#elif defined(_MSC_VER)
	return static_cast<int16_t>(swap_bytes(static_cast<uint16_t>(x)));
#else
	return static_cast<int16_t>(swap_bytes(static_cast<uint16_t>(x)));
#endif
}

uint16_t swap_bytes(uint16_t x)
{
#if defined(__GNUC__)
	return __builtin_bswap16(x);
#elif defined(_MSC_VER)
	return _byteswap_ushort(x);
#else
	bytes<uint16_t> b;
	b.value = x;
	std::reverse(b.begin(), b.end());
	return b.value;		
#endif
}

int32_t swap_bytes(int32_t x)
{
#if defined(__GNUC__)
	return bswap_32(x);
#elif defined(_MSC_VER)
	return static_cast<int32_t>(swap_bytes(static_cast<uint32_t>(x)));
#else
	return static_cast<int32_t>(swap_bytes(static_cast<uint32_t>(x)));
#endif		
}

uint32_t swap_bytes(uint32_t x)
{
#if defined(__GNUC__)
	return __builtin_bswap32(x);
#elif defined(_MSC_VER)
	return _byteswap_ulong(x);
#else
	bytes<uint32_t> b;
	b.value = x;
	std::reverse(b.begin(), b.end());
	return b.value;	
#endif	
}

int64_t swap_bytes(int64_t x)
{
#if defined(__GNUC__)
	return bswap_64(x);
#elif defined(_MSC_VER)
	return static_cast<int64_t>(swap_bytes(static_cast<uint64_t>(x)));
#else
	return static_cast<int64_t>(swap_bytes(static_cast<uint64_t>(x)));
#endif	
}

uint64_t swap_bytes(uint64_t x)
{
#if defined(__GNUC__)
	return __builtin_bswap64(x);
#elif defined(_MSC_VER)
	return _byteswap_uint64(x);
#else
	bytes<uint64_t> b;
	b.value = x;
	std::reverse(b.begin(), b.end());
	return b.value;
#endif
}

single swap_bytes(single x)
{
	bytes<single> b;
	b.value(x);
	std::reverse(b.begin(), b.end());
	return b.value();	
}

double swap_bytes(double x)
{
	bytes<double> b;
	b.value(x);
	std::reverse(b.begin(), b.end());
	return b.value();		
}

#include "idlib/utility/footer.in"
