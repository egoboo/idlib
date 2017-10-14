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

#define IDLIB_PRIVATE 1
#include "idlib/color/a.hpp"
#include "idlib/color/l.hpp"
#include "idlib/color/la.hpp"
#include "idlib/color/rgb.hpp"
#include "idlib/color/rgba.hpp"
#include "idlib/math/interpolate.hpp"
#include "idlib/math/floating_point.hpp"
#undef IDLIB_PRIVATE

template struct id::color<id::Ab>;
template struct id::color<id::Af>;

template struct id::color<id::Lb>;
template struct id::color<id::Lf>;

template struct id::color<id::LAb>;
template struct id::color<id::LAf>;

template struct id::color<id::RGBb>;
template struct id::color<id::RGBf>;

template struct id::color<id::RGBAb>;
template struct id::color<id::RGBAf>;

template struct id::lineary_interpolate_functor<id::color<id::Af>, single>;
template struct id::lineary_interpolate_functor<id::color<id::Lf>, single>;
template struct id::lineary_interpolate_functor<id::color<id::LAf>, single>;
template struct id::lineary_interpolate_functor<id::color<id::RGBf>, single>;
template struct id::lineary_interpolate_functor<id::color<id::RGBAf>, single>;

template struct id::invert_functor<id::color<id::Af>>;
template struct id::invert_functor<id::color<id::Ab>>;
template struct id::invert_functor<id::color<id::Lf>>;
template struct id::invert_functor<id::color<id::Lb>>;
template struct id::invert_functor<id::color<id::LAf>>;
template struct id::invert_functor<id::color<id::LAb>>;
template struct id::invert_functor<id::color<id::RGBf>>;
template struct id::invert_functor<id::color<id::RGBb>>;
template struct id::invert_functor<id::color<id::RGBAf>>;
template struct id::invert_functor<id::color<id::RGBAb>>;

template struct id::brighten_functor<id::color<id::Lf>>;
template struct id::brighten_functor<id::color<id::Lb>>;
template struct id::brighten_functor<id::color<id::LAf>>;
template struct id::brighten_functor<id::color<id::LAb>>;
template struct id::brighten_functor<id::color<id::RGBf>>;
template struct id::brighten_functor<id::color<id::RGBb>>;
template struct id::brighten_functor<id::color<id::RGBAf>>;
template struct id::brighten_functor<id::color<id::RGBAb>>;

template struct id::darken_functor<id::color<id::Lf>>;
template struct id::darken_functor<id::color<id::Lb>>;
template struct id::darken_functor<id::color<id::LAf>>;
template struct id::darken_functor<id::color<id::LAb>>;
template struct id::darken_functor<id::color<id::RGBf>>;
template struct id::darken_functor<id::color<id::RGBb>>;
template struct id::darken_functor<id::color<id::RGBAf>>;
template struct id::darken_functor<id::color<id::RGBAb>>;
