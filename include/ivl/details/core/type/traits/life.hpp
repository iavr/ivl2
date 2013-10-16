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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_LIFE_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_LIFE_HPP

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
// is_cons: arbitrary types and functions

struct is_cons_test : public input <>
{
	template <typename T, typename... A> static
	target <sizeof(T(generate <A>()...))> test(int);
};

template <bool, typename T, typename... A>  // bool: T is scalar or ref
struct is_cons_ : public sfinae <is_cons_test, T, A...> { };

template <typename R, typename... B, typename... A>
struct is_cons_<false, R(B...), A...> : public _false { };

//-----------------------------------------------------------------------------
// is_cons: scalars and references

template <typename T>
struct is_cons_<true, T> : public is_scalar <T> { };

template <typename T, typename A>
struct is_cons_<true, T, A> : public is_conv <A, T> { };

template <typename T, typename A, typename...An>
struct is_cons_<true, T, A, An...> : public _false { };

//-----------------------------------------------------------------------------
// is_cons: main entry point

template <typename T, typename... A>
using is_cons_fail = expr <any <is_void, T, A...>() || is_abstract <T>()>;

template <bool fail, typename T, typename... A>
struct is_cons_check : public _false { };

template <typename T, typename... A>
struct is_cons_check <false, T, A...> :
	public is_cons_<is_scalar <T>() || is_ref <T>(), T, A...> { };

template <typename T, typename... A>
using is_cons = is_cons_check <is_cons_fail <T, A...>{}, T, A...>;

//-----------------------------------------------------------------------------
// is_cons: arrays

template <typename T, size_t N>
struct is_cons_<false, T[N]> : public is_cons <remove_all_ext <T> > { };

template <typename T, size_t N, typename... A>
struct is_cons_<false, T[N], A...> : public _false { };

template <class T, class... A>
struct is_cons_<false, T[], A...> : public _false { };

//-----------------------------------------------------------------------------

template <typename T, typename A>
using is_explicit = expr <is_cons <T, A>() && !is_conv <A, T>()>;

//-----------------------------------------------------------------------------

struct is_assign_test : public input <>
{
	template <typename T, typename A> static
	target <sizeof(generate <T>() = generate <A>())> test(int);
};

template <typename T, typename A>
using is_assign = sfinae <is_assign_test, T, A>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::is_cons;
using details::is_explicit;
using details::is_assign;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_LIFE_HPP
