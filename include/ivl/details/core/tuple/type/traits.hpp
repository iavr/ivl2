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

#ifndef IVL_DETAILS_CORE_TUPLE_TYPE_TRAITS_HPP
#define IVL_DETAILS_CORE_TUPLE_TYPE_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct is_tuple_ : _false { };

template <typename S, typename... E>
struct is_tuple_<collection <S, E...> > : _true { };

}  // namespace details

template <typename T> using is_tuple = details::is_tuple_<raw_type <T> >;

template <typename T>
using is_tup_type = expr <is_pack <T>() || is_tuple <T>()>;

//-----------------------------------------------------------------------------

template <typename P> using all_tuple_p = all_p <is_tuple, P>;
template <typename P> using any_tuple_p = any_p <is_tuple, P>;

template <typename... E> using all_tuple = all_tuple_p <pack <E...> >;
template <typename... E> using any_tuple = any_tuple_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <typename P> using all_rref_p  = all_p <is_rref, P>;
template <typename P> using all_lref_p  = all_p <is_lref, P>;
template <typename P> using all_clref_p = all_p <is_clref, P>;

template <typename... E> using all_rref  = all_rref_p <pack <E...> >;
template <typename... E> using all_lref  = all_lref_p <pack <E...> >;
template <typename... E> using all_clref = all_clref_p <pack <E...> >;

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
using tup_tx_t = base_opt_t <tx_lref <S, tx_cv <remove_ref <S>, D> >, D>;

template <typename S, typename D> using tup_tx = type_of <tup_tx_t <S, D> >;

template <typename T> using raw_types = type_of <raw_type <T> >;

template <typename T>
struct tup_types_t :
	type_map_t <bind <tup_tx_t, T>::template map, raw_types <T> > { };

template <typename... E> struct tup_types_t <pack <E...> > : pack <E...> { };
template <typename T>    struct tup_types_t <_type <T> >   : _type <T> { };
template <typename T>    using  tup_types = type_of <tup_types_t <T> >;

//-----------------------------------------------------------------------------

template <size_t I, typename T>
using tup_elem_t = tup_tx_t <T, pick_p <I, raw_types <T> > >;

template <size_t I, typename T>
using tup_elem = type_of <tup_elem_t <I, T> >;

//-----------------------------------------------------------------------------

template <typename T> struct rtref_t  : base_opt_t <T&&, T> { };
template <typename T> struct ltref_t  : base_opt_t <T&, T> { };
template <typename T> struct cltref_t : base_opt_t <const T&, T> { };

template <typename T> using rtref  = type_of <rtref_t <T> >;
template <typename T> using ltref  = type_of <ltref_t <T> >;
template <typename T> using cltref = type_of <cltref_t <T> >;

template <typename... E>
struct rtref_t <pack <E...> > { using type = pre_tuple <rtref <E>...>; };

template <typename... E>
struct ltref_t <pack <E...> > { using type = pre_tuple <ltref <E>...>; };

template <typename... E>
struct cltref_t <pack <E...> > { using type = pre_tuple <cltref <E>...>; };

template <typename F, typename... E>
struct rtref_t <F(pack <E...>)> : ret_t <rtref <F>(rtref <E>...)> { };

template <typename F, typename... E>
struct ltref_t <F(pack <E...>)> : ret_t <ltref <F>(ltref <E>...)> { };

template <typename F, typename... E>
struct cltref_t <F(pack <E...>)> : ret_t <cltref <F>(cltref <E>...)> { };

//-----------------------------------------------------------------------------

template <size_t I, typename P> using rtel_t  = rtref_t <pick_p <I, P> >;
template <size_t I, typename P> using ltel_t  = ltref_t <pick_p <I, P> >;
template <size_t I, typename P> using cltel_t = cltref_t <pick_p <I, P> >;

template <size_t I, typename P> using rtel  = type_of <rtel_t <I, P> >;
template <size_t I, typename P> using ltel  = type_of <ltel_t <I, P> >;
template <size_t I, typename P> using cltel = type_of <cltel_t <I, P> >;

//-----------------------------------------------------------------------------

template <typename T> struct tref_t            : rtref_t <T> { };
template <typename T> struct tref_t <T&>       : ltref_t <T> { };
template <typename T> struct tref_t <const T&> : cltref_t <T> { };
template <typename T> using  tref              = type_of <tref_t <T> >;

template <typename T>
struct tref_types_t : type_map_t <tref_t, tup_types <T> > { };

template <typename T> using tref_types = type_of <tref_types_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename P, typename T, bool = is_tup_type <T>()>
struct tup_cons_ : all2 <is_cons, P, tref_types <T> > { };

template <typename T, typename P, bool = is_tup_type <T>()>
struct tup_conv_ : all2 <is_conv, tref_types <T>, P> { };

template <typename P, typename T, bool = is_tup_type <T>()>
struct tup_assign_ : all2 <is_assign, tref_types <P>, tref_types <T> > { };

