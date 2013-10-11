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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_FUN_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_FUN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template<typename> struct is_fun : public _false{ };

template<typename R, typename... A>
struct is_fun <R(A...)> : public _true { };

template<typename R, typename... A>
struct is_fun <R(A...) const> : public _true { };

template<typename R, typename... A>
struct is_fun <R(A...) volatile> : public _true { };

template<typename R, typename... A>
struct is_fun <R(A...) const volatile> : public _true { };

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, template <typename...> class F>
struct is_member_ptr_f_ : public _false { };

template <typename T, typename C, template <typename...> class F>
struct is_member_ptr_f_<T C::*, F> : public F <T> { };

template <typename T, template <typename...> class F>
struct is_member_ptr_f : public is_member_ptr_f_<remove_cv <T>, F> { };

//-----------------------------------------------------------------------------

template <typename T>
using is_member_ptr = is_member_ptr_f <T, always>;

template <typename T>
using is_method_ptr = is_member_ptr_f <T, is_fun>;

template <typename T>
using is_prop_ptr = is_member_ptr_f <T, neg <is_fun>::map>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::is_member_ptr;
using details::is_method_ptr;
using details::is_prop_ptr;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_FUN_HPP
