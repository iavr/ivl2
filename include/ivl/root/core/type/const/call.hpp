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

#ifndef IVL_CORE_TYPE_CONST_CALL_HPP
#define IVL_CORE_TYPE_CONST_CALL_HPP

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

template <typename S> struct c_ret_;
template <typename S> using  c_ret = type_of <c_ret_<S> >;

template <typename F, typename... A>
struct c_ret_<F(A...)> :
	remove_rref_t <ret <const_value <F>(const_value <A>...)> >{ };

//-----------------------------------------------------------------------------

template <typename D, typename S, typename R = c_ret <S>, bool = is_void <R>()>
struct c_call_;

template <typename D, typename F, typename... A, typename R>
struct c_call_<D, F(A...), R, false> : const_base <R, D>
{
	INLINE constexpr
	operator R() const
		{ return afun::tmp_call()(c_val._<F>(), c_val._<A>()...); }
};

template <typename D, typename F, typename... A, typename R>
struct c_call_<D, F(A...), R, true> : const_base <void, D>
{
	INLINE void
	operator()() const { afun::tmp_call()(c_val._<F>(), c_val._<A>()...); }
};

//-----------------------------------------------------------------------------

template <typename S> struct tmp_arg_;
template <typename S> using  tmp_arg = type_of <tmp_arg_<S> >;

template <typename F, typename... A>
struct tmp_arg_<F(A...)> : id_t <F(tmp <A...>)> { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename S, fun_ret <S> &...R>
using c_call = constant <tag::call, S, non_type <fun_ret <S>&, R>...>;

template <typename F, typename... A>
struct constant <tag::call, F(A...)> :
	details::c_call_<c_call <F(A...)> , F(A...)> { };

template <typename C, typename... A, C &R>
struct constant <tag::call, C(A...), non_type <raw_type <C>&, R> > :
	c_call <c_lref <C, R>(A...)> { };

template <typename S>
using c_tmp_call = c_call <details::tmp_arg <S> >;

template<char const*(&F)(), typename S = char const*()>
using c_string = c_call <S&(), F>;

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CONST_CALL_HPP
