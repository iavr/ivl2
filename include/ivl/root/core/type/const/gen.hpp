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

#ifndef IVL_CORE_TYPE_CONST_GEN_HPP
#define IVL_CORE_TYPE_CONST_GEN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

namespace details {

template <size_t N, typename T>
using gen_fun = fun_of <T, rep <N, T> >;

template <size_t N, typename S, gen_fun <N, fun_ret <S> > &F>
struct c_gen_;

template <size_t N, typename S, gen_fun <N, fun_ret <S> > &F>
using c_gen = type_of <c_gen_<N, S, F> >;

template <size_t N, typename T, typename... A, gen_fun <N, T> &F>
struct c_gen_<N, T(A...), F> : id_t <c_call <gen_fun <N, T>&(A...), F> > { };

}  // namespace details

using details::c_gen;

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
using c_e  = c_call <afun::exp(c_one)>;

template <typename T = double>
using c_pi = c_mul <c_call <afun::atan(c_one)>, c_int <4> >;

template <typename T = double>
using c_i = c_cons <std::complex <T>(c_zero, c_one)>;

template <typename T = double>
using c_j = c_i <T>;

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CONST_GEN_HPP
