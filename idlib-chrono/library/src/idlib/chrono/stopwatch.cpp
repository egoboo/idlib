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

/// @file idlib/chrono/stopwatch.cpp
/// @brief A stopwatch.
/// @author Michael Heilmann

#include "idlib/chrono/stopwatch.hpp"
#include <chrono>

namespace idlib {

struct stopwatch_impl
{
    bool m_running;

    std::chrono::high_resolution_clock::time_point m_begin;

    std::chrono::high_resolution_clock::time_point m_end;

    stopwatch_impl();

    stopwatch_impl(const stopwatch_impl&) = delete;
    stopwatch_impl(stopwatch_impl&&) = delete;
    stopwatch_impl& operator=(const stopwatch_impl&) = delete;
    stopwatch_impl& operator=(stopwatch_impl&&) = delete;

    bool is_running() const;

    double elapsed();

    void start();

    void stop();

    void reset();

}; // struct stopwatch_impl

stopwatch_impl::stopwatch_impl() :
    m_running(false),
    m_begin(std::chrono::high_resolution_clock::now()),
    m_end(std::chrono::high_resolution_clock::now())
{}

bool stopwatch_impl::is_running() const
{ return m_running; }

double stopwatch_impl::elapsed()
{
    if (m_running)
    {
        m_end = std::chrono::high_resolution_clock::now();
    }
    return std::chrono::duration_cast<std::chrono::duration<double>>(m_end - m_begin).count();
}

void stopwatch_impl::start()
{
    if (!m_running)
    {
        m_begin = std::chrono::high_resolution_clock::now();
        m_running = true;
    }
}

void stopwatch_impl::stop()
{
    if (m_running)
    {
        m_end = std::chrono::high_resolution_clock::now();
        m_running = false;
    }
}

void stopwatch_impl::reset()
{
    m_begin = std::chrono::high_resolution_clock::now();
    m_end = m_begin;
}

} // namespace idlib

namespace idlib {

stopwatch::stopwatch() :
    m_impl(std::make_unique<stopwatch_impl>())
{}

stopwatch::stopwatch(stopwatch&& other) noexcept(stopwatch::is_impl_noexcept_move_constructible_v) :
    m_impl(std::move(other.m_impl))
{}

stopwatch::~stopwatch()
{}

stopwatch& stopwatch::operator=(stopwatch&& other) noexcept(stopwatch::is_impl_noexcept_move_assignable_v)
{
    m_impl = std::move(other.m_impl);
    return *this;
}

bool stopwatch::is_running() const
{ return m_impl->is_running(); }

double stopwatch::elapsed()
{ return m_impl->elapsed(); }

void stopwatch::start()
{ m_impl->start(); }

void stopwatch::stop()
{ m_impl->stop(); }

void stopwatch::reset()
{ m_impl->reset(); }

} // namespace idlib
