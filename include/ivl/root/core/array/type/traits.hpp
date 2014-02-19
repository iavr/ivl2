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

struct A;
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

template <typename I> struct seq_ref_  : id_t <typename I::reference> { };
template <typename I> struct seq_type_ : id_t <typename I::value_type> { };
template <typename I> struct seq_size_ : id_t <typename I::size_type> { };
template <typename I> struct seq_diff_ : id_t <typename I::difference_type> { };
template <typename I> struct seq_ptr_  : id_t <typename I::pointer> { };

template <typename T> struct seq_ref_<T*>  : id_t <T&> { };
template <typename T> struct seq_type_<T*> : id_t <T> { };
template <typename T> struct seq_size_<T*> : id_t <size_t> { };
template <typename T> struct seq_diff_<T*> : id_t <ptrdiff_t> { };
template <typename T> struct seq_ptr_<T*>  : id_t <T*> { };

}  // namespace details

//-----------------------------------------------------------------------------

template <typename I> struct seq_ref_t  : details::seq_ref_<raw_type <I> > { };
template <typename I> struct seq_type_t : details::seq_type_<raw_type <I> > { };
template <typename I> struct seq_size_t : details::seq_size_<raw_type <I> > { };
template <typename I> struct seq_diff_t : details::seq_diff_<raw_type <I> > { };
template <typename I> struct seq_ptr_t  : details::seq_ptr_<raw_type <I> > { };

// template <typename I> using seq_ref  = type_of <seq_ref_t <I> >;   // defined @begin
// template <typename I> using seq_type = type_of <seq_type_t <I> >;  // defined @begin
template <typename I> using seq_size = type_of <seq_size_t <I> >;
template <typename I> using seq_diff = type_of <seq_diff_t <I> >;
template <typename I> using seq_ptr  = type_of <seq_ptr_t <I> >;

//-----------------------------------------------------------------------------

template <typename T> struct seq_size_t <_type <T> > : id_t <size_t> { };
template <typename T> struct seq_diff_t <_type <T> > : id_t <ptrdiff_t> { };

template <typename... I>
struct seq_size_t <pack <I...> > : common_t <seq_size <I>...> { };

template <typename... I>
struct seq_diff_t <pack <I...> > : common_t <seq_diff <I>...> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename A> struct r_seq_ref_ : id_t <typename A::fwd_reference> { };
template <typename A> struct l_seq_ref_ : id_t <typename A::reference> { };
template <typename A> struct c_seq_ref_ : id_t <typename A::const_reference> { };

template <typename A> struct l_seq_ptr_ : id_t <typename A::pointer> { };
template <typename A> struct c_seq_ptr_ : id_t <typename A::const_pointer> { };

template <typename T> struct r_seq_ref_<T*> : id_t <T&> { };
template <typename T> struct l_seq_ref_<T*> : id_t <T&> { };
template <typename T> struct c_seq_ref_<T*> : id_t <const T&> { };

template <typename T> struct l_seq_ptr_<T*> : id_t <T*> { };
template <typename T> struct c_seq_ptr_<T*> : id_t <const T*> { };

using seq_ref_sw = switch_ref <r_seq_ref_, l_seq_ref_, c_seq_ref_>;
using seq_ptr_sw = switch_ref <l_seq_ptr_, l_seq_ptr_, c_seq_ptr_>;

}  // namespace details

//-----------------------------------------------------------------------------

template <typename T> using r_seq_ref_t = switch_r <details::seq_ref_sw, T>;
template <typename T> using l_seq_ref_t = switch_l <details::seq_ref_sw, T>;
template <typename T> using c_seq_ref_t = switch_c <details::seq_ref_sw, T>;

template <typename T> using l_seq_ptr_t = switch_l <details::seq_ptr_sw, T>;
template <typename T> using c_seq_ptr_t = switch_c <details::seq_ptr_sw, T>;

template <typename T> using r_seq_ref = type_of <r_seq_ref_t <T> >;
template <typename T> using l_seq_ref = type_of <l_seq_ref_t <T> >;
template <typename T> using c_seq_ref = type_of <c_seq_ref_t <T> >;

template <typename T> using l_seq_ptr = type_of <l_seq_ptr_t <T> >;
template <typename T> using c_seq_ptr = type_of <c_seq_ptr_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename A> struct r_iter_ : id_t <typename A::fwd_iterator> { };
template <typename A> struct l_iter_ : id_t <typename A::iterator> { };
template <typename A> struct c_iter_ : id_t <typename A::const_iterator> { };

