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

#ifndef IVL_DETAILS_CORE_VEC_TRAITS_HPP
#define IVL_DETAILS_CORE_VEC_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template <typename T> struct tup_arg_t : public tup_types <atom_of <T> > { };
template <typename T> using  tup_arg = type_of <tup_arg_t <T> >;

template <typename... T> struct tup_args_t;
template <typename... T> using  tup_args = type_of <tup_args_t <T...> >;

template <typename... T>
struct tup_args_t { using type = tran <tup_arg <T>...>; };

template <typename T> struct tup_args_t <T> : public tup_types_t <T> { };

//-----------------------------------------------------------------------------

template <typename F, typename... T> struct tup_ret_t;
template <typename F, typename... T>
using tup_ret = type_of <tup_ret_t <F, T...> >;

namespace details {

template <typename S>       struct tup_ret_p;
template <typename S, bool> struct tup_ret_s;

template <typename F, typename... T>
struct tup_ret_p <F(pack <T...>)> : public pack <tup_ret <F(T)>...> { };

template <typename F, typename... T>
struct tup_ret_s <F(T...), true> : public tup_ret_p <F(tup_args <T...>)> { };

template <typename F, typename... T>
struct tup_ret_s <F(T...), false> : public ret_t <F(T...)> { };

}  // namespace details

template <typename F, typename... T>
struct tup_ret_t : public tup_ret_t <F(T...)> { };

template <typename F, typename... T>
struct tup_ret_t <F(T...)> :
	public details::tup_ret_s <F(T...), any_tuple <T...>{}> { };

template <typename F, typename... T>
struct tup_ret_t <F(pack <T...>)> : public tup_ret_t <F(T...)> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct tup_void_ : public is_void <T> { };

template <typename... T>
struct tup_void_<pack <T...> > : public any_p <tup_void_, pack <T...> > { };

}  // namespace details

template <typename F, typename... T>
struct tup_void : public tup_void <F(T...)> { };

template <typename F, typename... T>
struct tup_void <F(T...)> : public expr <
	any_tuple <T...>() && details::tup_void_<tup_ret <F(T...)> >()
> { };

template <typename F, typename... T>
struct tup_non_void : public tup_non_void <F(T...)> { };

template <typename F, typename... T>
struct tup_non_void <F(T...)> : public expr <
	any_tuple <T...>() && !details::tup_void_<tup_ret <F(T...)> >()
> { };

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_TRAITS_HPP
