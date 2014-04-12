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

#ifndef IVL_CORE_ARRAY_TYPE_TRAITS_HPP
#define IVL_CORE_ARRAY_TYPE_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct is_seq_   : _false { };
template <typename T> struct is_cont_  : is_seq_<T> { };
template <typename T> struct is_trav_  : _false { };
template <typename T> struct is_iter_  : is_trav_<T> { };
template <typename T> struct is_delta_ : _false { };
template <typename T> struct is_range_ : _false { };
template <typename T> struct is_urange_ : _false { };

// extending definition @tuple/type/traits
template <typename C, typename... A>
struct is_group_<sequence <C, A...> > : _true { };

template <typename C, typename... A>
struct is_seq_<sequence <C, A...> > : _true { };

template <typename C, typename... A>
struct is_trav_<traversor <C, A...> > : _true { };

template <typename C, typename... A>
struct is_iter_<iterator <C, A...> > : _true { };

template <typename T>
struct is_iter_<T*> : _true { };

template <typename T, size_t N>
struct is_cont_<T[N]> : _true { };

template <typename T>
struct is_cont_<initializer_list <T> > : _true { };

template <typename F, typename... A>
struct is_delta_<delta <F, A...> > : _true { };

template <>
struct is_delta_<uscore> : _true { };

template <typename B, typename U, typename... E>
struct is_range_<range_seq <B, U, E...> > : _true { };

template <typename B, typename U>
struct is_urange_<range_seq <B, U> > : _true { };

}  // namespace details

//-----------------------------------------------------------------------------

template <typename T> using is_cont   = details::is_cont_<raw_type <T> >;
template <typename T> using is_seq    = details::is_seq_<raw_type <T> >;
template <typename T> using is_iter   = details::is_iter_<raw_type <T> >;
template <typename T> using is_trav   = details::is_trav_<raw_type <T> >;
template <typename T> using is_delta  = details::is_delta_<raw_type <T> >;
template <typename T> using is_range  = details::is_range_<raw_type <T> >;
template <typename T> using is_urange = details::is_urange_<raw_type <T> >;

//-----------------------------------------------------------------------------

template <typename P> using all_seq_p = all_p <is_seq, P>;
template <typename P> using any_seq_p = any_p <is_seq, P>;

template <typename... E> using all_seq = all_seq_p <pack <E...> >;
template <typename... E> using any_seq = any_seq_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <bool F, typename S>
struct fixed_order_t : none { };

template <bool F, typename S>
using fixed_order = type_of <fixed_order_t <F, S> >;

template <size_t... N>
struct fixed_order_t <true, sizes <N...> > : sizes <N...> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct is_finite_ : expr <T::finite> { };

template <typename T, bool = is_seq_<T>{}>  struct seq_finite_  : _false { };
template <typename T, bool = is_trav <T>{}> struct trav_finite_ : _false { };

template <typename T> struct seq_finite_<T, true>  : is_finite_<T> { };
template <typename T> struct trav_finite_<T, true> : is_finite_<T> { };

template <typename T, bool = seq_finite_<T>{}>
struct seq_order_ : none { };

template <typename T>
struct seq_order_<T, true> : id_t <typename T::order_type> { };

}  // namespace details

template <typename T> using is_finite   = details::is_finite_<raw_type <T> >;
template <typename T> using seq_finite  = details::seq_finite_<raw_type <T> >;
template <typename T> using trav_finite = details::trav_finite_<raw_type <T> >;
template <typename T> using cont_finite = expr <is_cont <T>() || seq_finite <T>()>;

template <typename T> using seq_order_t = details::seq_order_<raw_type <T> >;
template <typename T> using seq_order   = type_of <seq_order_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T, typename = seq_order <T> >
struct seq_fixed_ : _false { };

template <typename T, size_t... N>
struct seq_fixed_<T, sizes <N...> > : _true { };

template <typename T, bool = seq_fixed_<T>{}>
struct seq_len_ : size <> { };

template <typename T>
struct seq_len_<T, true> : int_prod <seq_order <T> > { };

}  // namespace details

template <typename T> using seq_fixed = details::seq_fixed_<raw_type <T> >;
template <typename T> using seq_len   = details::seq_len_<raw_type <T> >;

//-----------------------------------------------------------------------------

template <typename... T> using seq_prim = first_b <is_finite <T>{}...>;

template <typename M, typename... A>
using term_pick = pick <typename M::template map <A...>{}, A...>;

