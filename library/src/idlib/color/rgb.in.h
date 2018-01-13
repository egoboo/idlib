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

    /// @brief Get the value of the red component.
    /// @return the value of the red component
    const component_r& get_red() const
    { return r; }
#if defined(ID_COLOR_SHORT_GETTERS) && 1 == ID_COLOR_SHORT_GETTERS
    const component_r& get_r() const noexcept
    { return r; }
#endif
    /// @}

    /// @{
    /// @brief Get the value of the green component.
    /// @return the value of the green component
    const component_g& get_green() const noexcept
    { return g; }
#if defined(ID_COLOR_SHORT_GETTERS) && 1 == ID_COLOR_SHORT_GETTERS
    const component_g& get_g() const
    { return g; }
#endif
    /// @}

    /// @{
    /// @brief Get the value of the blue component.
    /// @return the value of the blue component
    const component_b& get_blue() const noexcept
    { return b; }
#if defined(ID_COLOR_SHORT_GETTERS) && 1 == ID_COLOR_SHORT_GETTERS
    const component_b& get_b() const noexcept
    { return b; }
#endif
    /// @}