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

namespace details {

//-----------------------------------------------------------------------------

template <typename C, typename R>
struct member_base
{
	using class_type = C;
	using ret_type = R;
};

template <typename C, typename R, typename... A>
struct member_base <C, R (A...)>
{
	using class_type = C;
	using ret_type = R;
	using arg_type = pack <A...>;
};

//-----------------------------------------------------------------------------

template <typename M>
struct member_ { };

template <typename R, typename C>
struct member_ <R C::*> : public member_base <C, R> { };

//-----------------------------------------------------------------------------

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...)> :
	public member_base <C, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const> :
	public member_base <C const, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) volatile> :
	public member_base <C volatile, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const volatile> :
	public member_base <C const volatile, R (A...)> { };

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) &> :
	public member_base <C&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const&> :
	public member_base <C const&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) volatile&> :
	public member_base <C volatile&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const volatile&> :
	public member_base <C const volatile&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) &&> :
	public member_base <C&&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const&&> :
	public member_base <C const&&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) volatile&&> :
	public member_base <C  volatile&&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const volatile&&> :
	public member_base <C const volatile&&, R (A...)> { };

#endif  // IVL_HAS_FEATURE(cxx_reference_qualified_functions)

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename M>
using member = details::member_<raw_type <M> >;

template <typename M>
using member_class = typename member <M>::class_type;

template <typename M>
using member_ret = typename member <M>::ret_type;

template <typename M>
using member_arg = typename member <M>::arg_type;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_MEMBER_HPP