template <typename M, typename... A>
using term_get = typename M::template get <A...>;

//-----------------------------------------------------------------------------

template <typename... T> using cont_travers = _or <cont_finite <T>...>;
template <typename... T> using seq_travers  = _or <seq_finite <T>...>;

template <typename... T>
using iter_travers = expr <_and <is_iter <T>...>() && _or <trav_finite <T>...>()>;

template <typename... T>
using trav_travers = expr <_and <is_trav <T>...>() && _or <trav_finite <T>...>()>;

template <typename... T>
using raw_travers = expr <cont_travers <T...>() || iter_travers <T...>()>;

template <typename... T>
using travers = expr <seq_travers <T...>() || trav_travers <T...>()>;

//-----------------------------------------------------------------------------

template <typename T> using begin_of = decltype(begin(gen <T>()));
template <typename T> using end_of   = decltype(end(gen <T>()));

template <typename T> using has_begin = sfinae <begin_of, T>;
template <typename T> using has_end   = sfinae <end_of, T>;

template <typename T>
using has_range = expr <has_begin <T>() && has_end <T>()>;

//-----------------------------------------------------------------------------

namespace details {

template <typename I> struct seq_iter_ : id_t <typename I::iterator_type> { };
template <typename I> struct seq_iref_ : id_t <typename I::reference> { };
template <typename I> struct seq_val_  : id_t <typename I::value_type> { };
template <typename I> struct seq_size_ : id_t <typename I::size_type> { };
template <typename I> struct seq_diff_ : id_t <typename I::difference_type> { };
template <typename I> struct seq_iptr_ : id_t <typename I::pointer> { };

template <typename T> struct seq_iter_<T*> : id_t <T*> { };
template <typename T> struct seq_iref_<T*> : id_t <T&> { };
template <typename T> struct seq_val_<T*>  : id_t <T> { };
template <typename T> struct seq_size_<T*> : id_t <size_t> { };
template <typename T> struct seq_diff_<T*> : id_t <ptrdiff_t> { };
template <typename T> struct seq_iptr_<T*> : id_t <T*> { };

}  // namespace details

//-----------------------------------------------------------------------------

template <typename I> struct seq_iter_t : details::seq_iter_<raw_type <I> > { };
template <typename I> struct seq_iref_t : details::seq_iref_<raw_type <I> > { };
template <typename I> struct seq_val_t  : details::seq_val_ <raw_type <I> > { };
template <typename I> struct seq_size_t : details::seq_size_<raw_type <I> > { };
template <typename I> struct seq_diff_t : details::seq_diff_<raw_type <I> > { };
template <typename I> struct seq_iptr_t : details::seq_iptr_<raw_type <I> > { };

template <typename I> using seq_iter = type_of <seq_iter_t <I> >;
// template <typename I> using seq_iref = type_of <seq_iref_t <I> >;  // defined @begin
// template <typename I> using seq_val  = type_of <seq_val_t <I> >;   // defined @begin
template <typename I> using seq_size = type_of <seq_size_t <I> >;
template <typename I> using seq_diff = type_of <seq_diff_t <I> >;
template <typename I> using seq_iptr = type_of <seq_iptr_t <I> >;

//-----------------------------------------------------------------------------

template <typename... I>
struct seq_size_t <pack <I...> > : common_t <seq_size <I>...> { };

template <typename... I>
struct seq_diff_t <pack <I...> > : common_t <seq_diff <I>...> { };

//-----------------------------------------------------------------------------

// extending definition @type/traits/ref
template <typename C, typename T>
struct type_t <C, id_t <T> > : id_t <id_t <T> > { };

template <typename C, typename... T>
struct type_t <C, _type <T...> > : _type <type <C, T>...> { };

template <typename C, typename F, typename T>
struct type_t <C, F(_type <T>)> : id_t <type <C, F>(_type <type <C, T> >)> { };

//-----------------------------------------------------------------------------

// extending definition @type/traits/ref
template <typename C, typename T>
struct ref_t <C, id_t <T> > : id_t <T> { };

template <typename C, typename... T>
struct ref_t <C, _type <T...> > : common_t <ref <C, T>...> { };

template <typename C, typename F, typename T>
struct ref_t <C, F(_type <T>)> : bra_ret_t <ref <C, F>(ref <C, T>)> { };

//-----------------------------------------------------------------------------

template <typename T> using seq_type_t = tx_type_t <T, seq_val <T> >;
template <typename T> using seq_type   = type_of <seq_type_t <T> >;

