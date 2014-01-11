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

#ifndef IVL_DETAILS_CORE_TYPE_CONST_CALL_HPP
#define IVL_DETAILS_CORE_TYPE_CONST_CALL_HPP

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

template <typename T> using arg_c = _if <is_tmp <T>{}, c_type <T>, T>;

template <typename S> struct ret_ct;
template <typename S> using  ret_c = type_of <ret_ct <S> >;

template <typename F, typename... A>
struct ret_ct <F(A...)> : ret_t <value_type_of <F>(value_type_of <A>...)> { };

//-----------------------------------------------------------------------------

template <typename S, typename D, typename R = ret_c <S>, bool = is_void <R>()>
struct c_call_;

template <typename F, typename... A, typename D, typename R>
struct c_call_<F(A...), D, R, false> : constant <R, D>
{
	INLINE constexpr
	operator R() const { return afun::tmp_call()(F()(), A()()...); }
};

template <typename F, typename... A, typename D, typename R>
struct c_call_<F(A...), D, R, true> : constant <void, D>
{
	INLINE void
	operator()() const { afun::tmp_call()(F()(), A()()...); }
};

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct c_call : c_call <F(A...)> { };

template <typename F, typename... A>
struct c_call <F(A...)> : c_call_<F(arg_c <A>...), c_call <F(A...)> > { };

//-----------------------------------------------------------------------------

}  // namespace details

using details::c_call;

//-----------------------------------------------------------------------------

template <typename C, typename... A>
struct c_fun_call : c_fun_call <C(A...)> { };

template <typename C, typename... A>
struct c_fun_call <C(A...)> : c_call <c_cons <C>(A...)> { };

template <typename C, C &O, typename... A>
struct c_ref_call : c_ref_call <C(A...), O> { };

template <typename C, C &O, typename... A>
struct c_ref_call <C(A...), O> : c_call <c_ref <C, O>(A...)> { };

template <typename C, C const &O, typename... A>
struct c_cref_call : c_cref_call <C(A...), O> { };

template <typename C, C const &O, typename... A>
struct c_cref_call <C(A...), O> : c_call <c_cref <C, O>(A...)> { };

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_CONST_CALL_HPP
