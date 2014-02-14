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

#ifndef IVL_CORE_TUPLE_TYPE_COLLECTION_HPP
#define IVL_CORE_TUPLE_TYPE_COLLECTION_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename C, typename... A> struct collection;

//-----------------------------------------------------------------------------

template <typename... E>
using raw_tuple = collection <data::raw <>, E...>;

template <typename... E>
using pre_tuple = collection <data::pre <>, E...>;

template <typename... E>
using tuple = collection <data::tuple <>, E...>;

//-----------------------------------------------------------------------------

template <typename U>
using tail_tup = collection <data::tail <>, U>;

template <typename K, typename U>
using indirect_tup = collection <data::indirect <>, K, U>;

template <typename F, typename... A>
using apply_tup = collection <data::apply <>, F, A...>;

template <typename... U> using zip_tup  = collection <data::zip <>,  U...>;
template <typename... U> using join_tup = collection <data::join <>, U...>;

//-----------------------------------------------------------------------------

template <typename F, typename... A>
using apply_tuple = apply_tup <F, tup_atom_of <A>...>;

template <typename... U> using zip_tuple  = zip_tup  <tup_atom_of <U>...>;
template <typename... U> using join_tuple = join_tup <tup_atom_of <U>...>;

//-----------------------------------------------------------------------------

// extended elsewhere
template <typename T> struct tup_data_t : pack <> { };
template <typename T> using  tup_data = type_of <tup_data_t <T> >;

template <typename C, typename... A>
struct tup_data_t <collection <C, A...> > : pack <A...> { };

//-----------------------------------------------------------------------------

}  // namespace details

using details::collection;

using details::tail_tup;
using details::indirect_tup;

using details::apply_tup;
using details::zip_tup;
using details::join_tup;

using details::apply_tuple;
using details::zip_tuple;
using details::join_tuple;

//-----------------------------------------------------------------------------

}  // namespace tuples

using tuples::details::raw_tuple;
using tuples::details::pre_tuple;
using tuples::details::tuple;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_TYPE_COLLECTION_HPP
