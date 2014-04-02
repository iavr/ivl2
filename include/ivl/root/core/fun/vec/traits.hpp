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

#ifndef IVL_CORE_FUN_VEC_TRAITS_HPP
#define IVL_CORE_FUN_VEC_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template <typename F, typename... T> struct tup_vec_ret_t;
template <typename F, typename... T>
using tup_vec_ret = type_of <tup_vec_ret_t <F, T...> >;

namespace details {

template <typename S>       struct tup_vec_ret_pt;
template <typename S, bool> struct tup_vec_ret_st;

template <typename F, typename... T>
struct tup_vec_ret_pt <F(pack <T...>)> : pack <tup_vec_ret <F(T)>...> { };

template <typename F, typename... T>
struct tup_vec_ret_st <F(T...), true> : tup_vec_ret_pt <F(tup_args <T...>)> { };

template <typename F, typename... T>
struct tup_vec_ret_st <F(T...), false> : ret_t <F(T...)> { };

}  // namespace details

template <typename F, typename... T>
struct tup_vec_ret_t : tup_vec_ret_t <F(T...)> { };

template <typename F, typename... T>
struct tup_vec_ret_t <F(T...)> :
	details::tup_vec_ret_st <F(T...), any_tuple <T...>{}> { };

template <typename F, typename... T>
struct tup_vec_ret_t <F(pack <T...>)> : tup_vec_ret_t <F(T...)> { };

//-----------------------------------------------------------------------------

template <typename F, typename... T> struct seq_vec_ret_t;
template <typename F, typename... T>
using seq_vec_ret = type_of <seq_vec_ret_t <F, T...> >;

namespace details {

template <typename S>       struct seq_vec_ret_pt;
template <typename S, bool> struct seq_vec_ret_st;

template <typename F, typename... T>
struct seq_vec_ret_pt <F(pack <T...>)> : seq_vec_ret_t <F(T...)> { };

template <typename F, typename... T>
struct seq_vec_ret_st <F(T...), true> : seq_vec_ret_pt <F(seq_args <T...>)> { };

template <typename F, typename... T>
struct seq_vec_ret_st <F(T...), false> : ret_t <F(T...)> { };

}  // namespace details

template <typename F, typename... T>
struct seq_vec_ret_t : seq_vec_ret_t <F(T...)> { };

template <typename F, typename... T>
struct seq_vec_ret_t <F(T...)> :
	details::seq_vec_ret_st <F(T...), any_seq <T...>{}> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct tup_vec_void_ : is_void <T> { };

template <typename... T>
struct tup_vec_void_<pack <T...> > : any <tup_vec_void_, T...> { };

}  // namespace details

template <typename F, typename... T>
struct tup_vec_void : tup_vec_void <F(T...)> { };

template <typename F, typename... T>
struct tup_vec_void <F(T...)> :
	details::tup_vec_void_<tup_vec_ret <F(T...)> > { };

//-----------------------------------------------------------------------------

template <typename F, typename... T>
struct seq_vec_void : seq_vec_void <F(T...)> { };

template <typename F, typename... T>
struct seq_vec_void <F(T...)> : is_void <seq_vec_ret <F(T...)> > { };

//-----------------------------------------------------------------------------

namespace details {

template <template <typename...> class F>
struct vec_all_
{
	template <typename P, bool = any_tuple_p <P>(), bool = any_seq_p <P>()>
	struct map_;

	template <typename P> using map = map_<P>;

	template <typename... A>
	struct map_<pack <A...>, false, false> : F <A...> { };

	template <typename... A>
	struct map_<pack <A...>, true, false> : all_p <map, tup_args <A...> > { };

	template <typename... A, bool T>
	struct map_<pack <A...>, T, true> : map_<seq_args <A...> > { };
};

}  // namespace details

// TODO: template alias causes clang segmentation fault
template <template <typename...> class F, typename... A>
struct vec_all : details::vec_all_<F>::template map <pack <A...> > { };

//-----------------------------------------------------------------------------

namespace details {

template <typename F>
struct call_test { template <typename... A> using map = can_call <F(A...)>; };

}  // namespace details

// extending definition @type/traits/result
template <typename F, typename B, typename... A>
struct can_call <afun::details::vec_apply <F, B>(A...)> :
	vec_all <details::call_test <F>::template map, A...> { };

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_VEC_TRAITS_HPP
