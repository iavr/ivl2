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

#ifndef IVL_CORE_TYPE_PACK_REDUCE_HPP
#define IVL_CORE_TYPE_PACK_REDUCE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace packs {

//-----------------------------------------------------------------------------

namespace details {

template <typename P, size_t N = 0, bool = is_null <P>{}> struct first_;

template <template <typename...> class C, typename... B, size_t N>
struct first_<C <_true, B...>, N, false> : size <N> { };

template <template <typename...> class C, typename... B, size_t N>
struct first_<C <_false, B...>, N, false> : first_<C <B...>, N + 1> { };

}  // namespace details

template <typename P>    using first_p = details::first_<P>;
template <typename... B> using first   = first_p <pack <B...> >;
template <bool... B>     using first_b = first <expr <B>...>;

//-----------------------------------------------------------------------------

namespace details {

template <typename P, bool = is_null <P>{}>
struct _and_p_ : _if <car <P>{}, _and_p_<cdr <P> >, _false> { };

template <typename P, bool = is_null <P>{}>
struct _or_p_ : _if <car <P>{}, _true, _or_p_<cdr <P> > > { };

template <typename P> struct _and_p_<P, true> : _true  { };
template <typename P> struct _or_p_ <P, true> : _false { };

}  // namespace details

template <typename P> using _and_p = details::_and_p_<P>;
template <typename P> using _or_p  = details::_or_p_<P>;

template <typename... E> using _and = _and_p <pack <E...> >;
template <typename... E> using _or  = _or_p  <pack <E...> >;

//-----------------------------------------------------------------------------

namespace details {

template <template <typename...> class F, typename P, bool = is_null <P>{}>
struct all_p_ : _if <F <car <P> >{}, all_p_<F, cdr <P> >, _false> { };

template <template <typename...> class F, typename P, bool = is_null <P>{}>
struct any_p_ : _if <F <car <P> >{}, _true, any_p_<F, cdr <P> > > { };

template <template <typename...> class F, typename P>
struct all_p_ <F, P, true> : _true  { };

template <template <typename...> class F, typename P>
struct any_p_ <F, P, true> : _false { };

}  // namespace details

template <template <typename...> class F, typename P>
using all_p = details::all_p_<F, P>;

template <template <typename...> class F, typename P>
using any_p = details::any_p_<F, P>;

template <template <typename...> class F, typename... E>
using all = all_p <F, pack <E...> >;

template <template <typename...> class F, typename... E>
using any = any_p  <F, pack <E...> >;

//-----------------------------------------------------------------------------

template <typename T, typename P>
using contains_p = any_p <eq_to <T>::template map, P>;

template <typename T, typename... E>
using contains = contains_p <T, pack <E...> >;

//-----------------------------------------------------------------------------

template <typename P> using all_type_p = all_p <is_type, P>;
template <typename P> using any_type_p = any_p <is_type, P>;

template <typename... E> using all_type = all_type_p <pack <E...> >;
template <typename... E> using any_type = any_type_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <typename P> using all_pack_p = all_p <is_pack, P>;
template <typename P> using any_pack_p = any_p <is_pack, P>;

template <typename... E> using all_pack = all_pack_p <pack <E...> >;
template <typename... E> using any_pack = any_pack_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <typename P> using all_null_p = all_p <is_null, P>;
template <typename P> using any_null_p = any_p <is_null, P>;

template <typename... E> using all_null = all_null_p <pack <E...> >;
template <typename... E> using any_null = any_null_p <pack <E...> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename P, bool = is_null <P>{}>
struct all_eq_ : eq <P, rep <length <P>{}, car <P> > > { };

template <typename P>
struct all_eq_<P, true> : _true { };

}  // namespace details

template <typename P>    using all_eq_p = details::all_eq_<P>;
template <typename... E> using all_eq   = all_eq_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <template <typename...> class... C> struct all_cond;
template <template <typename...> class... C> struct any_cond;

template <> struct all_cond <> { template <typename... T> using map = _true; };
template <> struct any_cond <> { template <typename... T> using map = _false; };

