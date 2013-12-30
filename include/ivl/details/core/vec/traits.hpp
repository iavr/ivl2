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

template <typename T> struct vec_arg_t : public tup_types <atom_of <T> > { };
template <typename T> using  vec_arg = type_of <vec_arg_t <T> >;

template <typename... T> struct vec_args_t;
template <typename... T> using  vec_args = type_of <vec_args_t <T...> >;

template <typename... T>
struct vec_args_t { using type = tran <vec_arg <T>...>; };

template <typename T> struct vec_args_t <T> : public tup_types_t <T> { };

//-----------------------------------------------------------------------------

template <typename F, typename... T> struct vec_ret_t;
template <typename F, typename... T>
using vec_ret = type_of <vec_ret_t <F, T...> >;

namespace details {

template <typename S>       struct vec_ret_p;
template <typename S, bool> struct vec_ret_s;

template <typename F, typename... T>
struct vec_ret_p <F(pack <T...>)> : public pack <vec_ret <F(T)>...> { };

template <typename F, typename... T>
struct vec_ret_s <F(T...), true> : public vec_ret_p <F(vec_args <T...>)> { };

template <typename F, typename... T>
struct vec_ret_s <F(T...), false> : public ret_t <F(T...)> { };

}  // namespace details

template <typename F, typename... T>
struct vec_ret_t : public vec_ret_t <F(T...)> { };

template <typename F, typename... T>
struct vec_ret_t <F(T...)> :
	public details::vec_ret_s <F(T...), any_tuple <T...>{}> { };

template <typename F, typename... T>
struct vec_ret_t <F(pack <T...>)> : public vec_ret_t <F(T...)> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct vec_void_ : public is_void <T> { };

template <typename... T>
struct vec_void_<pack <T...> > : public any_p <vec_void_, pack <T...> > { };

}  // namespace details

template <typename F, typename... T>
struct vec_void : public vec_void <F(T...)> { };

template <typename F, typename... T>
struct vec_void <F(T...)> : public expr <
	any_tuple <T...>() && details::vec_void_<vec_ret <F(T...)> >()
> { };

template <typename F, typename... T>
struct vec_non_void : public vec_non_void <F(T...)> { };

template <typename F, typename... T>
struct vec_non_void <F(T...)> : public expr <
	any_tuple <T...>() && !details::vec_void_<vec_ret <F(T...)> >()
> { };

//-----------------------------------------------------------------------------

namespace details {

template <template <typename...> class F>
struct vec_rec_
{
	template <typename P>       struct rec;
	template <typename P, bool> struct test;

	template <typename... A>
	struct test <pack <A...>, false> : public F <A...> { };

	template <typename... A>
	struct test <pack <A...>, true> : public rec <vec_args <A...> > { };

	template <typename P> using map = test <P, any_tuple_p <P>{}>;
	template <typename P> struct rec : public all_p <map, P> { };
};

}  // namespace details

// TODO: template alias causes clang segmentation fault
template <template <typename...> class F, typename... A>
struct vec_rec : public details::vec_rec_<F>::template map <pack <A...> > { };

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_TRAITS_HPP
