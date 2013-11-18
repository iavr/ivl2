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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_MEMBER_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_MEMBER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template <typename R> struct sig_ret_t { using type = R; };
template <typename R> struct sig_arg_t;

template <typename R, typename... A>
struct sig_ret_t <R (A...)> { using type = R; };

template <typename R, typename... A>
struct sig_arg_t <R (A...)> : public pack <A...> { };

template <typename S> using sig_ret = type_of <sig_ret_t <S> >;
template <typename S> using sig_arg = type_of <sig_arg_t <S> >;

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename C, typename T>
struct member_parts
{
	using class_type = C;
	using sig_type = T;
	using ret_type = T;
};

template <typename C, typename R, typename... A>
struct member_parts <C, R (A...)>
{
	using class_type = C;
	using sig_type = R (A...);
	using ret_type = R;
	using arg_type = pack <A...>;
};

//-----------------------------------------------------------------------------

template <typename M>
struct member_ { };

template <typename T, typename C>
struct member_ <T C::*> : public member_parts <C, T> { };

//-----------------------------------------------------------------------------

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...)> :
	public member_parts <C, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const> :
	public member_parts <C const, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) volatile> :
	public member_parts <C volatile, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const volatile> :
	public member_parts <C const volatile, R (A...)> { };

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) &> :
	public member_parts <C&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const&> :
	public member_parts <C const&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) volatile&> :
	public member_parts <C volatile&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const volatile&> :
	public member_parts <C const volatile&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) &&> :
	public member_parts <C&&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const&&> :
	public member_parts <C const&&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) volatile&&> :
	public member_parts <C volatile&&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const volatile&&> :
	public member_parts <C const volatile&&, R (A...)> { };

#endif  // IVL_HAS_FEATURE(cxx_reference_qualified_functions)

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename M>
using member = details::member_<raw_type <M> >;

template <typename M>
using member_class = typename member <M>::class_type;

template <typename M>
using member_sig = typename member <M>::sig_type;

template <typename M>
using member_ret = typename member <M>::ret_type;

template <typename M>
using member_arg = typename member <M>::arg_type;

//-----------------------------------------------------------------------------

template <typename C, typename M>
using is_member_ptr_of = expr <
	is_member_ptr <M>() &&
	eq <raw_type <member_class <M> >, raw_type <C> >()
>;

//-----------------------------------------------------------------------------

template <typename C, typename R, typename... A>
struct member_ptr_t : public member_ptr_t <C, R (A...)> { };

template <typename C, typename T>
struct member_ptr_t <C, T> : public id_t <T raw_type <C>::*> { };

template <typename C, typename R, typename... A>
using member_ptr = type_of <member_ptr_t <C, R, A...> >;

//-----------------------------------------------------------------------------

template <typename C, typename R, typename ...A>
struct member_ptr_t <C, R (A...)>
	{ using type = R (C::*)(A...); };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const, R (A...)>
	{ using type = R (C::*)(A...) const; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C volatile, R (A...)>
	{ using type = R (C::*)(A...) volatile; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const volatile, R (A...)>
	{ using type = R (C::*)(A...) const volatile; };

//-----------------------------------------------------------------------------

template <typename C, typename R, typename ...A>
struct member_ptr_t <C&, R (A...)>
	{ using type = R (C::*)(A...) &; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const&, R (A...)>
	{ using type = R (C::*)(A...) const&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C volatile&, R (A...)>
	{ using type = R (C::*)(A...) volatile&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const volatile&, R (A...)>
	{ using type = R (C::*)(A...) const volatile&; };

//-----------------------------------------------------------------------------

template <typename C, typename R, typename ...A>
struct member_ptr_t <C&&, R (A...)>
	{ using type = R (C::*)(A...) &&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const&&, R (A...)>
	{ using type = R (C::*)(A...) const&&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C volatile&&, R (A...)>
	{ using type = R (C::*)(A...) volatile&&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const volatile&&, R (A...)>
	{ using type = R (C::*)(A...) const volatile&&; };

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_MEMBER_HPP
