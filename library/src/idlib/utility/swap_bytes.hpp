#pragma once

#include "idlib/utility.hpp"
#include <cstdint>

#include "idlib/utility/header.in"

/// @brief Swap the Bytes of an @a int8_t value.
/// @param x the @a int8_t value
/// @return the @a int8_t value with its Bytes swapped
int8_t swap_bytes(int8_t x);

/// @brief Swap the Bytes of an @a uint8_t value.
/// @param x the @a uint8_t value
/// @return the @a uint8_t value with its Bytes swapped
uint8_t swap_bytes(uint8_t x);

/// @brief Swap the Bytes of an @a int16_t value.
/// @param x the @a int16_t value
/// @return the @a int16_t value with its Bytes swapped
int16_t swap_bytes(int16_t x);

/// @brief Swap the Bytes of an @a uint16_t value.
/// @param x the @a uint16_t value
/// @return the @a uint16_t value with its Bytes swapped
uint16_t swap_bytes(uint16_t x);

/// @brief Swap the Bytes of an @a int32_t value.
/// @param x the @a int32_t value
/// @return the @a int32_t value with its Bytes swapped
int32_t swap_bytes(int32_t x);

/// @brief Swap the Bytes of an @a uint32_t value.
/// @param x the @a uint32_t value
/// @return the @a uint32_t value with its Bytes swapped
uint32_t swap_bytes(uint32_t x);

/// @brief Swap the Bytes of an @a int64_t value.
/// @param x the @a int64_t value
/// @return the @a int64_t value with its Bytes swapped
int64_t swap_bytes(int64_t x);

/// @brief Swap the Bytes of an @a uint64_t value.
/// @param x the @a uint64_t value
/// @return the @a uint64_t value with its Bytes swapped
uint64_t swap_bytes(uint64_t x);

/// @brief Swap the Bytes of a @a single value.
/// @param x the @a single value
/// @return the @a single value with its Bytes swapped
float swap_bytes(single x);

/// @brief Swap the Bytes of a @a double value.
/// @param x the @a double value
/// @return the @a double value with its Bytes swapped
double swap_bytes(double x);

#include "idlib/utility/footer.in"
