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

#ifndef IVL_CORE_TYPE_TRAITS_TRANSFORM_HPP
#define IVL_CORE_TYPE_TRAITS_TRANSFORM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = is_arr <T>(), bool = is_fun <T>()>
struct add_uref_ : id_t <T&&> { };

template <typename T>
struct add_uref_<T, false, false> : id_t <T> { };

template <typename T, bool = is_void <T>()>
struct add_rref_ : id_t <T> { };

template <typename T>
struct add_rref_<T, false> : id_t <T&&> { };

template <typename T, bool = is_void <T>() || is_lref <T>()>
struct add_lref_ : id_t <T> { };

template <typename T>
struct add_lref_<T, false> : id_t <T&> { };

}  // namespace details

template <typename T> using add_uref_t = details::add_uref_<T>;
template <typename T> using add_rref_t = details::add_rref_<T>;
template <typename T> using add_lref_t = details::add_lref_<T>;

template <typename T> struct remove_ref_t       : id_t <T> { };
template <typename T> struct remove_ref_t <T&>  : id_t <T> { };
template <typename T> struct remove_ref_t <T&&> : id_t <T> { };

template <typename T> using add_uref   = type_of <add_uref_t   <T> >;
template <typename T> using add_rref   = type_of <add_rref_t   <T> >;
template <typename T> using add_lref   = type_of <add_lref_t   <T> >;
template <typename T> using remove_ref = type_of <remove_ref_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct add_ptr_     : id_t <T*> { };
template <typename T> struct add_ptr_<T*> : id_t <T*> { };

template <typename T> struct remove_ptr_     : id_t <T> { };
template <typename T> struct remove_ptr_<T*> : id_t <T> { };

}  // namespace details

template <typename T>
using add_ptr_t = details::add_ptr_<remove_ref <T> >;

template <typename T>
using remove_ptr_t = details::remove_ptr_<remove_cv <T> >;

template <typename T> using add_ptr    = type_of <add_ptr_t    <T> >;
template <typename T> using remove_ptr = type_of <remove_ptr_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = is_ref <T>() || is_fun <T>() || is_const <T>()>
struct add_const_ : id_t <T> { };

template <typename T>
struct add_const_<T, false> : id_t <const T> { };

}  // namespace details

//-----------------------------------------------------------------------------

template <typename T> using add_const_t = details::add_const_<T>;

template <typename T> struct remove_const_t           : id_t <T> { };
template <typename T> struct remove_const_t <const T> : id_t <T> { };

template <typename T> using add_const    = type_of <add_const_t    <T> >;
template <typename T> using remove_const = type_of <remove_const_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = is_ref <T>() || is_fun <T>() || is_vol <T>()>
struct add_vol_ : id_t <T> { };

template <typename T>
struct add_vol_<T, false> : id_t <volatile T> { };

}  // namespace details

template <typename T> using add_vol_t = details::add_vol_<T>;

template <typename T> struct remove_vol_t              : id_t <T> { };
template <typename T> struct remove_vol_t <volatile T> : id_t <T> { };

template <typename T> using add_vol    = type_of <add_vol_t    <T> >;
template <typename T> using remove_vol = type_of <remove_vol_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct add_cv_ : add_const_t <add_vol <T> > { };

}  // namespace details

template <typename T> using add_cv_t = details::add_cv_ <T>;
template <typename T> using add_cv = type_of <add_cv_t <T> >;

// no alias: fwd-declared
// remove_cv defined @begin.hpp
template <typename T>
struct remove_cv_t : remove_vol_t <remove_const <T> > { };

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

template <
	template <typename> class R,
	template <typename> class L,
	template <typename> class C
>
struct choose_ref
{
	template <typename T> struct map_t;
	template <typename T> using  map = type_of <map_t <T> >;
	template <typename T> struct map_t <T&&>      : id_t <R <T> > { };
	template <typename T> struct map_t <T&>       : id_t <L <T> > { };
	template <typename T> struct map_t <const T&> : id_t <C <T> > { };
};

template <typename C, typename T>
using choose_r = typename C::template map <T&&>;

template <typename C, typename T>
using choose_l = typename C::template map <T&>;

template <typename C, typename T>
using choose_cl = typename C::template map <const T&>;

//-----------------------------------------------------------------------------

template <typename T>
using ref2ptr_t = _if <is_ref <T>{}, add_ptr_t <remove_ref <T> >, id_t <T> >;

template <typename T>
using ptr2ref_t = _if <is_ptr <T>{}, add_lref_t <remove_ptr <T> >, id_t <T> >;

template <typename T> using ref2ptr = type_of <ref2ptr_t <T> >;
template <typename T> using ptr2ref = type_of <ptr2ref_t <T> >;

//-----------------------------------------------------------------------------

template <typename T>
using is_clref = expr <is_lref <T>() && is_const <remove_ref <T> >()>;

template <typename T> using add_clref_t = add_lref_t <add_const <T> >;
template <typename T> using add_clref   = type_of <add_clref_t <T> >;

//-----------------------------------------------------------------------------

template <typename T> using raw_type_t = remove_cv_t <remove_ref <T> >;
template <typename T> using raw_type   = type_of <raw_type_t <T> >;

template <typename T> using bare_type_t = remove_ptr_t <raw_type <T> >;
template <typename T> using bare_type   = type_of <bare_type_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

// extended elsewhere
template <typename T>
struct copy_rec : id_t <T> { };

template <typename T>
struct copy_ : _if <is_arr <T>{}, id_t <remove_ext <T>*>,
	_if <is_fun <T>{}, add_ptr_t <T>, copy_rec <remove_cv <T> > >
> { };

template <typename T>
struct decay_ : _if <is_arr <T>{}, id_t <remove_ext <T>*>,
	_if <is_fun <T>{}, add_ptr_t <T>, remove_cv_t <T> >
> { };

}  // namespace details

template <typename T> using copy_t = details::copy_<remove_ref <T> >;
template <typename T> using copy = type_of <copy_t <T> >;

template <typename T> using decay_t = details::decay_<remove_ref <T> >;
template <typename T> using decay = type_of <decay_t <T> >;

//-----------------------------------------------------------------------------

template <typename T> struct reuse_t       : id_t <T> { };
template <typename T> struct reuse_t <T&&> : id_t <add_const <T>&> { };

template <typename T> using reuse = type_of <reuse_t <T> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_TRAITS_TRANSFORM_HPP
