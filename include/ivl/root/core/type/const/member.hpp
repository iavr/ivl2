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

#ifndef IVL_CORE_TYPE_CONST_MEMBER_HPP
#define IVL_CORE_TYPE_CONST_MEMBER_HPP

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

template <typename T> struct f_ret_ : id_t <T> { };
template <typename T> using  f_ret = type_of <f_ret_<T> >;

template <typename R, typename... A>
struct f_ret_<R(A...)> : id_t <R> { };

//-----------------------------------------------------------------------------

template <typename C, typename S>
using mem_ptr = member_ptr <f_ret <C>, S>;

template <typename C, typename S>
using mem_sig_ptr = mem_ptr <C, raw_type <fun_ret <S> > >;

//-----------------------------------------------------------------------------

template <typename C, typename T, mem_ptr <C, T> M>
using c_member = c_integral <mem_ptr <C, T>, M>;

//-----------------------------------------------------------------------------

template <typename C, typename T, mem_ptr <C, T> M, C &...R>
struct c_ref_member_;

template <typename C, typename T, mem_ptr <C, T> M, C &...R>
using c_ref_member = type_of <c_ref_member_<C, T, M, R...> >;

template <typename C, typename T, mem_ptr <C, T> M>
struct c_ref_member_<C, T, M> :
	id_t <c_call <op::ref_member(c_cons <C>, c_member <C, T, M>)> > { };

template <typename C, typename T, mem_ptr <C, T> M, C &R>
struct c_ref_member_<C, T, M, R> :
	id_t <c_call <op::ref_member(c_lref <C, R>, c_member <C, T, M>)> > { };

//-----------------------------------------------------------------------------

template <typename C, typename S, mem_sig_ptr <C, S> M, f_ret <C> &...R>
struct c_ref_call_;

template <typename C, typename S, mem_sig_ptr <C, S> M, f_ret <C> &...R>
using c_ref_call = type_of <c_ref_call_<C, S, M, R...> >;

template <typename C, typename F, typename... A, mem_ptr <C, F> M>
struct c_ref_call_<C, F&(A...), M> :
	id_t <c_call <op::ref_call(c_cons <C>, c_member <C, F, M>, A...)> > { };

template <typename C, typename F, typename... A, mem_ptr <C, F> M, C &R>
struct c_ref_call_<C, F&(A...), M, R> :
	id_t <c_call <op::ref_call(c_lref <C, R>, c_member <C, F, M>, A...)> > { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::c_member;
using details::c_ref_member;
using details::c_ref_call;

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CONST_MEMBER_HPP
