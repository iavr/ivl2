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

template <typename T>
struct is_array_ : _false { };

template <typename C, typename... A>
struct is_array_<sequence <C, A...> > : _true { };

template <typename T>
struct is_trav_ : _false { };

template <typename C, typename... A>
struct is_trav_<traversor <C, A...> > : _true { };

}  // namespace details

// no alias: fwd-declared
template <typename T>
struct is_array : details::is_array_<raw_type <T> > { };

// no alias: fwd-declared
template <typename T>
struct is_trav : details::is_trav_<raw_type <T> > { };

//-----------------------------------------------------------------------------

template <typename P> using all_array_p = all_p <is_array, P>;
template <typename P> using any_array_p = any_p <is_array, P>;

template <typename... E> using all_array = all_array_p <pack <E...> >;
template <typename... E> using any_array = any_array_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <typename P> using all_trav_p = all_p <is_trav, P>;
template <typename P> using any_trav_p = any_p <is_trav, P>;

template <typename... E> using all_trav = all_trav_p <pack <E...> >;
template <typename... E> using any_trav = any_trav_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <typename A> using seq_val        = typename A::value_type;
template <typename A> using seq_size       = typename A::size_type;
template <typename A> using seq_diff       = typename A::difference_type;
template <typename A> using seq_iter       = typename A::iterator;
template <typename A> using seq_fwd_iter   = typename A::fwd_iterator;
template <typename A> using seq_const_iter = typename A::const_iterator;
template <typename A> using seq_trav       = typename A::traversor;
template <typename A> using seq_fwd_trav   = typename A::fwd_traversor;
template <typename A> using seq_const_trav = typename A::const_traversor;

//-----------------------------------------------------------------------------

template <typename I> struct it_val_t  : id_t <typename I::value_type> { };
template <typename I> struct it_diff_t : id_t <typename I::difference_type> { };
template <typename I> struct it_ref_t  : id_t <typename I::reference> { };
template <typename I> struct it_ptr_t  : id_t <typename I::pointer> { };

template <typename T> struct it_val_t <T*>  : id_t <T> { };
template <typename T> struct it_diff_t <T*> : id_t <ptrdiff_t> { };
template <typename T> struct it_ref_t <T*>  : id_t <T&> { };
template <typename T> struct it_ptr_t <T*>  : id_t <T*> { };

template <typename I> using it_val  = type_of <it_val_t <I> >;
template <typename I> using it_diff = type_of <it_diff_t <I> >;
template <typename I> using it_ref  = type_of <it_ref_t <I> >;
template <typename I> using it_ptr  = type_of <it_ptr_t <I> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILC_CORE_ARRAY_TYPE_TRAITS_HPP