template <template <typename...> class C, template <typename...> class... D>
struct all_cond <C, D...>
{
	template <typename... T> using map =
		_and <C <T...>, typename all_cond <D...>::template map <T...> >;
};

template <template <typename...> class C, template <typename...> class... D>
struct any_cond <C, D...>
{
	template <typename... T> using map =
		_or <C <T...>, typename all_cond <D...>::template map <T...> >;
};

//-----------------------------------------------------------------------------

namespace details {

template <
	template <typename...> class F, typename A, typename B,
	bool = length <A>() == length <B>()
>
struct all2_ : _false { };

template <
	template <typename...> class F, typename A, typename B,
	bool = length <A>() == length <B>()
>
struct any2_ : _false { };

template <
	template <typename...> class F,
	template <typename...> class C, typename... A,
	template <typename...> class D, typename... B
>
struct all2_<F, C <A...>, D <B...>, true> : _and <F <A, B>...> { };

template <
	template <typename...> class F,
	template <typename...> class C, typename... A,
	template <typename...> class D, typename... B
>
struct any2_<F, C <A...>, D <B...>, true> : _or <F <A, B>...> { };

}  // namespace details

template <template <typename...> class F, typename A, typename B>
using all2 = details::all2_<F, A, B>;

template <template <typename...> class F, typename A, typename B>
using any2 = details::any2_<F, A, B>;

//-----------------------------------------------------------------------------

template <size_t L>
struct eq_len_to
{
	template <typename P>
	using map = expr <length <P>() == L>;
};

template <typename P> using eq_len_of = eq_len_to <length <P>{}>;

namespace details {

template <typename P, bool = is_null <P>()>
struct eq_len_p_ : all_p <eq_len_of <car <P> >::template map, cdr <P> > { };

template <typename P>
struct eq_len_p_<P, true> : _true { };

}  // namespace details

template <typename P>    using eq_len_p = details::eq_len_p_<P>;
template <typename... P> using eq_len   = eq_len_p <pack <P...> >;

//-----------------------------------------------------------------------------

namespace details {

template <template <typename...> class F, typename P, bool = any_null_p <P>()>
struct alls_p_ :
	_if <embed <F, cars_p <P> >{}, alls_p_<F, cdrs_p <P> >, _false> { };

template <template <typename...> class F, typename P, bool = any_null_p <P>()>
struct anys_p_ :
	_if <embed <F, cars_p <P> >{}, _true, anys_p_<F, cdrs_p <P> > > { };

template <template <typename...> class F, typename P>
struct alls_p_<F, P, true> : _true { };

template <template <typename...> class F, typename P>
struct anys_p_<F, P, true> : _false { };

}  // namespace details

template <template <typename...> class F, typename P>
using alls_p = _if <eq_len_p <P>{}, details::alls_p_<F, P>, _false>;

template <template <typename...> class F, typename P>
using anys_p = _if <eq_len_p <P>{}, details::anys_p_<F, P>, _false>;

template <template <typename...> class F, typename... P>
using alls = alls_p <F, pack <P...> >;

template <template <typename...> class F, typename... P>
using anys = anys_p <F, pack <P...> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename P, bool = any_null_p <P>{}>
struct tran_ : cons_t <cars_p <P>, type_of <tran_<cdrs_p <P> > > > { };

template <typename P> struct tran_<P, true> : null_of_t <P> { };

}  // namespace details

template <typename P> using tran_pt = details::tran_<P>;
template <typename P> using tran_p  = type_of <tran_pt <P> >;

template <typename... P> using tran_t = tran_pt <pack <P...> >;
template <typename... P> using tran   = type_of <tran_t <P...> >;

//-----------------------------------------------------------------------------

template <typename P>
using tran_len_p = int_min <sz_map <length_of, select_p <is_pack, P> > >;

template <typename... P>
using tran_len = tran_len_p <pack <P...> >;

//-----------------------------------------------------------------------------

}  // namespace packs

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_PACK_REDUCE_HPP
