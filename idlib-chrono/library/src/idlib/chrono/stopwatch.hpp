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

/// @file idlib/chrono/stopwatch.hpp
/// @brief A stopwatch.
/// @author Michael Heilmann
#pragma once

#include "idlib/platform.hpp"
#include <memory>
#include <type_traits>

namespace idlib {

/// @brief Implementation of PIMPL.
struct stopwatch_impl;

/// @brief A stopwatch.
/// @remark Default constructible, not copyable, movable.
struct stopwatch {
private:
    /// @brief Pointer of PIMPL.
    std::unique_ptr<stopwatch_impl> m_impl;
    static constexpr bool is_impl_noexcept_move_constructible_v = std::is_nothrow_move_constructible<std::unique_ptr<stopwatch_impl>>::value;
    static constexpr bool is_impl_noexcept_move_assignable_v = std::is_nothrow_move_assignable<std::unique_ptr<stopwatch_impl>>::value;
public:
    /// @brief Construct this stopwatch.
    /// @post
    /// - <tt>this.running = false</tt>
    /// - <tt>this.begin = now</tt>
    /// - <tt>this.end = now</tt>
    stopwatch();

    stopwatch(const stopwatch&) = delete;
    stopwatch(stopwatch&& other) noexcept(stopwatch::is_impl_noexcept_move_constructible_v);

    ~stopwatch();

    stopwatch& operator=(const stopwatch&) = delete;
    stopwatch& operator=(stopwatch&&) noexcept(stopwatch::is_impl_noexcept_move_assignable_v);
    
    /// @brief Get if this stopwatch is running.
    /// @return @a true if this stopwatch is running, @a false otherwise
    /// @post <tt>result = this.running</tt>
    bool is_running() const;

    /// @brief Get the elapsed time duration.
    /// @return the elapsed time duration
    /// @post
    /// - If the stopwatch is running, the time between now and the start time is returned i.e.
    ///   <tt>result = now - this.begin</tt>
    ///   if <tt>this.running = true</tt>
    /// - If the stopwatch is not running, the time between the end time and the start time is returned i.e.
    ///   <tt>result = this.end - this.begin</tt>
    ///   if<tt>this.running = false</tt>
    double elapsed();

    /// @brief Start this stopwatch.
    /// @remark No effect is this stopwatch is started.
    /// @post
    /// - If <tt>this.running = false</tt> then
    ///   - <tt>this.running = true</tt>
    ///   - <tt>this.end = now</tt>
    /// - otherwise
    ///   - do nothing
    void start();

    /// @brief Stop this stopwatch.
    /// @remark No effect if this stopwatch is stopped.
    /// @post
    /// - If <tt>this.running = true</tt> then
    ///   - <tt>this.running = false</tt>
    ///   - <tt>this.end = now</tt>
    /// - otherwise
    ///   - do nothing
    void stop();

    /// @brief Reset this stopwatch.
    /// @post
    /// <tt>this.begin = this.end = now</tt>
    void reset();

}; // struct stopwatch

} // idlib