template <typename P, typename T> struct tup_cons_<P, T, false>   : _false { };
template <typename T, typename P> struct tup_conv_<T, P, false>   : _false { };
template <typename P, typename T> struct tup_assign_<P, T, false> : _false { };

}  // namespace details

//-----------------------------------------------------------------------------

template <typename C, typename T> using tup_cons = details::tup_cons_<C, T>;
template <typename T, typename C> using tup_conv = details::tup_conv_<T, C>;

template <typename C, typename T>
using tup_explicit = expr <tup_cons <C, T>() && !tup_conv <T, C>()>;

template <typename T, typename C>
using tup_tup_conv = expr <tup_conv <T, C>() && !tup_conv <pack <T>, C>()>;

template <typename C, typename T>
using tup_tup_explicit =
	expr <tup_explicit <C, T>() && !tup_explicit <C, pack <T> >()>;

//-----------------------------------------------------------------------------

template <typename C, typename T>
using tup_assign = details::tup_assign_<C, T>;

template <typename C, typename T, bool = tup_assign <C, T>()>
struct tup_atom_assign : tup_assign <C, rep <length_of <C>{}, T> > { };

template <typename C, typename T>
struct tup_atom_assign <C, T, true> : _false { };

//-----------------------------------------------------------------------------

namespace details {

// defined @atom/traits
template <typename P, bool = any_type_p <P>{}> struct tup_tmp_type { };
template <typename P, bool = any_pack_p <P>{}> struct tup_tmp_pack;

template <template <typename...> class C, typename... E>
struct tup_tmp_pack <C <E...>, true> :
	embed_t <raw_tuple, tran_p <tmp <_type_of <E>...> > > { };

template <template <typename...> class C, typename... E>
struct tup_tmp_pack <C <E...>, false> : tup_tmp_type <C <E...> > { };

}  // namespace details

template <typename P> using tup_tmp_pt = details::tup_tmp_pack <P>;
template <typename P> using tup_tmp_p  = type_of <tup_tmp_pt <P> >;

template <typename... E> using tup_tmp_t = tup_tmp_pt <pack <E...> >;
template <typename... E> using tup_tmp   = type_of <tup_tmp_t <E...> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename P, size_t = length <P>()>
struct tup_tran_ : tran_pt <P> { };

template <typename P> struct tup_tran_<P, 1> : car_t <P> { };

}  // namespace details

template <typename P> using tup_tran_pt = details::tup_tran_<P>;
template <typename P> using tup_tran_p  = type_of <tup_tran_pt <P> >;

template <typename... P> using tup_tran_t = tup_tran_pt <pack <P...> >;
template <typename... P> using tup_tran   = type_of <tup_tran_t <P...> >;

//-----------------------------------------------------------------------------

template <typename T> struct tup_arg_t : tup_types <atom_of <T> > { };
template <typename T> using  tup_arg = type_of <tup_arg_t <T> >;

template <typename... T> struct tup_args_t;
template <typename... T> using  tup_args = type_of <tup_args_t <T...> >;

template <typename... T>
struct tup_args_t { using type = tup_tran <tup_arg <T>...>; };

template <typename T> struct tup_args_t <T> : tup_types_t <T> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename S> struct tup_ret_pt;
template <typename S> struct tup_ret_et;
template <typename S> using  tup_ret_e = type_of <tup_ret_et <S> >;

template <typename F, typename... T>
struct tup_ret_et <F(pack <T...>)> : ret_t <F(T...)> { };

template <typename F, typename... T>
struct tup_ret_pt <F(pack <T...>)> : pack <tup_ret_e <F(T)>...> { };

}  // namespace details

template <typename F, typename... T>
struct tup_ret_t : tup_ret_t <F(T...)> { };

template <typename F, typename... T>
struct tup_ret_t <F(T...)> : details::tup_ret_pt <F(tup_args <T...>)> { };

template <typename F, typename... T>
using tup_ret = type_of <tup_ret_t <F, T...> >;

template <typename F, typename... T>
struct tup_void : any_p <is_void, tup_ret <F, T...> > { };

//-----------------------------------------------------------------------------

// TODO: redesign; only used for array construction now along with reuse <>
template <typename T>
using tuple_of_t = _if <is_tuple <T>{}, raw_type_t <T>, id_t <tuple <T> > >;

template <typename T> using tuple_of = type_of <tuple_of_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

// extending definition @type/traits/transform
template <typename S, typename... A>
struct create_rec <collection <S, A...> > :
	create_rec <type_of <collection <S, A...> > > { };

template <typename... E>
struct create_rec <pack <E...> > { using type = tuple <create <E>...>; };

template <typename F, typename... E>
struct create_rec <F(pack <E...>)>  { using type = create <ret <F(E...)> >; };

}  // namespace details

//-----------------------------------------------------------------------------

// extended elsewhere
template <typename T> struct under_t : pack <> { };
template <typename T> using  under = type_of <under_t <T> >;

template <typename S, typename... A>
struct under_t <tuples::collection <S, A...> > : pack <A...> { };

template <typename K, typename U>
struct under_t <tuples::indirect_tup <K, U> > : pack <U> { };

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_TYPE_TRAITS_HPP
