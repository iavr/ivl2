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

#ifndef IVL_DETAILS_CORE_ARRAY_TYPE_ITER_HPP
#define IVL_DETAILS_CORE_ARRAY_TYPE_ITER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename S> class iterator;
template <typename T, typename S> class traversor;

template <typename T> using rev_iter  = iterator <T, data::rev <> >;
template <typename T> using iter_iter = iterator <T, data::iter <> >;
template <typename T> using atom_iter = iterator <T, data::atom <> >;

template <typename T> using iter_trav = traversor <T, data::iter <> >;
template <typename T> using atom_trav = traversor <T, data::atom <> >;

//-----------------------------------------------------------------------------

}  // namespace details

using details::iterator;
using details::traversor;

using details::rev_iter;
using details::iter_iter;
using details::atom_iter;

using details::iter_trav;
using details::atom_trav;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_TYPE_ITER_HPP