template <typename T> using seq_ref_t = tx_ref_t <T, seq_val <T> >;
template <typename T> using seq_ref   = type_of <seq_ref_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename A, typename T, bool = is_seq <A>()>
struct seq_conv_ : is_conv <seq_ref <A>, T> { };

template <typename T, typename A, bool = is_seq <A>()>
struct seq_cons_ : is_cons <T, seq_ref <A> > { };

template <typename T, typename A, bool = is_seq <A>()>
struct seq_assign_ : is_assign <T, seq_ref <A> > { };

template <typename... A, typename T>
struct seq_conv_<pack <A...>, T, false> : _and <is_conv <A, T>...> { };

template <typename T, typename... A>
struct seq_cons_<T, pack <A...>, false> : _and <is_cons <T, A>...> { };

template <typename A, typename T> struct seq_conv_ <A, T, false> : _false { };
template <typename T, typename A> struct seq_cons_ <T, A, false> : _false { };
template <typename T, typename A> struct seq_assign_<T, A, false> : _false { };

}  // namespace details

//-----------------------------------------------------------------------------

template <typename T, typename A> using seq_cons = details::seq_cons_<T, A>;
template <typename A, typename T> using seq_conv = details::seq_conv_<A, T>;

template <typename T, typename A>
using seq_explicit = expr <seq_cons <T, A>() && !seq_conv <A, T>()>;

template <typename A, typename T>
using seq_seq_conv = expr <seq_conv <A, T>() && !is_conv <A, T>()>;

template <typename T, typename A>
using seq_seq_explicit = expr <seq_explicit <T, A>() && !is_explicit <T, A>()>;

//-----------------------------------------------------------------------------

template <typename T, typename A>
using seq_assign = details::seq_assign_<T, A>;

template <typename T, typename A, bool = seq_assign <T, A>()>
struct seq_atom_assign : is_assign <T, A> { };

template <typename T, typename A>
struct seq_atom_assign <T, A, true> : _false { };

//-----------------------------------------------------------------------------

namespace details {

template <typename A> using r_seq_ref_ = id_t <typename A::r_reference>;
template <typename A> using l_seq_ref_ = id_t <typename A::l_reference>;
template <typename A> using c_seq_ref_ = id_t <typename A::c_reference>;

template <typename A> using l_seq_ptr_ = id_t <typename A::l_pointer>;
template <typename A> using c_seq_ptr_ = id_t <typename A::c_pointer>;

}  // namespace details

template <typename T> using r_seq_ref_t = details::r_seq_ref_<raw_type <T> >;
template <typename T> using l_seq_ref_t = details::l_seq_ref_<raw_type <T> >;
template <typename T> using c_seq_ref_t = details::c_seq_ref_<raw_type <T> >;

template <typename T> using l_seq_ptr_t = details::l_seq_ptr_<raw_type <T> >;
template <typename T> using c_seq_ptr_t = details::c_seq_ptr_<raw_type <T> >;

template <typename T> using r_seq_ref = type_of <r_seq_ref_t <T> >;
template <typename T> using l_seq_ref = type_of <l_seq_ref_t <T> >;
template <typename T> using c_seq_ref = type_of <c_seq_ref_t <T> >;

template <typename T> using l_seq_ptr = type_of <l_seq_ptr_t <T> >;
template <typename T> using c_seq_ptr = type_of <c_seq_ptr_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename A> using r_seq_iter_ = id_t <typename A::r_iterator>;
template <typename A> using l_seq_iter_ = id_t <typename A::l_iterator>;
template <typename A> using c_seq_iter_ = id_t <typename A::c_iterator>;

template <typename Q, typename A>
using r_seq_trav_ = id_t <typename A::template r_traversor <Q> > ;

template <typename Q, typename A>
using l_seq_trav_ = id_t <typename A::template l_traversor <Q> > ;

template <typename Q, typename A>
using c_seq_trav_ = id_t <typename A::template c_traversor <Q> > ;

}  // namespace details

template <typename T> using r_seq_iter_t = details::r_seq_iter_<raw_type <T> >;
template <typename T> using l_seq_iter_t = details::l_seq_iter_<raw_type <T> >;
template <typename T> using c_seq_iter_t = details::c_seq_iter_<raw_type <T> >;

template <typename T> using r_seq_iter = type_of <r_seq_iter_t <T> >;
template <typename T> using l_seq_iter = type_of <l_seq_iter_t <T> >;
template <typename T> using c_seq_iter = type_of <c_seq_iter_t <T> >;

