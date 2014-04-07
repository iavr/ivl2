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

#ifndef IVL_CORE_ATOM_USCORE_OP_HPP
#define IVL_CORE_ATOM_USCORE_OP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace atoms {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename V, only_if <is_trav <V>{}> = 0>
INLINE constexpr V&&
operator<<=(V&& v, uscore) { return fwd <V>(v) <<= key::iter(); }

template <typename V, only_if <is_trav <V>{}> = 0>
INLINE constexpr V&&
operator>>=(V&& v, uscore) { return fwd <V>(v) >>= key::iter(); }

//-----------------------------------------------------------------------------

INLINE constexpr inc_step
operator++(uscore) { return inc_step(); }

//-----------------------------------------------------------------------------

// TODO: elsewhere
template <typename T> struct is_range : _false { };

template <typename T> struct is_update            : _false { };
template <>           struct is_update <inc_step> : _true { };

//-----------------------------------------------------------------------------

// TODO: make & use afun::range
template <
	typename B, typename U,
	typename R = range_seq <raw_type <B>, base_opt <U> >,
	only_if <!is_range <B>() && is_update <U>()>
= 0>
INLINE constexpr R
operator,(B b, U&& u) { return R(b, fwd <U>(u)); }

template <
	typename B,
	typename R = range_seq <raw_type <B>, inc_step>,
	only_if <!is_range <B>()>
= 0>
INLINE constexpr R
operator,(B b, uscore) { return b, ++uscore(); }

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ATOM_USCORE_OP_HPP
