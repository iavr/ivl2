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

#ifndef IVL_CORE_TUPLE_TYPE_TRAITS_HPP
#define IVL_CORE_TUPLE_TYPE_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

// extended elsewhere
template <typename T> struct is_group_ : _false { };
template <typename T> struct is_tuple_ : _false { };

template <typename C, typename... A>
struct is_group_<collection <C, A...> > : _true { };

template <typename C, typename... A>
struct is_tuple_<collection <C, A...> > : _true { };

}  // namespace details

template <typename T> using is_group = details::is_group_<raw_type <T> >;
template <typename T> using is_tuple = details::is_tuple_<raw_type <T> >;

template <typename T>
using is_tup_type = expr <is_pack <T>() || is_tuple <T>()>;

//-----------------------------------------------------------------------------

template <typename T> using tup_len      = length_of <raw_type <T> >;
template <typename T> using tup_null     = expr <tup_len <T>() == 0>;
template <typename T> using tup_non_null = expr <tup_len <T>() != 0>;

template <typename T>
using tup_empty = expr <is_tuple <T>() && tup_null <T>()>;

template <typename T>
using tup_non_empty = expr <is_tuple <T>() && !tup_null <T>()>;

template <typename T>
using as_tup_non_empty = expr <as_tuple <T>() && !tup_null <T>()>;

//-----------------------------------------------------------------------------

template <typename P> using all_tuple_p = all_p <is_tuple, P>;
template <typename P> using any_tuple_p = any_p <is_tuple, P>;

template <typename... E> using all_tuple = all_tuple_p <pack <E...> >;
template <typename... E> using any_tuple = any_tuple_p <pack <E...> >;

template <typename P> using all_group_p = all_p <is_group, P>;
template <typename P> using any_group_p = any_p <is_group, P>;

template <typename... E> using all_group = all_group_p <pack <E...> >;
template <typename... E> using any_group = any_group_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <typename P> using all_rref_p = all_p <is_rref, P>;
template <typename P> using all_lref_p = all_p <is_lref, P>;
template <typename P> using all_cref_p = all_p <is_cref, P>;

template <typename... E> using all_rref = all_rref_p <pack <E...> >;
template <typename... E> using all_lref = all_lref_p <pack <E...> >;
template <typename... E> using all_cref = all_cref_p <pack <E...> >;

//-----------------------------------------------------------------------------

// extending definition @type/traits/ref
template <typename C, typename... E>
struct type_t <C, pack <E...> > : pack <type <C, E>...> { };

template <typename C, typename F, typename... E>
struct type_t <C, F(pack <E...>)> :
	id_t <type <C, F>(pack <type <C, E>...>)> { };

//-----------------------------------------------------------------------------

// extending definition @type/traits/ref
template <typename C, typename... E>
struct ref_t <C, pack <E...> > : id_t <pre_tuple <ref <C, E>...> > { };

template <typename C, typename F, typename... E>
struct ref_t <C, F(pack <E...>)> : ret_t <ref <C, F>(ref <C, E>...)> { };

//-----------------------------------------------------------------------------

template <typename T> using tup_val = type_of <raw_type <T> >;

template <typename T>
struct tup_type_t :
	type_map_t <bind <tx_type_t, T>::template map, tup_val <T> > { };

template <typename... E> struct tup_type_t <pack <E...> > : pack <E...> { };
template <typename T>    struct tup_type_t <_type <T> >   : _type <T> { };

template <typename T>
using tup_ref_t = type_map_t <bind <tx_ref_t, T>::template map, tup_val <T> >;

template <typename T> using tup_type = type_of <tup_type_t <T> >;
template <typename T> using tup_ref  = type_of <tup_ref_t <T> >;

//-----------------------------------------------------------------------------

template <size_t I, typename T>
using tup_elem_t = tx_type_t <T, pick_p <I, tup_val <T> > >;

template <size_t I, typename T>
using tup_elem = type_of <tup_elem_t <I, T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename P, typename T, bool = is_tup_type <T>()>
struct tup_cons_ : all2 <is_cons, P, tup_ref <T> > { };

template <typename T, typename P, bool = is_tup_type <T>()>
struct tup_conv_ : all2 <is_conv, tup_ref <T>, P> { };

template <typename P, typename T, bool = is_tup_type <T>()>
struct tup_assign_ : all2 <is_assign, tup_ref <P>, tup_ref <T> > { };

template <typename P, typename T> struct tup_cons_<P, T, false>   : _false { };
template <typename T, typename P> struct tup_conv_<T, P, false>   : _false { };
template <typename P, typename T> struct tup_assign_<P, T, false> : _false { };

template <typename P, typename T, typename R = tup_ref <P> >
struct tup_atom_assign_;

template <typename P, typename T, typename... E>
struct tup_atom_assign_<P, T, pack <E...> > : _and <is_assign <E, T>...> { };

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
struct tup_atom_assign : details::tup_atom_assign_<C, T> { };

template <typename C, typename T>
struct tup_atom_assign <C, T, true> : _false { };

template <typename T, size_t L> struct tup_op_ref_assign : is_op_ref <T> { };
template <typename T>           struct tup_op_ref_assign <T, 1>: _false { };

//-----------------------------------------------------------------------------

namespace details {

// TODO: define for sequences
template <typename T, bool = is_tuple <T>()>
struct common_of_ : id_t <T> { };

template <typename T>
struct common_of_<T, true> : id_t <common_or_p <int, tup_type <T> > > { };

}  // namespace details

template <typename T> using common_of_t = details::common_of_<raw_type <T> >;
template <typename T> using common_of = type_of <common_of_t <T> >;

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

template <typename... A>
using tup_tran_len = tran_len <tup_type <tup_atom_of <A> >...>;

template <typename... A>
using tup_tran_rng = sz_rng_of_i <tup_tran_len <A...>{}>;

//-----------------------------------------------------------------------------

template <typename T> struct tup_arg_t : tup_ref <tup_atom_of <T> > { };
template <typename T> using  tup_arg = type_of <tup_arg_t <T> >;

template <typename... T> struct tup_args_t;
template <typename... T> using  tup_args = type_of <tup_args_t <T...> >;

template <typename... T>
struct tup_args_t : id_t <tup_tran <tup_arg <T>...> > { };

template <typename T> struct tup_args_t <T> : tup_type_t <T> { };

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

namespace details {

// extending definition @type/traits/transform
template <typename C, typename... A>
struct copy_rec <collection <C, A...> > :
	copy_rec <tup_ref <collection <C, A...> > > { };

template <typename... E>
struct copy_rec <pack <E...> > : id_t <tuple <copy <E>...> > { };

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_TYPE_TRAITS_HPP