template <typename A> struct r_trav_ : id_t <typename A::fwd_traversor> { };
template <typename A> struct l_trav_ : id_t <typename A::traversor> { };
template <typename A> struct c_trav_ : id_t <typename A::const_traversor> { };

template <typename T> struct r_iter_<T*> : id_t <T*> { };
template <typename T> struct l_iter_<T*> : id_t <T*> { };
template <typename T> struct c_iter_<T*> : id_t <const T*> { };

template <typename T> struct r_trav_<T*> : id_t <T*> { };
template <typename T> struct l_trav_<T*> : id_t <T*> { };
template <typename T> struct c_trav_<T*> : id_t <const T*> { };

using iter_sw = switch_ref <r_iter_, l_iter_, c_iter_>;
using trav_sw = switch_ref <r_trav_, l_trav_, c_trav_>;

}  // namespace details

//-----------------------------------------------------------------------------

template <typename T> struct r_iter_t : switch_r <details::iter_sw, T> { };
template <typename T> struct l_iter_t : switch_l <details::iter_sw, T> { };
template <typename T> struct c_iter_t : switch_c <details::iter_sw, T> { };

template <typename T> struct r_trav_t : switch_r <details::trav_sw, T> { };
template <typename T> struct l_trav_t : switch_l <details::trav_sw, T> { };
template <typename T> struct c_trav_t : switch_c <details::trav_sw, T> { };

template <typename T> using r_iter = type_of <r_iter_t <T> >;
template <typename T> using l_iter = type_of <l_iter_t <T> >;
template <typename T> using c_iter = type_of <c_iter_t <T> >;

template <typename T> using r_trav = type_of <r_trav_t <T> >;
template <typename T> using l_trav = type_of <l_trav_t <T> >;
template <typename T> using c_trav = type_of <c_trav_t <T> >;

//-----------------------------------------------------------------------------

template <typename T> struct r_iter_t <_type <T> > : id_t <T> { };
template <typename T> struct l_iter_t <_type <T> > : id_t <T> { };
template <typename T> struct c_iter_t <_type <T> > : id_t <T> { };

template <typename T> struct r_trav_t <_type <T> > : id_t <T> { };
template <typename T> struct l_trav_t <_type <T> > : id_t <T> { };
template <typename T> struct c_trav_t <_type <T> > : id_t <T> { };

template <typename... A> struct r_iter_t <pack <A...> > : pack <r_iter <A>...> { };
template <typename... A> struct l_iter_t <pack <A...> > : pack <l_iter <A>...> { };
template <typename... A> struct c_iter_t <pack <A...> > : pack <c_iter <A>...> { };

template <typename... A> struct r_trav_t <pack <A...> > : pack <r_trav <A>...> { };
template <typename... A> struct l_trav_t <pack <A...> > : pack <l_trav <A>...> { };
template <typename... A> struct c_trav_t <pack <A...> > : pack <c_trav <A>...> { };

//-----------------------------------------------------------------------------

template <typename A, typename T, typename S = seq_type <A> >
using seq_conv = expr <is_conv <S, T>() && !is_conv <A, T>()>;

template <typename T, typename A, typename S = seq_type <A> >
using seq_explicit = expr <is_explicit <T, S>() && !is_explicit <T, A>()>;

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = is_ref <T>{}>
struct seq_result_ : id_t <T> { };

template <typename T>
struct seq_result_<T, false> : _type <T> { };

}  // namespace details

template <typename T> using seq_result_t = details::seq_result_<T>;
template <typename T> using seq_result = type_of <seq_result_t <T> >;

// extending definition @tuple/type/traits
template <typename T> struct r_ref_t <_type <T> > : id_t <T> { };
template <typename T> struct l_ref_t <_type <T> > : id_t <T> { };
template <typename T> struct c_ref_t <_type <T> > : id_t <T> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename S> struct seq_ret_;

template <typename F, typename... A>
struct seq_ret_<F(pack <A...>)> : ret_t <F(A...)> { };

}  // namespace details

template <typename... T>
using seq_args = pack <seq_type <seq_atom_of <T> >...>;

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

template <typename A, typename T = seq_type <A>, bool F = fix_seq <A>()>
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
