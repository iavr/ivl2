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

#ifndef IVL_CORE_TYPE_CONST_OP_HPP
#define IVL_CORE_TYPE_CONST_OP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F, typename... A>
using c_op = c_fun_call <F, A...>;

namespace op = afun::op;

//-----------------------------------------------------------------------------

template <typename A> using c_plus  = c_op <op::plus(A)>;
template <typename A> using c_minus = c_op <op::minus(A)>;

template <typename A, typename B> using c_add = c_op <op::add(A, B)>;
template <typename A, typename B> using c_sub = c_op <op::sub(A, B)>;
template <typename A, typename B> using c_mul = c_op <op::mul(A, B)>;
template <typename A, typename B> using c_div = c_op <op::div(A, B)>;
template <typename A, typename B> using c_mod = c_op <op::mod(A, B)>;

template <typename A, typename B> using c_eq  = c_op <op::eq (A, B)>;
template <typename A, typename B> using c_neq = c_op <op::neq(A, B)>;
template <typename A, typename B> using c_gt  = c_op <op::gt (A, B)>;
template <typename A, typename B> using c_lt  = c_op <op::lt (A, B)>;
template <typename A, typename B> using c_ge  = c_op <op::ge (A, B)>;
template <typename A, typename B> using c_le  = c_op <op::le (A, B)>;

template <typename A> using c_not = c_op <op::_not(A)>;

template <typename A, typename B> using c_and = c_op <op::_and(A, B)>;
template <typename A, typename B> using c_or  = c_op <op::_or (A, B)>;

template <typename A, typename B> using c_bit_not  = c_op <op::bit_not(A, B)>;
template <typename A, typename B> using c_bit_and  = c_op <op::bit_and(A, B)>;
template <typename A, typename B> using c_bit_or   = c_op <op::bit_or (A, B)>;
template <typename A, typename B> using c_bit_xor  = c_op <op::bit_xor(A, B)>;

template <typename A, typename B> using c_left  = c_op <op::left (A, B)>;
template <typename A, typename B> using c_right = c_op <op::right(A, B)>;

//-----------------------------------------------------------------------------

template <typename A> using c_deref = c_op <op::deref(A)>;
template <typename A> using c_addr  = c_op <op::addr(A)>;

template <typename A, typename B> using c_bracket = c_op <op::bracket(A, B)>;
template <typename A, typename B> using c_comma   = c_op <op::comma(A, B)>;

template <typename A, typename B, typename C>
using c_cond = c_op <op::cond(A, B, C)>;

//-----------------------------------------------------------------------------

template <typename T>
using c_sizeof = c_op <op::_sizeof, tmp <T> >;

template <typename T>
using c_alignof = c_op <op::_alignof, tmp <T> >;

//-----------------------------------------------------------------------------

template <typename T, typename A>
using c_conv = c_op <op::conv(tmp <T>, A)>;

template <typename T, typename A>
using c_static_cast = c_op <op::_static_cast(tmp <T>, A)>;

template <typename T, typename A>
using c_dynamic_cast = c_op <op::_dynamic_cast(tmp <T>, A)>;

template <typename T, typename A>
using c_const_cast = c_op <op::_const_cast(tmp <T>, A)>;

template <typename T, typename A>
using c_reinterpret_cast = c_op <op::_reinterpret_cast(tmp <T>, A)>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::c_plus;
using details::c_minus;

using details::c_add;
using details::c_sub;
using details::c_mul;
using details::c_div;
using details::c_mod;

using details::c_eq;
using details::c_neq;
using details::c_gt;
using details::c_lt;
using details::c_ge;
using details::c_le;

using details::c_not;
using details::c_and;
using details::c_or;

using details::c_bit_not;
using details::c_bit_and;
using details::c_bit_or;
using details::c_bit_xor;

using details::c_left;
using details::c_right;

using details::c_deref;
using details::c_addr;
using details::c_bracket;
using details::c_comma;
using details::c_cond;

using details::c_sizeof;
using details::c_alignof;

using details::c_conv;
using details::c_static_cast;
using details::c_dynamic_cast;
using details::c_const_cast;
using details::c_reinterpret_cast;

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CONST_OP_HPP
