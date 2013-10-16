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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_RELATION_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_RELATION_HPP

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
struct is_base_eq : public expr <__is_base_of(B, D)> { };

#else

struct is_base_eq_test : public input <>
{
	template <class T>
	struct base { base(const volatile T&); };

	template <class T>
	struct der
	{
		operator const volatile T& ();
		template <class U> operator const base <U>&();
	};

	template <class B, class D> static
	target <sizeof(base <B>(generate <der <D> >()))> test(int);
};

template <typename B, typename D>
using is_base_eq = expr <!sfinae <is_base_eq_test, B, D>() && is_class <B>()>;

#endif  // IVL_HAS_FEATURE(is_base_of)

//-----------------------------------------------------------------------------

template <typename B, typename D>
using is_base = expr <is_base_eq <B, D>() && !eq <B, D>()>;

template <typename A, typename B>
using is_related = expr <is_base_eq <A, B>() || is_base_eq <B, A>()>;

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(is_convertible_to)

template <typename S, typename D>
struct is_conv : public expr <__is_convertible_to(S, D)> { };

template <typename S, typename D> using is_conv_ = is_conv <S, D>;

#else

struct is_conv_test : public input <>
{
	template <typename S, typename D> static
	target <sizeof(convert <D>(generate <S>()))> test(int);
};

template <
	typename S, typename D,
	bool = is_void <S>() || is_fun <D>() || is_arr <D>()
>
struct is_conv_ : public is_void <D> { };

template <typename S, typename D>
struct is_conv_ <S, D, false> :
	public expr <sfinae <is_conv_test, S, D>() && !is_abstract <D>()> { };

template <typename S, typename D> using is_conv = is_conv_ <S, D>;

#endif  // IVL_HAS_FEATURE(is_convertible_to)

//-----------------------------------------------------------------------------

}  // namespace details

using details::is_base_eq;
using details::is_base;
using details::is_related;
using details::is_conv;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_RELATION_HPP
