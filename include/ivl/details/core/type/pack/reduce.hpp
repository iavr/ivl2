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

#ifndef IVL_DETAILS_CORE_TYPE_PACK_REDUCE_HPP
#define IVL_DETAILS_CORE_TYPE_PACK_REDUCE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace packs {

//-----------------------------------------------------------------------------

namespace details {

template <typename P, bool = is_null <P>{}>
struct _and_p_ : public _if <car <P>{}, _and_p_<cdr <P> >, _false> { };

template <typename P, bool = is_null <P>{}>
struct _or_p_ : public _if <car <P>{}, _true, _or_p_<cdr <P> > > { };

template <typename P> struct _and_p_<P, true> : public _true  { };
template <typename P> struct _or_p_ <P, true> : public _false { };

}  // namespace details

template <typename P> using _and_p = details::_and_p_<P>;
template <typename P> using _or_p  = details::_or_p_<P>;

template <typename... E> using _and = _and_p <pack <E...> >;
template <typename... E> using _or  = _or_p  <pack <E...> >;

//-----------------------------------------------------------------------------

namespace details {

template <template <typename...> class F, typename P, bool = is_null <P>{}>
struct all_p_ : public _if <F <car <P> >{}, all_p_<F, cdr <P> >, _false> { };

template <template <typename...> class F, typename P, bool = is_null <P>{}>
struct any_p_ : public _if <F <car <P> >{}, _true, any_p_<F, cdr <P> > > { };

template <template <typename...> class F, typename P>
struct all_p_ <F, P, true> : public _true  { };

template <template <typename...> class F, typename P>
struct any_p_ <F, P, true> : public _false { };

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

template <typename P> using all_null_p = all_p <is_null, P>;
template <typename P> using any_null_p = any_p <is_null, P>;

template <typename... E> using all_null = all_null_p <pack <E...> >;
template <typename... E> using any_null = any_null_p <pack <E...> >;

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

template <size_t L>
struct eq_len_to
{
	template <typename P>
	using map = expr <length <P>() == L>;
};

template <typename P> using eq_len_of = eq_len_to <length <P>{}>;

template <typename P>
struct eq_len_p :
	public all_p <eq_len_of <car <P> >::template map, cdr <P> > { };

template <template <typename...> class C>
struct eq_len_p <C <> > : public _true { };

template <typename... P>
using eq_len = eq_len_p <pack <P...> >;

//-----------------------------------------------------------------------------

namespace details {

template <template <typename...> class F, typename P, bool = any_null_p <P>{}>
struct alls_p_ :
	public _if <embed <F, cars_p <P> >{}, alls_p_<F, cdrs_p <P> >, _false> { };

template <template <typename...> class F, typename P, bool = any_null_p <P>{}>
struct anys_p_ :
	public _if <embed <F, cars_p <P> >{}, _true, anys_p_<F, cdrs_p <P> > > { };

template <template <typename...> class F, typename P>
struct alls_p_<F, P, true> : public _true { };

template <template <typename...> class F, typename P>
struct anys_p_<F, P, true> : public _false { };

}  // namespace details

//-----------------------------------------------------------------------------

template <template <typename...> class F, typename P>
using anys_p = _if <eq_len_p <P>{}, details::anys_p_<F, P>, _false>;

template <template <typename...> class F, typename P>
using alls_p = _if <eq_len_p <P>{}, details::alls_p_<F, P>, _false>;

template <template <typename...> class F, typename... P>
using anys = anys_p <F, pack <P...> >;

template <template <typename...> class F, typename... P>
using alls = alls_p <F, pack <P...> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename P, bool = any_null_p <P>{}>
struct tran_ : public cons_t <cars_p <P>, type_of <tran_<cdrs_p <P> > > > { };

template <typename P>
struct tran_<P, true> { using type = null_of <P>; };

template <typename P, size_t = length <P>()>
struct tran_opt : public tran_<P> { };

template <typename P> struct tran_opt <P, 1> : public car_t <P> { };
template <typename P> struct tran_opt <P, 0>;

}  // namespace details

template <typename P> using tran_pt = details::tran_opt <P>;
template <typename P> using tran_p  = type_of <tran_pt <P> >;

template <typename... P> using tran_t = tran_pt <pack <P...> >;
template <typename... P> using tran   = type_of <tran_t <P...> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename A>
INLINE constexpr A min_(A a, A b) { return a < b ? a : b; }

template <typename A>
INLINE constexpr A max_(A a, A b) { return a > b ? a : b; }

template <
	typename T, template <typename...> class F,
	typename P, bool = is_null <P>{}
>
struct int_min_ : public integral <T,
	min_(F <car <P> >{}(), int_min_<T, F, cdr <P> >{}())
> {};

template <
	typename T, template <typename...> class F,
	typename P, bool = is_null <P>{}
>
struct int_max_ : public integral <T,
	max_(F <car <P> >{}(), int_max_<T, F, cdr <P> >{}())
> {};

template <typename T, template <typename...> class F, typename P>
struct int_min_<T, F, P, true> :
	public integral <T, std::numeric_limits <T>::max()> {};

template <typename T, template <typename...> class F, typename P>
struct int_max_<T, F, P, true> :
	public integral <T, std::numeric_limits <T>::min()> {};

}  // namespace details

//-----------------------------------------------------------------------------

template <typename T, template <typename...> class F, typename P>
using integral_min_p = details::int_min_<T, F, P>;

template <typename T, template <typename...> class F, typename P>
using integral_max_p = details::int_max_<T, F, P>;

template <typename T, template <typename...> class F, typename... E>
using integral_min = integral_min_p <T, F, pack <E...> >;

template <typename T, template <typename...> class F, typename... E>
using integral_max = integral_max_p <T, F, pack <E...> >;

template <template <typename...> class F, typename P>
using num_min_p = integral_min_p <int, F, P>;

template <template <typename...> class F, typename P>
using num_max_p = integral_max_p <int, F, P>;

template <template <typename...> class F, typename... E>
using num_min = integral_min <int, F, E...>;

template <template <typename...> class F, typename... E>
using num_max = integral_max <int, F, E...>;

template <template <typename...> class F, typename P>
using sz_min_p = integral_min_p <size_t, F, P>;

template <template <typename...> class F, typename P>
using sz_max_p = integral_max_p <size_t, F, P>;

template <template <typename...> class F, typename... E>
using sz_min = integral_min <size_t, F, E...>;

template <template <typename...> class F, typename... E>
using sz_max = integral_max <size_t, F, E...>;

//-----------------------------------------------------------------------------

}  // namespace packs

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_PACK_REDUCE_HPP
