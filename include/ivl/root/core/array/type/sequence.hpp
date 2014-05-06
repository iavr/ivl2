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

#ifndef IVL_CORE_ARRAY_TYPE_ARRAY_HPP
#define IVL_CORE_ARRAY_TYPE_ARRAY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename C, typename... A> struct sequence;

//-----------------------------------------------------------------------------

template <typename T, size_t... N>
using aggr_array = sequence <tag::aggr, T, sizes <N...> >;

template <typename T, size_t... N>
using pre_fixed_array = sequence <tag::pre_fixed, T, sizes <N...> >;

template <typename T, size_t... N>
using fixed_array = sequence <tag::fixed, T, sizes <N...> >;

template <typename T>
using heap_array = sequence <tag::heap, T>;

//-----------------------------------------------------------------------------

template <typename... N>
using iota_seq = sequence <tag::iota, N...>;

template <typename B, typename U, typename... E>
using range_seq = sequence <tag::range, B, U, E...>;

template <typename B, typename U, typename... N>
using slice_seq = sequence <tag::slice, B, U, N...>;

//-----------------------------------------------------------------------------

template <typename U> using each_seq = sequence <tag::each, U>;
template <typename U> using tail_seq = sequence <tag::tail, U>;
template <typename U> using flip_seq = sequence <tag::flip, U>;

template <typename K, typename U>
using indirect_seq = sequence <tag::indirect, K, U>;

//-----------------------------------------------------------------------------

template <typename M, typename F, typename... A>
using apply_seq = sequence <tag::apply, M, F, A...>;

template <typename M, typename... U>
using zip_seq  = sequence <tag::zip, M, U...>;

template <typename... U>
using join_seq = sequence <tag::join, U...>;

//-----------------------------------------------------------------------------

template <typename M, typename F, typename... A>
using apply_sequence = apply_seq <M, F, seq_atom_of <A>...>;

template <typename M, typename... U>
using zip_sequence = zip_seq <M, seq_atom_of <U>...>;

template <typename... U>
using join_sequence = join_seq <seq_atom_of <U>...>;

template <typename M> using apply_seq_by      = bind <apply_seq, M>;
template <typename M> using apply_sequence_by = bind <apply_sequence, M>;

template <typename M> using zip_seq_by      = bind <zip_seq, M>;
template <typename M> using zip_sequence_by = bind <zip_sequence, M>;

//-----------------------------------------------------------------------------

template <typename T, size_t... N>
struct array_t : id_t <fixed_array <T, N...> > { };

template <typename T>
struct array_t <T> : id_t <heap_array <T> > { };

template <typename T, size_t... N>
using array = type_of <array_t <T, N...> >;

//-----------------------------------------------------------------------------

// extended elsewhere
template <typename A> struct seq_data_t : pack <> { };
template <typename A> using  seq_data = type_of <seq_data_t <A> >;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::sequence;

using details::pre_fixed_array;
using details::fixed_array;
using details::heap_array;

using details::iota_seq;
using details::range_seq;
using details::slice_seq;

using details::each_seq;
using details::tail_seq;
using details::flip_seq;
using details::indirect_seq;

using details::apply_seq;
using details::apply_seq_by;
using details::zip_seq;
using details::zip_seq_by;
using details::join_seq;

using details::apply_sequence;
using details::apply_sequence_by;
using details::zip_sequence;
using details::zip_sequence_by;
using details::join_sequence;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

using arrays::details::array;
using arrays::details::aggr_array;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_TYPE_ARRAY_HPP
