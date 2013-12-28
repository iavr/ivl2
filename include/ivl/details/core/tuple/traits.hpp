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

template <typename T> struct is_tuple_ : public _false { };
template <typename T> struct as_tuple_ : public _false { };

template <typename S, typename... E>
struct is_tuple_<collection <S, E...> > : public _true { };

// extended elsewhere
template <typename S, typename... E>
struct as_tuple_<collection <S, E...> > : public _true { };

}  // namespace details

template <typename T> using is_tuple = details::is_tuple_<raw_type <T> >;
template <typename T> using as_tuple = details::as_tuple_<raw_type <T> >;

template <typename T>
using is_tup_type = expr <is_pack <T>() || as_tuple <T>()>;

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
using tup_tx_t = base_opt_t <tx_lref <S, tx_cv <remove_ref <S>, D> > >;

template <typename S, typename D> using tup_tx = type_of <tup_tx_t <S, D> >;

template <typename T>
using raw_types = type_of <raw_type <T> >;

template <typename T>
struct tup_types_t :
	public apply_t <bind <tup_tx_t, T>::template map, raw_types <T> > { };

template <typename... E>
struct tup_types_t <pack <E...> > : public pack <E...> { };

template <typename T> using tup_types = type_of <tup_types_t <T> >;

//-----------------------------------------------------------------------------

template <size_t I, typename T>
using tup_elem_t = tup_tx_t <T, pick_p <I, raw_types <T> > >;

template <size_t I, typename T>
using tup_elem = type_of <tup_elem_t <I, T> >;

//-----------------------------------------------------------------------------

template <typename T> struct rtref_t  { using type = base_opt <T&&>; };
template <typename T> struct ltref_t  { using type = base_opt <T&>; };
template <typename T> struct cltref_t { using type = base_opt <const T&>; };

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

template <
	template <typename...> class R, typename C, typename T,
	bool = all <is_tup_type, C, T>()
>
struct tup_rel : public alls <R, tup_types <C>, tup_types <T> > { };

template <template <typename...> class R, typename C, typename T>
struct tup_rel <R, C, T, false> : public _false { };

}  // namespace details

template <typename C, typename T>
using tup_cons = details::tup_rel <is_cons, C, T>;

template <typename T, typename C>
using tup_conv = details::tup_rel <is_conv, T, C>;

template <typename C, typename T>
using tup_explicit = details::tup_rel <is_explicit, C, T>;

template <typename C, typename T>
struct tup_assign : public details::tup_rel <is_assign, C, T> { };

template <typename... E, typename... P, typename T>
struct tup_assign <pack <pack <E...>, P...>, T> :
	public alls <tup_assign, pack <pack <E...>, P...>, tup_types <T> > { };

//-----------------------------------------------------------------------------

template <typename T, typename C>
using tup_tup_conv = expr <tup_conv <T, C>() && !tup_conv <pack <T>, C>()>;

template <typename C, typename T>
using tup_tup_explicit =
	expr <tup_explicit <C, T>() && !tup_explicit <C, pack <T> >()>;

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct apply_tuple_t { using type = apply_tup <F, atom_of <A>...>; };

template <typename F, typename... A>
struct loop_tuple_t { using type = loop_tup <F, atom_of <A>...>; };

template <typename... U>
struct zip_tuple_t { using type = zip_tup <atom_of <U>...>; };

template <typename... U>
struct join_tuple_t { using type = join_tup <atom_of <U>...>; };

template <typename... U> using apply_tuple = type_of <apply_tuple_t <U...> >;
template <typename... U> using loop_tuple  = type_of <loop_tuple_t <U...> >;
template <typename... U> using zip_tuple   = type_of <zip_tuple_t <U...> >;
template <typename... U> using join_tuple  = type_of <join_tuple_t <U...> >;

//-----------------------------------------------------------------------------

// TODO: redesign; only used for array construction now along with reuse <>
template <typename T>
using tuple_of_t = _if <is_tuple <T>{}, raw_type_t <T>, id_t <tuple <T> > >;

template <typename T> using tuple_of = type_of <tuple_of_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

// extending definition under type/traits
template <typename S, typename... A>
struct create_rec <collection <S, A...> > :
	public create_rec <type_of <collection <S, A...> > > { };

template <typename... E>
struct create_rec <pack <E...> > { using type = tuple <create <E>...>; };

template <typename F, typename... E>
struct create_rec <F(pack <E...>)>  { using type = create <ret <F(E...)> >; };

}  // namespace details

//-----------------------------------------------------------------------------

// extended elsewhere
template <typename T> struct under_t : public pack <> { };
template <typename T> using  under = type_of <under_t <T> >;

template <typename S, typename... A>
struct under_t <collection <S, A...> > : public pack <A...> { };

template <typename D, typename P>
struct under_t <base_tup <D, P> > : public under_t <D> { };

template <typename K, typename U>
struct under_t <indirect_tup <K, U> > : public pack <U> { };

//-----------------------------------------------------------------------------

template <size_t J, typename P>
using elem_at_p = tuple_details::elem <J, pick_p <J, P> >;

template <size_t J, typename... E>
using elem_at = elem_at_p <J, pack <E...> >;

template <size_t J, typename T>
using under_elem_at = elem_at_p <J, under <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename F>
class tup_applier
{
	template <typename... A>
	struct map_t { using type = F(pack <A...>); };

	template <typename... A>
	struct map_t <pack <A...> > : public map_t <A...> { };

public:
	template <typename... A>
	using map = type_of <map_t <A...> >;
};

}  // namespace details

template <typename F, typename... A>
using tup_apply_types =
	map <details::tup_applier <F>::template map, tran <tup_types <A>...> >;

//-----------------------------------------------------------------------------

template <typename... U>
struct zip_len :
	public sz_min_p <length_of, select <is_pack, tup_types <U>...> > { };

template <typename U>
struct zip_len <U> : public tup_len <U> { };

template <typename F, typename... A>
using tup_loop_types = rep <zip_len <A...>{}, bool>;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_TRAITS_HPP
