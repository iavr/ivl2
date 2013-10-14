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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_TRANSFORM_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_TRANSFORM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = is_void <T>()>
struct add_rref_t_ { using type = T; };

template <typename T>
struct add_rref_t_<T, false> { using type = T&&; };

template <typename T, bool = is_void <T>() || is_lref <T>()>
struct add_lref_t_ { using type = T; };

template <typename T>
struct add_lref_t_<T, false> { using type = T&; };

}  // namespace details

template <typename T> using add_rref_t = details::add_rref_t_<T>;
template <typename T> using add_lref_t = details::add_lref_t_<T>;

template <typename T> struct remove_ref_t       { using type = T; };
template <typename T> struct remove_ref_t <T&>  { using type = T; };
template <typename T> struct remove_ref_t <T&&> { using type = T; };

template <typename T> using add_rref   = type_of <add_rref_t   <T> >;
template <typename T> using add_lref   = type_of <add_lref_t   <T> >;
template <typename T> using remove_ref = type_of <remove_ref_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct add_ptr_t_     { using type = T*; };
template <typename T> struct add_ptr_t_<T*> { using type = T*; };

template <typename T> struct remove_ptr_t_     { using type = T; };
template <typename T> struct remove_ptr_t_<T*> { using type = T; };

}  // namespace details

template <typename T>
using add_ptr_t = details::add_ptr_t_<remove_ref <T> >;

template <typename T>
using remove_ptr_t = details::remove_ptr_t_<remove_cv <T> >;

template <typename T> using add_ptr    = type_of <add_ptr_t    <T> >;
template <typename T> using remove_ptr = type_of <remove_ptr_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = is_ref <T>() || is_fun <T>() || is_const <T>()>
struct add_const_t_ { using type = T;};

template <typename T>
struct add_const_t_<T, false> { using type = const T;};

}  // namespace details

//-----------------------------------------------------------------------------

template <typename T> using add_const_t = details::add_const_t_<T>;

template <typename T> struct remove_const_t           { using type = T;};
template <typename T> struct remove_const_t <const T> { using type = T;};

template <typename T> using add_const    = type_of <add_const_t    <T> >;
template <typename T> using remove_const = type_of <remove_const_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = is_ref <T>() || is_fun <T>() || is_vol <T>()>
struct add_vol_t_ { using type = T;};

template <typename T>
struct add_vol_t_<T, false> { using type = volatile T;};

}  // namespace details

template <typename T> using add_vol_t = details::add_vol_t_<T>;

template <typename T> struct remove_vol_t              { using type = T;};
template <typename T> struct remove_vol_t <volatile T> { using type = T;};

template <typename T> using add_vol    = type_of <add_vol_t    <T> >;
template <typename T> using remove_vol = type_of <remove_vol_t <T> >;

//-----------------------------------------------------------------------------

namespace details {
template <typename T> struct add_cv_t_ : public add_const_t <add_vol <T> > { };
}  // namespace details

template <typename T> using add_cv_t = details::add_cv_t_ <T>;
template <typename T> using add_cv = type_of <add_cv_t <T> >;

// remove_cv_t defined as struct because it is fwd-declared @begin.hpp
// remove_cv defined @begin.hpp
template <typename T>
struct remove_cv_t : public remove_vol_t <remove_const <T> > { };

//-----------------------------------------------------------------------------

template <template <typename...> class P, template <typename...> class F>
struct transfer
{
	template <typename S, typename D>
	using map = _if <P <S>{}, F <D>, id_t <D> >;
};

//-----------------------------------------------------------------------------

template <typename S, typename D>
using tx_rref_t = transfer <is_rref, add_rref_t>::map <S, D>;

template <typename S, typename D>
using tx_lref_t = transfer <is_lref, add_lref_t>::map <S, D>;

template <typename S, typename D>
using tx_ptr_t = transfer <is_ptr, add_ptr_t>::map <S, D>;

template <typename S, typename D>
using tx_const_t = transfer <is_const, add_const_t>::map <S, D>;

template <typename S, typename D>
using tx_vol_t = transfer <is_vol, add_vol_t>::map <S, D>;

template <typename S, typename D> using tx_rref  = type_of <tx_rref_t <S, D> >;
template <typename S, typename D> using tx_lref  = type_of <tx_lref_t <S, D> >;
template <typename S, typename D> using tx_ptr   = type_of <tx_ptr_t <S, D> >;
template <typename S, typename D> using tx_const = type_of <tx_const_t <S, D> >;
template <typename S, typename D> using tx_vol   = type_of <tx_vol_t <S, D> >;

//-----------------------------------------------------------------------------

template <typename S, typename D>
using tx_cv_t = tx_vol_t <S, tx_const <S, D> >;

template <typename S, typename D> using tx_cv = type_of <tx_cv_t <S, D> >;

//-----------------------------------------------------------------------------

template <typename T> using raw_type_t = remove_cv_t <remove_ref <T> >;
template <typename T> using raw_type   = type_of <raw_type_t <T> >;

template <typename T> using bare_type_t = remove_ptr_t <raw_type <T> >;
template <typename T> using bare_type   = type_of <bare_type_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T>
using decay_t_ = _if <is_arr <T>{}, id_t <remove_ext <T>*>,
	_if <is_fun <T>{}, add_ptr_t <T>, remove_cv_t <T> >
>;

}  // namespace details

template <typename T> using decay_t = details::decay_t_ <remove_ref <T> >;
template <typename T> using decay   = type_of <decay_t <T> >;

//-----------------------------------------------------------------------------

template <typename T> struct keep_t       { using type = T; };
template <typename T> struct keep_t <T&&> { using type = add_const <T>&; };

template <typename T> using keep = type_of <keep_t <T> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_TRANSFORM_HPP