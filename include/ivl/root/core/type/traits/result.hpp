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

#ifndef IVL_CORE_TYPE_TRAITS_RESULT_HPP
#define IVL_CORE_TYPE_TRAITS_RESULT_HPP

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
using fun_test = decltype(tmp_ret(gen <F>(), gen <A>()...));

template <typename C, typename M, typename... A>
using method_test = decltype((gen <C>().*gen <M>())(gen <A>()...));

template <typename C, typename M>
using prop_test = decltype((gen <C>().*gen <M>()));

//-----------------------------------------------------------------------------

template <typename S> struct res_fun;

template <typename F, typename... A>
struct res_fun <F(A...)> : ret_sfinae <fun_test, F, A...> { };

//-----------------------------------------------------------------------------

template <typename F, typename S, bool = is_method_ptr <F>()>
struct res_member : nat { };

template <typename F, typename M, typename C, typename... A>
struct res_member <F, M(C, A...), true> :
	ret_sfinae <method_test, ptr2ref <C>, M, A...> { };

template <typename F, typename M, typename C>
struct res_member <F, M(C), false> :
	ret_sfinae <prop_test, ptr2ref <C>, M> { };

//-----------------------------------------------------------------------------

template <typename F, typename S, bool = is_member_ptr <F>()>
struct res_switch : res_fun <S> { };

template <typename F, typename S>
struct res_switch <F, S, true> : res_member <F, S> { };

//-----------------------------------------------------------------------------

template <typename F, typename S, bool = is_complete <F>()>
struct res_complete : res_switch <F, S> { };

template <typename F, typename S>
struct res_complete <F, S, false> : nat { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct result_t : result_t <F(A...)> { };

template <typename F, typename... A>
struct result_t <F(A...)> :
	details::res_complete <remove_ref <F>, F(A...)> { };

template <typename... S>
using result = type_of <result_t <S...> >;

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct ret_t : ret_t <F(A...)> { };

template <typename F, typename... A>
struct ret_t <F(A...)> : id_t <details::fun_test <F, A...> > { };

template <typename F, typename... A>
using ret = type_of <ret_t <F, A...> >;

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct res_t : res_t <F(A...)> { };

template <typename F, typename... A>
struct res_t <F(A...)> : ret_sfinae <details::fun_test, F, A...> { };

template <typename F, typename... A>
using res = type_of <res_t <F, A...> >;

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct bra_ret_t;

template <typename F, typename A>
struct bra_ret_t <F, A> : bra_ret_t <F(A)> { };

template <typename F, typename A>
struct bra_ret_t <F(A)> : id_t <decltype(gen <F>()[gen <A>()])> { };

template <typename F, typename... A>
using bra_ret = type_of <bra_ret_t <F, A...> >;

//-----------------------------------------------------------------------------

// extended elsewhere
template <typename F, typename... A>
struct can_call : can_call <F(A...)> { };

template <typename F, typename... A>
struct can_call <F(A...)> : sfinae <details::fun_test, F, A...> { };

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct call_first_t : call_first_t <F(A...)> { };

template <typename F, typename... Fn, typename... A>
struct call_first_t <pack <F, Fn...>(A...)> :
	_if <can_call <F(A...)>{}, id_t <F>, call_first_t <pack <Fn...>, A...> > { };

template <typename F, typename... A>
struct call_first_t <pack <F>(A...)> : id_t <F> { };

template <typename F, typename... A>
struct call_first_t <F(A...)> : id_t <F> { };

template <typename F, typename... A>
using call_first = type_of <call_first_t <F, A...> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_TRAITS_RESULT_HPP
