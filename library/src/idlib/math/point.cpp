// Copyright Michael Heilmann 2016, 2017, 2018.
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
#include "idlib/math/point.hpp"
#include "idlib/math/floating_point.hpp"
#undef IDLIB_PRIVATE

template struct id::point<id::vector<single, 1>>;
template struct id::point<id::vector<single, 2>>;
template struct id::point<id::vector<single, 3>>;
template struct id::point<id::vector<single, 4>>;

template struct id::point<id::vector<double, 1>>;
template struct id::point<id::vector<double, 2>>;
template struct id::point<id::vector<double, 3>>;
template struct id::point<id::vector<double, 4>>;

template struct id::point<id::vector<quadruple, 1>>;
template struct id::point<id::vector<quadruple, 2>>;
template struct id::point<id::vector<quadruple, 3>>;
template struct id::point<id::vector<quadruple, 4>>;
