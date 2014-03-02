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

#ifndef IVL_CORE_TUPLE_TYPE_TAG_HPP
#define IVL_CORE_TUPLE_TYPE_TAG_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tag {

//-----------------------------------------------------------------------------

template <typename... D> struct raw_ { };
template <typename... D> struct pre_ { };
template <typename... D> struct tuple_ { };

template <typename... D> struct tail_ { };
template <typename... D> struct flip_ { };
template <typename... D> struct indirect_ { };
template <typename... D> struct apply_ { };
template <typename... D> struct zip_ { };
template <typename... D> struct join_ { };

//-----------------------------------------------------------------------------

using raw   = raw_<>;
using pre   = pre_<>;
using tuple = tuple_<>;

using tail     = tail_<>;
using flip     = flip_<>;
using indirect = indirect_<>;
using apply    = apply_<>;
using zip      = zip_<>;
using join     = join_<>;

//-----------------------------------------------------------------------------

}  // namespace tag

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_TYPE_TAG_HPP
