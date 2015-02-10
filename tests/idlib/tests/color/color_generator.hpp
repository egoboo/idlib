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

#pragma once

#include "idlib/idlib.hpp"

namespace id { namespace tests { namespace color {

template <typename S, typename E = void>
struct color_generator;

template <typename S>
struct color_generator<S, std::enable_if_t<id::is_any_of<S, id::RGBb, id::RGBf, id::RGBAb, id::RGBAf>::value>>
{
    using C = id::color<S>;
    std::vector<C> operator()() const
    {
        static const std::vector<C> colors =
        {
            C::black(),   // x x x
            C::blue(),    // x x b
            C::green(),   // x g x
            C::cyan(),    // x g b
            C::red(),     // r x x
            C::magenta(), // r x b
            C::yellow(),  // r g x
            C::white(),   // r g b
        };
        return colors;
    }
};

template <typename S>
struct color_generator<S, std::enable_if_t<id::is_any_of<S, id::Lb, id::Lf, id::LAb, id::LAf>::value>>
{
    using C = id::color<S>;
    std::vector<C> operator()() const
    {
        static const std::vector<C> colors =
        {
            C::black(),
            C::white(),
        };
        return colors;
    }
};

} } } // namespace id::tests::color
