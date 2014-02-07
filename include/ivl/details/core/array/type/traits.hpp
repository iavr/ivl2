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

#ifndef IVL_DETAILS_CORE_ARRAY_TYPE_TRAITS_HPP
#define IVL_DETAILS_CORE_ARRAY_TYPE_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct is_seq_  : _false { };
template <typename T> struct is_cont_ : is_seq_<T> { };
template <typename T> struct is_trav_ : _false { };
template <typename T> struct is_iter_ : is_trav_<T> { };

template <typename T, size_t N>
struct is_cont_<T[N]> : _true { };

template <typename T>
struct is_cont_<initializer_list <T> > : _true { };

template <typename C, typename... A>
struct is_seq_<sequence <C, A...> > : _true { };

template <typename C, typename... A>
struct is_iter_<iterator <C, A...> > : _true { };

template <typename C, typename... A>
struct is_trav_<traversor <C, A...> > : _true { };

}  // namespace details

template <typename T> using is_cont = details::is_cont_<raw_type <T> >;
template <typename T> using is_seq  = details::is_seq_<raw_type <T> >;
template <typename T> using is_iter = details::is_iter_<raw_type <T> >;
template <typename T> using is_trav = details::is_trav_<raw_type <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = is_trav <T>{}>
struct seq_finite_ : _false { };

template <typename T>
struct seq_finite_ <T, true> : expr <T::finite> { };

}  // namespace details

template <typename T>
using seq_finite = details::seq_finite_<raw_type <T> >;

template <typename... T>
using seq_prim = first_b <seq_finite <T>{}...>;

//-----------------------------------------------------------------------------

template <typename P> using all_cont_p = all_p <is_cont, P>;
template <typename P> using any_cont_p = any_p <is_cont, P>;

template <typename... E> using all_cont = all_cont_p <pack <E...> >;
template <typename... E> using any_cont = any_cont_p <pack <E...> >;

template <typename P> using all_seq_p = all_p <is_seq, P>;
template <typename P> using any_seq_p = any_p <is_seq, P>;

template <typename... E> using all_seq = all_seq_p <pack <E...> >;
template <typename... E> using any_seq = any_seq_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <typename P> using all_iter_p = all_p <is_iter, P>;
template <typename P> using any_iter_p = any_p <is_iter, P>;

template <typename... E> using all_iter = all_iter_p <pack <E...> >;
template <typename... E> using any_iter = any_iter_p <pack <E...> >;

template <typename P> using all_trav_p = all_p <is_trav, P>;
template <typename P> using any_trav_p = any_p <is_trav, P>;

template <typename... E> using all_trav = all_trav_p <pack <E...> >;
template <typename... E> using any_trav = any_trav_p <pack <E...> >;

template <typename P> using all_finite_p = all_p <seq_finite, P>;
template <typename P> using any_finite_p = any_p <seq_finite, P>;

template <typename... E> using all_finite = all_finite_p <pack <E...> >;
template <typename... E> using any_finite = any_finite_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <typename... T>
using can_loop = expr <all_iter <T...>() && any_finite <T...>()>;

//-----------------------------------------------------------------------------

template <typename T> using begin_of = decltype(begin(gen <T>()));
template <typename T> using end_of   = decltype(end(gen <T>()));

template <typename T> using has_begin = sfinae <begin_of, T>;
template <typename T> using has_end   = sfinae <end_of, T>;

template <typename T>
using has_range = expr <has_begin <T>() && has_end <T>()>;

//-----------------------------------------------------------------------------

template <typename I>
struct seq_val_t : id_t <typename raw_type <I>::value_type> { };

template <typename I>
struct seq_size_t : id_t <typename raw_type <I>::size_type> { };

template <typename I>
struct seq_diff_t : id_t <typename raw_type <I>::difference_type> { };

template <typename I>
struct seq_ref_t  : id_t <typename raw_type <I>::reference> { };

template <typename I>
struct seq_ptr_t  : id_t <typename raw_type <I>::pointer> { };

template <typename T> struct seq_val_t <T*>  : id_t <T> { };
template <typename T> struct seq_size_t <T*> : id_t <size_t> { };
template <typename T> struct seq_diff_t <T*> : id_t <ptrdiff_t> { };
template <typename T> struct seq_ref_t <T*>  : id_t <T&> { };
template <typename T> struct seq_ptr_t <T*>  : id_t <T*> { };

template <typename I> using seq_val  = type_of <seq_val_t <I> >;
template <typename I> using seq_size = type_of <seq_size_t <I> >;
template <typename I> using seq_diff = type_of <seq_diff_t <I> >;
// template <typename I> using seq_ref  = type_of <seq_ref_t <I> >;  // defined @begin
template <typename I> using seq_ptr  = type_of <seq_ptr_t <I> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename A> struct r_iter_  : id_t <typename A::fwd_iterator> { };
template <typename A> struct l_iter_  : id_t <typename A::iterator> { };
template <typename A> struct cl_iter_ : id_t <typename A::const_iterator> { };

template <typename A> struct r_trav_  : id_t <typename A::fwd_traversor> { };
template <typename A> struct l_trav_  : id_t <typename A::traversor> { };
template <typename A> struct cl_trav_ : id_t <typename A::const_traversor> { };

template <typename T> struct r_iter_<T*>  : id_t <T*> { };
template <typename T> struct l_iter_<T*>  : id_t <T*> { };
template <typename T> struct cl_iter_<T*> : id_t <const T*> { };

template <typename T> struct r_trav_<T*>  : id_t <T*> { };
template <typename T> struct l_trav_<T*>  : id_t <T*> { };
template <typename T> struct cl_trav_<T*> : id_t <const T*> { };

using iter_ = choose_ref <r_iter_, l_iter_, cl_iter_>;
using trav_ = choose_ref <r_trav_, l_trav_, cl_trav_>;

}  // namespace details

//-----------------------------------------------------------------------------

template <typename T> using r_iter_t  = choose_r  <details::iter_, T>;
template <typename T> using l_iter_t  = choose_l  <details::iter_, T>;
template <typename T> using cl_iter_t = choose_cl <details::iter_, T>;

template <typename T> using r_trav_t  = choose_r  <details::trav_, T>;
template <typename T> using l_trav_t  = choose_l  <details::trav_, T>;
template <typename T> using cl_trav_t = choose_cl <details::trav_, T>;

template <typename T> using r_iter  = type_of <r_iter_t <T> >;
template <typename T> using l_iter  = type_of <l_iter_t <T> >;
template <typename T> using cl_iter = type_of <cl_iter_t <T> >;

template <typename T> using r_trav  = type_of <r_trav_t <T> >;
template <typename T> using l_trav  = type_of <l_trav_t <T> >;
template <typename T> using cl_trav = type_of <cl_trav_t <T> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILC_CORE_ARRAY_TYPE_TRAITS_HPP
