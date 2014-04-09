/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_TYPE_CONST_FUN_HPP
#define IVL_CORE_TYPE_CONST_FUN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

template <typename T, T (*F)()>
struct c_gen : c_sig <T()>::template call <F> { };

template <typename T, T (*F)(T), typename A1>
struct c_gen1 : c_sig <T(T)>::template call <F, A1> { };

template <typename T, T (*F)(T, T), typename A1, typename A2>
struct c_gen2 : c_sig <T(T, T)>::template call <F, A1, A2> { }	;

//-----------------------------------------------------------------------------

namespace details {

namespace lim = afun::lim;

template <typename T> using c_min = c_tmp_call <lim::min(T)>;
template <typename T> using c_max = c_tmp_call <lim::max(T)>;

template <typename T = double> using c_eps = c_tmp_call <lim::eps(T)>;
template <typename T = double> using c_inf = c_tmp_call <lim::inf(T)>;
template <typename T = double> using c_nan = c_tmp_call <lim::nan(T)>;

}  // namespace details

using details::c_min;
using details::c_max;
using details::c_eps;
using details::c_inf;
using details::c_nan;

//-----------------------------------------------------------------------------

template <typename T = double>
using c_e  = c_gen1 <T, std::exp, c_one>;

template <typename T = double>
using c_pi = c_mul <c_gen1 <T, std::atan, c_one>, c_int <4> >;

template <typename T = double>
using c_i  = c_cons <std::complex <T>(c_zero, c_one)>;

template <typename T = double>
using c_j  = c_i <T>;

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CONST_FUN_HPP