template <typename T, typename Q = arrays::path>
using r_seq_trav_t = details::r_seq_trav_<Q, raw_type <T> >;

template <typename T, typename Q = arrays::path>
using l_seq_trav_t = details::l_seq_trav_<Q, raw_type <T> >;

template <typename T, typename Q = arrays::path>
using c_seq_trav_t = details::c_seq_trav_<Q, raw_type <T> >;

template <typename T, typename Q = arrays::path>
using r_seq_trav = type_of <r_seq_trav_t <T, Q> >;

template <typename T, typename Q = arrays::path>
using l_seq_trav = type_of <l_seq_trav_t <T, Q> >;

template <typename T, typename Q = arrays::path>
using c_seq_trav = type_of <c_seq_trav_t <T, Q> >;

//-----------------------------------------------------------------------------

template <typename C, typename T, typename... Q> struct iter_t;
template <typename C, typename T, typename Q>    struct trav_t;

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename A> struct r_iter_ : r_seq_iter_<A> { };
template <typename A> struct l_iter_ : l_seq_iter_<A> { };
template <typename A> struct c_iter_ : c_seq_iter_<A> { };

template <typename Q, typename A> struct r_trav_ : r_seq_trav_<Q, A> { };
template <typename Q, typename A> struct l_trav_ : l_seq_trav_<Q, A> { };
template <typename Q, typename A> struct c_trav_ : c_seq_trav_<Q, A> { };

//-----------------------------------------------------------------------------

template <typename T> struct r_iter_<T*> : id_t <T*> { };
template <typename T> struct l_iter_<T*> : id_t <T*> { };
template <typename T> struct c_iter_<T*> : id_t <const T*> { };

template <typename Q, typename T> struct r_trav_<Q, T*> : id_t <T*> { };
template <typename Q, typename T> struct l_trav_<Q, T*> : id_t <T*> { };
template <typename Q, typename T> struct c_trav_<Q, T*> : id_t <const T*> { };

//-----------------------------------------------------------------------------

using iter_sw = ref_switch <r_iter_, l_iter_, c_iter_>;

template <typename Q>
using trav_sw = t_ref_switch <
	bind <r_trav_, Q>,
	bind <l_trav_, Q>,
	bind <c_trav_, Q>
>;

//-----------------------------------------------------------------------------

template <typename C, typename T, typename Q, bool I = path_edge <Q>()>
struct iter_trav_ : iter_t <C, T> { };

