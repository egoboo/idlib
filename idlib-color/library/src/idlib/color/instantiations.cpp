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
#undef IDLIB_PRIVATE

template struct idlib::color<idlib::Ab>;
template struct idlib::color<idlib::Af>;

template struct idlib::color<idlib::Lb>;
template struct idlib::color<idlib::Lf>;

template struct idlib::color<idlib::LAb>;
template struct idlib::color<idlib::LAf>;

template struct idlib::color<idlib::RGBb>;
template struct idlib::color<idlib::RGBf>;

template struct idlib::color<idlib::RGBAb>;
template struct idlib::color<idlib::RGBAf>;

template struct idlib::lineary_interpolate_functor<idlib::color<idlib::Af>, single>;
template struct idlib::lineary_interpolate_functor<idlib::color<idlib::Lf>, single>;
template struct idlib::lineary_interpolate_functor<idlib::color<idlib::LAf>, single>;
template struct idlib::lineary_interpolate_functor<idlib::color<idlib::RGBf>, single>;
template struct idlib::lineary_interpolate_functor<idlib::color<idlib::RGBAf>, single>;

template struct idlib::invert_functor<idlib::color<idlib::Af>>;
template struct idlib::invert_functor<idlib::color<idlib::Ab>>;
template struct idlib::invert_functor<idlib::color<idlib::Lf>>;
template struct idlib::invert_functor<idlib::color<idlib::Lb>>;
template struct idlib::invert_functor<idlib::color<idlib::LAf>>;
template struct idlib::invert_functor<idlib::color<idlib::LAb>>;
template struct idlib::invert_functor<idlib::color<idlib::RGBf>>;
template struct idlib::invert_functor<idlib::color<idlib::RGBb>>;
template struct idlib::invert_functor<idlib::color<idlib::RGBAf>>;
template struct idlib::invert_functor<idlib::color<idlib::RGBAb>>;

template struct idlib::brighten_functor<idlib::color<idlib::Lf>>;
template struct idlib::brighten_functor<idlib::color<idlib::Lb>>;
template struct idlib::brighten_functor<idlib::color<idlib::LAf>>;
template struct idlib::brighten_functor<idlib::color<idlib::LAb>>;
template struct idlib::brighten_functor<idlib::color<idlib::RGBf>>;
template struct idlib::brighten_functor<idlib::color<idlib::RGBb>>;
template struct idlib::brighten_functor<idlib::color<idlib::RGBAf>>;
template struct idlib::brighten_functor<idlib::color<idlib::RGBAb>>;

template struct idlib::darken_functor<idlib::color<idlib::Lf>>;
template struct idlib::darken_functor<idlib::color<idlib::Lb>>;
template struct idlib::darken_functor<idlib::color<idlib::LAf>>;
template struct idlib::darken_functor<idlib::color<idlib::LAb>>;
template struct idlib::darken_functor<idlib::color<idlib::RGBf>>;
template struct idlib::darken_functor<idlib::color<idlib::RGBb>>;
template struct idlib::darken_functor<idlib::color<idlib::RGBAf>>;
template struct idlib::darken_functor<idlib::color<idlib::RGBAb>>;
