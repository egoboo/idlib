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
