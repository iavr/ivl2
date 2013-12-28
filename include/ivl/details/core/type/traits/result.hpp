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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_RESULT_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_RESULT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F, typename... A>
using fun_test = decltype(afun::tmp_call()(gen <F>(), gen <A>()...));

template <typename C, typename M, typename... A>
using method_test = decltype((gen <C>().*gen <M>())(gen <A>()...));

template <typename C, typename M>
using prop_test = decltype((gen <C>().*gen <M>()));

//-----------------------------------------------------------------------------

template <typename S> struct res_fun;

template <typename F, typename... A>
struct res_fun <F(A...)> : public ret_sfinae <fun_test, F, A...> { };

//-----------------------------------------------------------------------------

template <typename F, typename S, bool = is_method_ptr <F>()>
struct res_member : public nat { };

template <typename F, typename M, typename C, typename... A>
struct res_member <F, M(C, A...), true> :
	public ret_sfinae <method_test, ptr2ref <C>, M, A...> { };

template <typename F, typename M, typename C>
struct res_member <F, M(C), false> :
	public ret_sfinae <prop_test, ptr2ref <C>, M> { };

//-----------------------------------------------------------------------------

template <typename F, typename S, bool = is_member_ptr <F>()>
struct res_choose : public res_fun <S> { };

template <typename F, typename S>
struct res_choose <F, S, true> : public res_member <F, S> { };

//-----------------------------------------------------------------------------

template <typename F, typename S, bool = is_complete <F>()>
struct res_complete : public res_choose <F, S> { };

template <typename F, typename S>
struct res_complete <F, S, false> : public nat { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct result_t : public result_t <F(A...)> { };

template <typename F, typename... A>
struct result_t <F(A...)> :
	public details::res_complete <remove_ref <F>, F(A...)> { };

template <typename... S> using result = type_of <result_t <S...> >;

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct ret_t : public ret_t <F(A...)> { };

template <typename F, typename... A>
struct ret_t <F(A...)> : public id_t <details::fun_test <F, A...> > { };

template <typename F, typename... A> using ret = type_of <ret_t <F, A...> >;

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct can_call : public can_call <F(A...)> { };

template <typename F, typename... A>
struct can_call <F(A...)> : public sfinae <details::fun_test, F, A...> { };

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_RESULT_HPP
