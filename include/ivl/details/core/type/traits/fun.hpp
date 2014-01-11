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

template <typename S> struct raw_fun_t { using type = S; };
template <typename S> using  raw_fun = type_of <raw_fun_t <S> >;

template <typename R, typename... A>
struct raw_fun_t <R(A...)> { using type = R(A...); };

template <typename R, typename... A>
struct raw_fun_t <R(A...) const> { using type = R(A...); };

template <typename R, typename... A>
struct raw_fun_t <R(A...) volatile> { using type = R(A...); };

template <typename R, typename... A>
struct raw_fun_t <R(A...) const volatile> { using type = R(A...); };

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)

template <typename R, typename... A>
struct raw_fun_t <R(A...) &> { using type = R(A...); };

template <typename R, typename... A>
struct raw_fun_t <R(A...) const&> { using type = R(A...); };

template <typename R, typename... A>
struct raw_fun_t <R(A...) volatile&> { using type = R(A...); };

template <typename R, typename... A>
struct raw_fun_t <R(A...) const volatile&> { using type = R(A...); };

template <typename R, typename... A>
struct raw_fun_t <R(A...) &&> { using type = R(A...); };

template <typename R, typename... A>
struct raw_fun_t <R(A...) const&&> { using type = R(A...); };

template <typename R, typename... A>
struct raw_fun_t <R(A...) volatile&&> { using type = R(A...); };

template <typename R, typename... A>
struct raw_fun_t <R(A...) const volatile&&> { using type = R(A...); };

#endif  // IVL_HAS_FEATURE(cxx_reference_qualified_functions)

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct is_fun_ : _false { };
template <typename S> struct fun_ret_;
template <typename S> struct fun_arg_;

template<typename R, typename... A>
struct is_fun_<R(A...)> : _true { };

template <typename R, typename... A>
struct fun_ret_<R(A...)> { using type = R; };

template <typename R, typename... A>
struct fun_arg_<R(A...)> : pack <A...> { };

}  // namespace details {

template <typename T> using is_fun = details::is_fun_<raw_fun <T> >;

template <typename S> using fun_ret_t = details::fun_ret_<raw_fun <S> >;
template <typename S> using fun_arg_t = details::fun_arg_<raw_fun <S> >;

template <typename S> using fun_ret = type_of <fun_ret_t <S> >;
template <typename S> using fun_arg = type_of <fun_arg_t <S> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_FUN_HPP
