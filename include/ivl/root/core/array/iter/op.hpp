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

#ifndef IVL_CORE_ARRAY_ITER_OP_HPP
#define IVL_CORE_ARRAY_ITER_OP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

struct B;
namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename I, typename C = raw_type <I>, only_if <is_iter <I>{}> = 0>
INLINE C operator++(I&& i, int) { C c(i); return ++i, c; }

template <typename I, typename C = raw_type <I>, only_if <is_iter <I>{}> = 0>
INLINE C operator--(I&& i, int) { C c(i); return --i, c; }

//-----------------------------------------------------------------------------

template <typename I, only_if <is_iter <I>{}> = 0>
INLINE I operator+(I i, seq_diff <I> n) { return i += n; }

template <typename I, only_if <is_iter <I>{}> = 0>
INLINE I operator-(I i, seq_diff <I> n) { return i -= n; }

//-----------------------------------------------------------------------------

template <typename V, typename P, only_if <is_trav <V>{}> = 0>
INLINE V operator<<(V v, P) { return v <<= P(); }

template <typename V, typename P, only_if <is_trav <V>{}> = 0>
INLINE V operator>>(V v, P) { return v >>= P(); }

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_OP_HPP
