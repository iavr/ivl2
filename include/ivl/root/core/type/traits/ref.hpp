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

#ifndef IVL_CORE_TYPE_TRAITS_REF_HPP
#define IVL_CORE_TYPE_TRAITS_REF_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template <typename T>
using is_base_opt = expr <is_empty <T>() && !is_final <T>()>;

// no alias: faster on clang
template <typename T, typename R = raw_type <T>, typename Q = R>
struct base_opt_t : _if_t <is_base_opt <Q>{}, R, T> { };

template <typename T, typename R = raw_type <T>, typename Q = R>
using base_opt = type_of <base_opt_t <T, R, Q> >;

//-----------------------------------------------------------------------------

template <typename T> using uref_opt_t = base_opt_t <add_uref <T> >;
template <typename T> using uref_opt = type_of <uref_opt_t <T> >;

template <typename T> using rref_opt_t = base_opt_t <add_rref <T> >;
template <typename T> using rref_opt = type_of <rref_opt_t <T> >;

//-----------------------------------------------------------------------------

template <typename C, typename T> struct add_ref_t;
template <typename C, typename T> using  add_ref = type_of <add_ref_t <C, T> >;

template <typename T> struct add_ref_t <tag::rref, T> : id_t <T&&> { };
template <typename T> struct add_ref_t <tag::lref, T> : id_t <T&> { };
template <typename T> struct add_ref_t <tag::cref, T> : id_t <const T&> { };

//-----------------------------------------------------------------------------

// extended elsewhere
template <typename C, typename T> struct type_t : add_ref_t <C, T> { };
template <typename C, typename T> using type = type_of <type_t <C, T> >;

// extended elsewhere
template <typename C, typename T>
struct ref_t : base_opt_t <add_ref <C, T>, T> { };

template <typename C, typename T>
using ref = type_of <ref_t <C, T> >;

//-----------------------------------------------------------------------------

template <typename T> using r_type_t = type_t <tag::rref, T>;
template <typename T> using l_type_t = type_t <tag::lref, T>;
template <typename T> using c_type_t = type_t <tag::cref, T>;

template <typename T> using r_type = type_of <r_type_t <T> >;
template <typename T> using l_type = type_of <l_type_t <T> >;
template <typename T> using c_type = type_of <c_type_t <T> >;

//-----------------------------------------------------------------------------

template <typename T> using r_ref_t = ref_t <tag::rref, T>;
template <typename T> using l_ref_t = ref_t <tag::lref, T>;
template <typename T> using c_ref_t = ref_t <tag::cref, T>;

template <typename T> using r_ref = type_of <r_ref_t <T> >;
template <typename T> using l_ref = type_of <l_ref_t <T> >;
template <typename T> using c_ref = type_of <c_ref_t <T> >;

//-----------------------------------------------------------------------------

template <size_t I, typename P> using r_pick_p = r_ref <pick_p <I, P> >;
template <size_t I, typename P> using l_pick_p = l_ref <pick_p <I, P> >;
template <size_t I, typename P> using c_pick_p = c_ref <pick_p <I, P> >;

template <size_t I, typename... E> using r_pick = r_ref <pick <I, E...> >;
template <size_t I, typename... E> using l_pick = l_ref <pick <I, E...> >;
template <size_t I, typename... E> using c_pick = c_ref <pick <I, E...> >;

//-----------------------------------------------------------------------------

template <typename S, typename D> struct tx_type_t : id_t <D> { };
template <typename S, typename D> using  tx_type = type_of <tx_type_t <S, D> >;

template <typename S, typename D>
struct tx_type_t <S&&, D> : r_type_t <D> { };

template <typename S, typename D>
struct tx_type_t <S&, D> : l_type_t <D> { };

template <typename S, typename D>
struct tx_type_t <const S&, D> : c_type_t <D> { };

//-----------------------------------------------------------------------------

template <typename S, typename D> struct tx_ref_t : r_ref_t <D> { };
template <typename S, typename D> using  tx_ref = type_of <tx_ref_t <S, D> >;

template <typename S, typename D>
struct tx_ref_t <S&&, D> : r_ref_t <D> { };

template <typename S, typename D>
struct tx_ref_t <S&, D> : l_ref_t <D> { };

template <typename S, typename D>
struct tx_ref_t <const S&, D> : c_ref_t <D> { };

//-----------------------------------------------------------------------------

template <typename S, typename D>
using tx_types_t = type_map_t <bind <tx_type_t, S>::template map, D>;

template <typename S, typename D>
using tx_refs_t = type_map_t <bind <tx_ref_t, S>::template map, D>;

template <typename S, typename D>
using tx_types = type_of <tx_types_t <S, D> >;

template <typename S, typename D>
using tx_refs  = type_of <tx_refs_t <S, D> >;

//-----------------------------------------------------------------------------

template <
	template <typename...> class R,
	template <typename...> class L,
	template <typename...> class C
>
struct ref_switch
{
	template <typename T> struct map_t : id_t <R <T> > { };
	template <typename T> using  map   = type_of <map_t <T> >;

	template <typename T> struct map_t <T&&>      : id_t <R <T> > { };
	template <typename T> struct map_t <T&>       : id_t <L <T> > { };
	template <typename T> struct map_t <const T&> : id_t <C <T> > { };
};

template <typename R, typename L, typename C>
using t_ref_switch =
	ref_switch <R::template map, L::template map, C::template map>;

template <typename S, typename T>
using switch_ref = typename S::template map <T>;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_TRAITS_REF_HPP
