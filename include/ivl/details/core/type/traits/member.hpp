/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright	C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_MEMBER_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_MEMBER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

template <typename T, template <typename...> class F>
struct is_member_ptr_f_ : _false { };

template <typename T, typename C, template <typename...> class F>
struct is_member_ptr_f_<T C::*, F> : F <T> { };

template <typename T, template <typename...> class F>
struct is_member_ptr_f : is_member_ptr_f_<remove_cv <T>, F> { };

}  // namespace details

template <typename T>
using is_member_ptr = details::is_member_ptr_f <T, always>;

template <typename T>
using is_method_ptr = details::is_member_ptr_f <T, is_fun>;

template <typename T>
using is_prop_ptr = details::is_member_ptr_f <T, neg <is_fun>::map>;

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename M> struct member_class_ { };
template <typename M> struct member_type_ { };

template <typename T, typename C>
struct member_class_<T C::*> { using type = C; };

template <typename T, typename C>
struct member_type_<T C::*> { using type = T; };

//-----------------------------------------------------------------------------

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...)> { using type = C; };

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) const> { using type = C const; };

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) volatile> { using type = C volatile; };

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) const volatile>
	{ using type = C const volatile; };

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) &> { using type = C&; };

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) const&> { using type = C const&; };

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) volatile&> { using type = C volatile&; };

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) const volatile&>
	{ using type = C const volatile&; };

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) &&> { using type = C&&; };

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) const&&> { using type = C const&&; };

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) volatile&&> { using type = C volatile&&; };

template <typename R, typename C, typename ...A>
struct member_class_<R (C::*)(A...) const volatile&&>
	{ using type = C const volatile&&; };

#endif  // IVL_HAS_FEATURE(cxx_reference_qualified_functions)

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename M>
using member_class_t = details::member_class_<raw_type <M> >;

template <typename M>
using member_type_t = details::member_type_<raw_type <M> >;

template <typename M> using member_class = type_of <member_class_t <M> >;
template <typename M> using member_type  = type_of <member_type_t <M> >;

template <typename M> using member_fun_t = raw_fun_t <member_type <M> >;
template <typename M> using member_ret_t = fun_ret_t <member_type <M> >;
template <typename M> using member_arg_t = fun_arg_t <member_type <M> >;

template <typename M> using member_fun = type_of <member_fun_t <M> >;
template <typename M> using member_ret = type_of <member_ret_t <M> >;
template <typename M> using member_arg = type_of <member_arg_t <M> >;

//-----------------------------------------------------------------------------

template <typename C, typename M>
using is_ptr_of = eq <raw_type <member_class <M> >, raw_type <C> >;

template <typename C, typename M>
using is_member_ptr_of = expr <is_member_ptr <M>() && is_ptr_of <C, M>()>;

template <typename C, typename M>
using is_method_ptr_of = expr <is_method_ptr <M>() && is_ptr_of <C, M>()>;

template <typename C, typename M>
using is_prop_ptr_of = expr <is_prop_ptr <M>() && is_ptr_of <C, M>()>;

//-----------------------------------------------------------------------------

template <typename C, typename R, typename... A>
struct member_ptr_t : member_ptr_t <C, R(A...)> { };

template <typename C, typename T>
struct member_ptr_t <C, T> : id_t <T raw_type <C>::*> { };

template <typename C, typename R, typename... A>
using member_ptr = type_of <member_ptr_t <C, R, A...> >;

//-----------------------------------------------------------------------------

template <typename C, typename R, typename ...A>
struct member_ptr_t <C, R(A...)>
	{ using type = R (C::*)(A...); };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const, R(A...)>
	{ using type = R (C::*)(A...) const; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C volatile, R(A...)>
	{ using type = R (C::*)(A...) volatile; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const volatile, R(A...)>
	{ using type = R (C::*)(A...) const volatile; };

//-----------------------------------------------------------------------------

template <typename C, typename R, typename ...A>
struct member_ptr_t <C&, R(A...)>
	{ using type = R (C::*)(A...) &; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const&, R(A...)>
	{ using type = R (C::*)(A...) const&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C volatile&, R(A...)>
	{ using type = R (C::*)(A...) volatile&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const volatile&, R(A...)>
	{ using type = R (C::*)(A...) const volatile&; };

//-----------------------------------------------------------------------------

template <typename C, typename R, typename ...A>
struct member_ptr_t <C&&, R(A...)>
	{ using type = R (C::*)(A...) &&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const&&, R(A...)>
	{ using type = R (C::*)(A...) const&&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C volatile&&, R(A...)>
	{ using type = R (C::*)(A...) volatile&&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const volatile&&, R(A...)>
	{ using type = R (C::*)(A...) const volatile&&; };

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_MEMBER_HPP
