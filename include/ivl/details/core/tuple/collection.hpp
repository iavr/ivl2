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

#ifndef IVL_DETAILS_CORE_TUPLE_COLLECTION_HPP
#define IVL_DETAILS_CORE_TUPLE_COLLECTION_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename P> struct base_tup;

template <typename S, typename... A> struct store;
template <typename S, typename... A> struct collection;

//-----------------------------------------------------------------------------

template <typename... E>
using tuple = collection <data::tuple <>, E...>;

template <typename K, typename U>
using indirect_tup = collection <data::indirect <>, K, U>;

template <typename F, typename... A>
using apply_tup = collection <data::apply <>, F, A...>;

template <typename F, typename... A>
using loop_tup = collection <data::loop <>, F, A...>;

template <typename... U>
using zip_tup = collection <data::zip <>, U...>;

template <typename... U>
using join_tup = collection <data::join <>, U...>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::base_tup;
using details::collection;

using details::tuple;
using details::indirect_tup;
using details::apply_tup;
using details::loop_tup;
using details::zip_tup;
using details::join_tup;

//-----------------------------------------------------------------------------

}  // namespace tuples

using tuples::tuple;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_COLLECTION_HPP
