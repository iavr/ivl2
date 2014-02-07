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

#ifndef IVL_CORE_TYPE_TRAITS_LIFE_HPP
#define IVL_CORE_TYPE_TRAITS_LIFE_HPP

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

template <typename T, typename... A>
using is_cons_test = decltype(T(gen <A>()...));

template <bool, typename T, typename... A>  // bool: T is scalar or ref
struct is_cons_ : sfinae <is_cons_test, T, A...> { };

template <typename R, typename... B, typename... A>
struct is_cons_<false, R(B...), A...> : _false { };

//-----------------------------------------------------------------------------
// is_cons: scalars and references

template <typename T>
struct is_cons_<true, T> : is_scalar <T> { };

template <typename T, typename A>
struct is_cons_<true, T, A> : is_conv <A, T> { };

template <typename T, typename A, typename...An>
struct is_cons_<true, T, A, An...> : _false { };

//-----------------------------------------------------------------------------
// is_cons: void and abstract types

template <bool fail, typename T, typename... A>
struct is_cons_check : _false { };

template <typename T, typename... A>
struct is_cons_check <false, T, A...> :
	is_cons_<is_scalar <T>() || is_ref <T>(), T, A...> { };

//-----------------------------------------------------------------------------
// is_cons: main entry point

// TODO: std version is much faster on GCC, especially with
// non-builtin traits; fix

#if defined(__clang__)

// no alias: faster on clang
template <typename T, typename... A>
struct is_cons :
	is_cons_check <any <is_void, T, A...>() || is_abstract <T>(), T, A...> { };

#else  // defined(__clang__)

template <typename T, typename... A>
using is_cons = expr <std::is_constructible <T, A...>{}>;

#endif  // defined(__clang__)

//-----------------------------------------------------------------------------
// is_cons: arrays

template <typename T, size_t N>
struct is_cons_<false, T[N]> : is_cons <remove_all_ext <T> > { };

template <typename T, size_t N, typename... A>
struct is_cons_<false, T[N], A...> : _false { };

template <class T, class... A>
struct is_cons_<false, T[], A...> : _false { };

//-----------------------------------------------------------------------------

template <typename T, typename A>
using is_explicit = expr <is_cons <T, A>() && !is_conv <A, T>()>;

//-----------------------------------------------------------------------------

template <typename T, typename A>
using is_assign_test = decltype(gen <T>() = gen <A>());

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

#endif  // IVL_CORE_TYPE_TRAITS_LIFE_HPP
