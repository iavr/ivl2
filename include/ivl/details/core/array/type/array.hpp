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

#ifndef IVL_DETAILS_CORE_ARRAY_TYPE_ARRAY_HPP
#define IVL_DETAILS_CORE_ARRAY_TYPE_ARRAY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename C> class sequence;

//-----------------------------------------------------------------------------

template <typename T, size_t... N>
struct array_t : id_t <sequence <T, data::fixed <sizes <N...> > > > { };

template <typename T>
struct array_t <T> : id_t <sequence <T, data::heap <> > > { };

template <typename T, size_t... N>
using array = type_of <array_t <T, N...> >;

//-----------------------------------------------------------------------------

template <typename T, typename K, typename U>
using indirect_array = sequence <T, data::indirect <K, U> >;

template <typename T, size_t... N>
using aggr_array = sequence <T, data::aggr <sizes <N...> > >;

//-----------------------------------------------------------------------------

}  // namespace details

using details::sequence;

//-----------------------------------------------------------------------------

}  // namespace arrays

using arrays::details::array;
using arrays::details::aggr_array;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_TYPE_ARRAY_HPP
