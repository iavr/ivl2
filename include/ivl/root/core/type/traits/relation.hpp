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

#ifndef IVL_CORE_TYPE_TRAITS_RELATION_HPP
#define IVL_CORE_TYPE_TRAITS_RELATION_HPP

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

#if IVL_HAS_FEATURE(is_base_of)

template <typename B, typename D>
struct is_base_eq : expr <__is_base_of(B, D)> { };

#else

namespace is_base_eq_test
{
	template <class T>
	struct base { base(const volatile T&); };

	template <class T>
	struct der
	{
		operator const volatile T&();
		template <class U> operator const base <U>&();
	};

	template <class B, class D>
	using map = decltype(base <B>(gen <der <D> >()));
}

template <typename B, typename D>
using is_base_eq =
	_not <sfinae <is_base_eq_test::map, B, D>() && is_class <B>{}>;

#endif  // IVL_HAS_FEATURE(is_base_of)

//-----------------------------------------------------------------------------

template <typename B, typename D>
using is_base = expr <is_base_eq <B, D>() && !eq <B, D>()>;

template <typename A, typename B>
using is_related = expr <is_base_eq <A, B>() || is_base_eq <B, A>()>;

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(is_convertible_to)

template <typename S, typename D>
struct is_conv : expr <__is_convertible_to(S, D) && !is_abstract <D>()> { };

#else

template <typename S, typename D>
using is_conv_test = decltype(convert <D>(gen <S>()));

template <
	typename S, typename D,
	bool = is_void <S>() || is_fun <D>() || is_arr <D>()
>
struct is_conv_ : is_void <D> { };

template <typename S, typename D>
struct is_conv_ <S, D, false> :
	expr <sfinae <is_conv_test, S, D>() && !is_abstract <D>()> { };

template <typename S, typename D> using is_conv = is_conv_ <S, D>;

#endif  // IVL_HAS_FEATURE(is_convertible_to)

//-----------------------------------------------------------------------------

template <typename T, typename A>
using static_casts_test = decltype(static_cast <T>(gen <A>()));

template <typename T, typename A>
using dynamic_casts_test = decltype(dynamic_cast <T>(gen <A>()));

template <typename T, typename A>
using const_casts_test = decltype(const_cast <T>(gen <A>()));

template <typename T, typename A>
using reinterpret_casts_test = decltype(reinterpret_cast <T>(gen <A>()));

template <typename T, typename A>
using static_casts = sfinae <static_casts_test, T, A>;

template <typename T, typename A>
using dynamic_casts = sfinae <dynamic_casts_test, T, A>;

template <typename T, typename A>
using const_casts = sfinae <const_casts_test, T, A>;

template <typename T, typename A>
using reinterpret_casts = sfinae <reinterpret_casts_test, T, A>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename A, typename B>
using ternary = decltype(true ? gen <A>() : gen <B>());

template <
	typename A, typename B,
	typename T = ternary <A, B>, bool = all <is_rref, A, B>()
>
struct common_ternary : id_t <T> { };

template <typename A, typename B, typename T>
struct common_ternary <A, B, T, false> : remove_rref_t <T> { };

//-----------------------------------------------------------------------------

// extended elsewhere
template <typename A, typename B>
struct common_rec : id_t <nat> { };

template <
	typename A, typename B,
	typename a = raw_type <A>, typename b = raw_type <B>
>
struct common_user : common_rec <a, b> { };

template <typename A, typename B, typename a>
struct common_user <A, B, a, a> : common_ternary <A, B> { };

template <typename A, typename B, typename T = type_of <common_user <A, B> > >
struct common2_t : id_t <T> { };

template <typename A, typename B>
struct common2_t <A, B, nat> : common_ternary <A, B> { };

template <typename A, typename B>
using common2 = type_of <common2_t <A, B> >;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename P> struct common_pt;
template <typename P> using  common_p = type_of <common_pt <P> >;

template <typename... T> using common_t = common_pt <pack <T...> >;
template <typename... T> using common = type_of <common_t <T...> >;

template <template <typename...> class C, typename E>
struct common_pt <C <E> > : id_t <E> { };

template <
	template <typename...> class C,
	typename E, typename F, typename... G
>
struct common_pt <C <E, F, G...> > :
	common_pt <C <details::common2 <E, F>, G...> > { };

//-----------------------------------------------------------------------------

namespace details {

template <typename P, bool = all_p <is_constant, P>()>
struct const_common_ : common_pt <map <value_type_of, P> > { };

template <typename P>
struct const_common_<P, false> :
	common_pt <select_p <neg <is_constant>::template map, P> > { };

}  // namespace details

template <typename P> using const_common_pt = details::const_common_<P>;
template <typename P> using const_common_p  = type_of <const_common_pt <P> >;

template <typename... T> using const_common_t = const_common_pt <pack <T...> >;
template <typename... T> using const_common = type_of <const_common_t <T...> >;

//-----------------------------------------------------------------------------

template <typename D, typename P>
struct common_or_pt : common_pt <P> { };

template <typename D, template <typename...> class C>
struct common_or_pt <D, C <> > : id_t <D> { };

template <typename D, typename P>
using common_or_p = type_of <common_or_pt <D, P> >;

template <typename D, typename... T>
using common_or_t = common_or_pt <D, pack <T...> >;

template <typename D, typename... T>
using common_or = type_of <common_or_t <D, T...> >;

//-----------------------------------------------------------------------------

using details::is_base_eq;
using details::is_base;
using details::is_related;
using details::is_conv;

using details::static_casts;
using details::dynamic_casts;
using details::const_casts;
using details::reinterpret_casts;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_TRAITS_RELATION_HPP
