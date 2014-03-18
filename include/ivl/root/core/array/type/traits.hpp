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

}  // namespace details

//-----------------------------------------------------------------------------

template <typename T> using is_cont  = details::is_cont_<raw_type <T> >;
template <typename T> using is_seq   = details::is_seq_<raw_type <T> >;
template <typename T> using is_iter  = details::is_iter_<raw_type <T> >;
template <typename T> using is_trav  = details::is_trav_<raw_type <T> >;

//-----------------------------------------------------------------------------

template <typename P> using all_seq_p = all_p <is_seq, P>;
template <typename P> using any_seq_p = any_p <is_seq, P>;

template <typename... E> using all_seq = all_seq_p <pack <E...> >;
template <typename... E> using any_seq = any_seq_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <typename T> struct fin_trav;

namespace details {

template <typename T, bool = is_seq <T>{}>  struct fix_seq_    : _false { };
template <typename T, bool = fix_seq_<T>{}> struct seq_len_    : size <> { };
template <typename T, bool = fix_seq_<T>{}> struct seq_length_ : no_size { };

template <typename T, bool = is_seq <T>{}>  struct fin_seq_  : _false { };
template <typename T, bool = is_trav <T>{}> struct fin_trav_ : _false { };

template <typename T> struct fix_seq_<T, true>    : expr <T::fixed> { };
template <typename T> struct seq_len_<T, true>    : size <T::length> { };
template <typename T> struct seq_length_<T, true> : T::length_type { };

template <typename T> struct fin_seq_<T, true>  : expr <T::finite> { };
template <typename T> struct fin_trav_<T, true> : expr <T::finite> { };

}  // namespace details

template <typename T> using fix_seq = details::fix_seq_<raw_type <T> >;
template <typename T> using seq_len = details::seq_len_<raw_type <T> >;

template <typename T> using seq_length_t = details::seq_length_<raw_type <T> >;
template <typename T> using seq_length   = type_of <seq_length_t <T> >;

template <typename T> using  fin_seq  = details::fin_seq_<raw_type <T> >;
template <typename T> struct fin_trav : details::fin_trav_<raw_type <T> > { };
template <typename T> using  fin_cont = expr <is_cont <T>() || fin_seq <T>()>;

template <typename... T> using prim_seq  = first_b <fin_seq <T>{}...>;
template <typename... T> using prim_trav = first_b <fin_trav <T>{}...>;

//-----------------------------------------------------------------------------

template <typename M, typename... A>
using term_seq = typename M::template seq <A...>;

template <typename M, typename... A>
using term_trav = typename M::template trav <A...>;

//-----------------------------------------------------------------------------

template <typename... T> using cont_travers = _or <fin_cont <T>...>;
template <typename... T> using seq_travers  = _or <fin_seq <T>...>;

template <typename... T>
using iter_travers = expr <_and <is_iter <T>...>() && _or <fin_trav <T>...>()>;

template <typename... T>
using trav_travers = expr <_and <is_trav <T>...>() && _or <fin_trav <T>...>()>;

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

template <typename T> struct seq_size_t <_type <T> > : id_t <size_t> { };
template <typename T> struct seq_diff_t <_type <T> > : id_t <ptrdiff_t> { };

template <typename... I>
struct seq_size_t <pack <I...> > : common_t <seq_size <I>...> { };

template <typename... I>
struct seq_diff_t <pack <I...> > : common_t <seq_diff <I>...> { };

//-----------------------------------------------------------------------------

// extending definition @type/traits/ref
template <typename C, typename... T>
struct type_t <C, _type <T...> > : _type <type <C, T>...> { };

template <typename C, typename F, typename T>
struct type_t <C, F(_type <T>)> : id_t <type <C, F>(_type <type <C, T> >)> { };

//-----------------------------------------------------------------------------

// extending definition @type/traits/ref
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

template <typename A, typename T, typename R = seq_ref <A> >
using seq_conv_ = expr <is_conv <R, T>() && !is_conv <A, T>()>;

template <typename T, typename A, typename R = seq_ref <A> >
using seq_explicit_ = expr <is_explicit <T, R>() && !is_explicit <T, A>()>;

}  // namespace details

template <typename A, typename T, bool = is_seq <A>()>
struct seq_conv : details::seq_conv_<A, T> { };

template <typename A, typename T>
struct seq_conv <A, T, false> : _false { };

template <typename T, typename A, bool = is_seq <A>()>
struct seq_explicit : details::seq_explicit_<T, A> { };

template <typename T, typename A>
struct seq_explicit <T, A, false> : _false { };

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
struct iter_t <C, _type <T> > : id_t <T> { };

template <typename C, typename T, typename Q>
struct trav_t <C, _type <T>, Q> : id_t <T> { };

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
struct iter_opt_ : rref_opt_t <T> { };

template <typename T>
struct iter_opt_<T, true> : base_opt_t <T> { };

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

namespace details {

template <typename A, typename T = seq_ref <A>, bool F = fix_seq <A>()>
struct seq_copy_ : id_t <heap_array <copy <T> > > { };

template <typename A, typename T>
struct seq_copy_<A, T, true> :
	id_t <fixed_array <copy <T>, seq_len <A>{}> > { };

// extending definition @type/traits/transform
template <typename C, typename... A>
struct copy_rec <sequence <C, A...> > : seq_copy_<sequence <C, A...> > { };

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILC_CORE_ARRAY_TYPE_TRAITS_HPP
