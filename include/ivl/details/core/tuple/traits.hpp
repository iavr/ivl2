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

#ifndef IVL_DETAILS_CORE_TUPLE_TRAITS_HPP
#define IVL_DETAILS_CORE_TUPLE_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

template <typename T>
struct is_tuple_ : public _false { };

template <typename S, typename... E>
struct is_tuple_<collection <S, E...> > : public _true { };

}  // namespace details

template <typename T> using is_tuple = details::is_tuple_<raw_type <T> >;

template <typename T> struct as_tuple;

//-----------------------------------------------------------------------------

template <typename... A>
using all_tuple = all <is_tuple, A...>;

template <typename... A>
using any_tuple = any <is_tuple, A...>;

//-----------------------------------------------------------------------------

template <typename T> using tup_len = length_of <raw_type <T> >;

template <typename T>
using tup_empty = expr <is_tuple <T>() && !tup_len <T>()>;

template <typename T>
using tup_non_empty = expr <is_tuple <T>() && tup_len <T>()>;

template <typename T>
using as_tup_non_empty = expr <as_tuple <T>() && tup_len <T>()>;

//-----------------------------------------------------------------------------

template <typename S, typename D>
using tup_tx_t = tx_lref_t <S, tx_cv <remove_ref <S>, D> >;

template <typename S, typename D> using tup_tx = type_of <tup_tx_t <S, D> >;

template <typename T>
using raw_types = type_of <raw_type <T> >;

template <typename T>
struct tup_types_t :
	public apply_t <bind <tup_tx_t, T>::template map, raw_types <T> > { };

template <typename... E>
struct tup_types_t <pack <E...> > { using type = pack <E...>; };

template <typename T> using tup_types = type_of <tup_types_t <T> >;

//-----------------------------------------------------------------------------

template <size_t I, typename T>
using tup_elem_t = tup_tx_t <T, pick_p <I, raw_types <T> > >;

template <size_t I, typename T>
using tup_elem = type_of <tup_elem_t <I, T> >;

//-----------------------------------------------------------------------------

template <typename T> struct rtref_t  { using type = T&&; };
template <typename T> struct ltref_t  { using type = T&; };
template <typename T> struct cltref_t { using type = const T&; };

template <typename T> using rtref  = type_of <rtref_t <T> >;
template <typename T> using ltref  = type_of <ltref_t <T> >;
template <typename T> using cltref = type_of <cltref_t <T> >;

template <typename... E>
struct rtref_t <pack <E...> > { using type = tuple <rtref <E>...>; };

template <typename... E>
struct ltref_t <pack <E...> > { using type = tuple <ltref <E>...>; };

template <typename... E>
struct cltref_t <pack <E...> > { using type = tuple <cltref <E>...>; };

template <typename F, typename... E>
struct rtref_t <F(pack <E...>)>  { using type = ret <F(rtref <E>...)>; };

template <typename F, typename... E>
struct ltref_t <F(pack <E...>)>  { using type = ret <F(ltref <E>...)>; };

template <typename F, typename... E>
struct cltref_t <F(pack <E...>)> { using type = ret <F(cltref <E>...)>; };

//-----------------------------------------------------------------------------

template <size_t I, typename P> using rtel_t  = rtref_t <pick_p <I, P> >;
template <size_t I, typename P> using ltel_t  = ltref_t <pick_p <I, P> >;
template <size_t I, typename P> using cltel_t = cltref_t <pick_p <I, P> >;

template <size_t I, typename P> using rtel  = type_of <rtel_t <I, P> >;
template <size_t I, typename P> using ltel  = type_of <ltel_t <I, P> >;
template <size_t I, typename P> using cltel = type_of <cltel_t <I, P> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename C, typename T, bool = is_pack <T>() || is_tuple <T>()>
struct tup_cons_ : public alls <is_cons, tup_types <C>, tup_types <T> > { };

template <typename C, typename T>
struct tup_cons_<C, T, false> : public _false { };

template <typename T, typename C, bool = is_pack <T>() || is_tuple <T>()>
struct tup_conv_ : public alls <is_conv, tup_types <T>, tup_types <C> > { };

template <typename T, typename C>
struct tup_conv_<T, C, false> : public _false { };

template <typename C, typename T, bool = is_pack <T>() || is_tuple <T>()>
struct tup_assign_ : public alls <is_assign, tup_types <C>, tup_types <T> > { };

template <typename C, typename T>
struct tup_assign_<C, T, false> : public _false { };

}  // namespace details

template <typename C, typename T> using tup_cons = details::tup_cons_ <C, T>;
template <typename T, typename C> using tup_conv = details::tup_conv_ <T, C>;

template <typename C, typename T>
using tup_explicit = expr <tup_cons <C, T>() && !tup_conv <T, C>()>;

template <typename C, typename T>
struct tup_assign : public details::tup_assign_<C, T> { };

template <typename... E, typename... P, typename T>
struct tup_assign <pack <pack <E...>, P...>, T> :
	public alls <tup_assign, pack <pack <E...>, P...>, tup_types <T> > { };

//-----------------------------------------------------------------------------

template <typename T>
using tuple_of_t = _if <is_tuple <T>{}, raw_type_t <T>, id_t <tuple <T> > >;

template <typename T> using tuple_of = type_of <tuple_of_t <T> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

namespace tmeta {

template <typename F>
struct tup_app
{
	template <typename... E>
	using map = F(pack <E...>);
};

}  // namespace tmeta

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_TRAITS_HPP
