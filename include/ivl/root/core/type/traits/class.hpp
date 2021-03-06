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

#ifndef IVL_CORE_TYPE_TRAITS_CLASS_HPP
#define IVL_CORE_TYPE_TRAITS_CLASS_HPP

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

#if IVL_HAS_FEATURE(is_class)

template <typename T> struct is_class : expr <__is_class(T)> { };

#else

template <typename T> using is_class_test = int T::*;

template <typename T>
using is_class = expr <null_sfinae <is_class_test, T>() && !is_union <T>()>;

#endif  // IVL_HAS_FEATURE(is_class)

//-----------------------------------------------------------------------------

template <typename T>
using is_derive = expr <is_class <T>() && !is_final <T>()>;

template <bool D, typename... T> struct derive_ : T... { };
template <        typename... T> struct derive_<false, T...>;

template <typename... T>
using derive = details::derive_<_and <is_derive <T>...>{}, T...>;

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(is_empty)

template <typename T> struct is_empty : expr <__is_empty(T)> { };

#else

template <typename T, typename N = size <sizeof(T)> >
using is_empty_test = only_if <sizeof(derive <T, sized <N{}> >) == N{}>;

template <typename T> using is_empty = sfinae <is_empty_test, T>;

#endif  // IVL_HAS_FEATURE(is_empty)

//-----------------------------------------------------------------------------

template <typename T> using is_complete_test = size <sizeof(T)>;

template <
	typename T,
	bool = is_fun <remove_ptr <T> >(), bool = is_member_ptr <T>()
>
struct is_complete_ : sfinae <is_complete_test, remove_ref <T> > { };

template <> struct is_complete_<void> : _true { };

template <typename T> struct is_complete_<T, true, false> :
	is_complete_<fun_ret <remove_ptr <T> > > { };

template <typename T> struct is_complete_<T, false, true> :
	is_complete_<member_class <T> > { };

template <typename T> using is_complete = is_complete_<T>;

//-----------------------------------------------------------------------------

template <typename T> using is_abstract_test = T (*)[1];
template <typename T> using is_abstract =
	expr <!null_sfinae <is_abstract_test, T>() && is_class <T>()>;

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(is_polymorphic)

template <typename T>
struct is_poly : expr <__is_polymorphic(T)> { };

#else

template <typename T> using is_poly_test =
	decltype((T*) dynamic_cast <const volatile void*>(gen <T*>()));

template <typename T> using is_poly = sfinae <is_poly_test, T>;

#endif  // IVL_HAS_FEATURE(is_polymorphic)

//-----------------------------------------------------------------------------

}  // namespace details

using details::is_class;
using details::is_derive;
using details::is_empty;
using details::is_complete;
using details::is_abstract;
using details::is_poly;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_TRAITS_HPP
