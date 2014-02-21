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

#ifndef IVL_CORE_ARRAY_TYPE_TAG_HPP
#define IVL_CORE_ARRAY_TYPE_TAG_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tag {

//-----------------------------------------------------------------------------

template <typename... D> struct atom_ { };
template <typename... D> struct iter_ { };
template <typename... D> struct trav_ { };

template <typename... D> struct aggr_ { };
template <typename... D> struct fixed_ { };
template <typename... D> struct heap_ { };

template <typename... D> using pre_fixed_ = pre_<fixed_<D...> >;

//-----------------------------------------------------------------------------

using atom = atom_<>;
using iter = iter_<>;
using trav = trav_<>;

using aggr  = aggr_<>;
using fixed = fixed_<>;
using heap  = heap_<>;

using pre_fixed = pre_fixed_<>;

//-----------------------------------------------------------------------------

}  // namespace tag

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_TYPE_TAG_HPP