template <typename C, typename T, typename Q>
struct iter_trav_<C, T, Q, true> : trav_t <C, T, Q> { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename C, typename T, typename Q>
struct iter_t <C, T, Q> : details::iter_trav_<C, T, Q> { };

template <typename C, typename T>
struct iter_t <C, T> : switch_ref <details::iter_sw, add_ref <C, T> > { };

template <typename C, typename T, typename Q>
struct trav_t : switch_ref <details::trav_sw <Q>, add_ref <C, T> > { };

template <typename C, typename T, typename... Q>
using iter = type_of <iter_t <C, T, Q...> >;

template <typename C, typename T, typename Q>
using trav = type_of <trav_t <C, T, Q> >;

template <typename C, typename T>
struct iter_t <C, _type <T> > : _type <T> { };

template <typename C, typename T, typename Q>
struct trav_t <C, _type <T>, Q> : _type <T> { };

template <typename C, typename... A>
struct iter_t <C, pack <A...> > : pack <iter <C, id_t <A> >...> { };

template <typename C, typename... A, typename Q>
struct trav_t <C, pack <A...>, Q> : pack <trav <C, id_t <A>, Q>...> { };

template <typename C, typename T>
struct iter_t <C, id_t <T> > :
	switch_ref <details::iter_sw, ref <C, T> > { };

template <typename C, typename T, typename Q>
struct trav_t <C, id_t <T>, Q> :
	switch_ref <details::trav_sw <Q>, ref <C, T> > { };

//-----------------------------------------------------------------------------

template <typename T, typename... Q>
using r_iter_t = iter_t <tag::rref, T, Q...>;

template <typename T, typename... Q>
using l_iter_t = iter_t <tag::lref, T, Q...>;

template <typename T, typename... Q>
using c_iter_t = iter_t <tag::cref, T, Q...>;

template <typename T, typename... Q>
using r_iter = type_of <r_iter_t <T, Q...> >;

template <typename T, typename... Q>
using l_iter = type_of <l_iter_t <T, Q...> >;

template <typename T, typename... Q>
using c_iter = type_of <c_iter_t <T, Q...> >;

//-----------------------------------------------------------------------------

template <typename T, typename Q = arrays::path>
using r_trav_t = trav_t <tag::rref, T, Q>;

template <typename T, typename Q = arrays::path>
using l_trav_t = trav_t <tag::lref, T, Q>;

template <typename T, typename Q = arrays::path>
using c_trav_t = trav_t <tag::cref, T, Q>;

template <typename T, typename Q = arrays::path>
using r_trav = type_of <r_trav_t <T, Q> >;

template <typename T, typename Q = arrays::path>
using l_trav = type_of <l_trav_t <T, Q> >;

template <typename T, typename Q = arrays::path>
using c_trav = type_of <c_trav_t <T, Q> >;

//-----------------------------------------------------------------------------

template <typename T, bool = is_iter <T>()>
struct iter_opt_ : base_opt_t <T> { };

template <typename T>
struct iter_opt_<T, false> : rref_opt_t <T> { };

template <typename T>
struct iter_opt_<_type <T>, false> : base_opt_t <T> { };

template <typename T> using iter_opt_t = iter_opt_<T>;
template <typename T> using iter_opt = type_of <iter_opt_t <T> >;

//-----------------------------------------------------------------------------

template <size_t N, typename T>
using iter_elem = tuples::elem <N, iter_opt <T> >;

template <size_t N, typename... E>
using iter_elem_at = iter_elem <N, pick <N, E...> >;

template <typename T> using r_iter_ref = r_ref <iter_opt <T> >;
template <typename T> using l_iter_ref = l_ref <iter_opt <T> >;
template <typename T> using c_iter_ref = c_ref <iter_opt <T> >;

template <size_t N, typename... E>
using r_iter_pick = r_iter_ref <pick <N, E...> >;

template <size_t N, typename... E>
using l_iter_pick = l_iter_ref <pick <N, E...> >;

template <size_t N, typename... E>
using c_iter_pick = c_iter_ref <pick <N, E...> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename S> struct seq_ret_;

template <typename F, typename... A>
struct seq_ret_<F(pack <A...>)> : ret_t <F(A...)> { };

}  // namespace details

template <typename... T>
using seq_args = pack <seq_ref <seq_atom_of <T> >...>;

template <typename F, typename... A>
struct seq_ret_t : seq_ret_t <F(A...)> { };

template <typename F, typename... A>
struct seq_ret_t <F(A...)> : details::seq_ret_<F(seq_args <A...>)> { };

template <typename F, typename... A>
using seq_ret = type_of <seq_ret_t <F, A...> >;

template <typename F, typename... A>
struct seq_void : is_void <seq_ret <F, A...> > { };

//-----------------------------------------------------------------------------

template <typename U, typename... A>
using make_seq_of = arrays::pre_fixed_array <U, sizeof...(A)>;

template <typename... A>
using make_seq = make_seq_of <common_or <int, A...>, A...>;

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, bool F, size_t N>
struct new_seq_ : id_t <fixed_array <T, N> > { };

template <typename T, size_t N>
struct new_seq_ <T, false, N> : id_t <heap_array <T> > { };

template <typename T, typename... A>
struct new_seq :
	new_seq_<T, all <seq_fixed, A...>{}, sz_min <seq_len <A>{}...>{}> { };

//-----------------------------------------------------------------------------

template <typename A>
using seq_flat = new_seq <flat <seq_ref <A> >, A>;

// extending definition @tuple/type/traits
template <typename C, typename... A>
struct flat_rec <sequence <C, A...> > : seq_flat <sequence <C, A...> > { };

//-----------------------------------------------------------------------------

template <typename A>
using seq_copy = new_seq <copy <seq_ref <A> >, A>;

// extending definition @type/traits/transform
template <typename C, typename... A>
struct copy_rec <sequence <C, A...> > : seq_copy <sequence <C, A...> > { };

//-----------------------------------------------------------------------------

template <typename A, typename B>
using seq_common = new_seq <common2 <seq_ref <A>, seq_ref <B> >, A, B>;

// extending definition @type/traits/relation
template <typename CA, typename... A, typename CB, typename... B>
struct common_rec <sequence <CA, A...>, sequence <CB, B...> > :
	seq_common <flat <sequence <CA, A...> >, flat <sequence <CB, B...> > > { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILC_CORE_ARRAY_TYPE_TRAITS_HPP
