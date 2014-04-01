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

#ifndef IVL_CORE_FUN_OP_SWAP_HPP
#define IVL_CORE_FUN_OP_SWAP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace fun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct swap : afun::swap
{
	using afun::swap::operator();

	template <typename T, typename U, only_if <all_tuple <T, U>{}> = 0>
	INLINE void
	operator()(T&& t, U&& u) const { loop(*this, fwd <T>(t), fwd <U>(u)); }

	// TODO: specialize for sequences with .swap() like heap_array
	template <typename A, typename B, only_if <all_seq <A, B>{}> = 0>
	INLINE void
	operator()(A&& a, B&& b) const { loop(*this, fwd <A>(a), fwd <B>(b)); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::swap;

//-----------------------------------------------------------------------------

}  // namespace fun

//-----------------------------------------------------------------------------

// definitions in same namespace as containers
// to be selected via ADL over std::swap

//-----------------------------------------------------------------------------

namespace tuples {
namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename U, only_if <all_tuple <T, U>{}> = 0>
INLINE void
swap(T&& t, U&& u) { fun::swap()(fwd <T>(t), fwd <U>(u)); }

//-----------------------------------------------------------------------------

}  // namespace details
}  // namespace tuples

//-----------------------------------------------------------------------------

namespace arrays {
namespace details {

//-----------------------------------------------------------------------------

template <typename A, typename B, only_if <all_seq <A, B>{}> = 0>
INLINE void
swap(A&& a, B&& b) { fun::swap()(fwd <A>(a), fwd <B>(b)); }

//-----------------------------------------------------------------------------

}  // namespace details
}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_OP_SWAP_HPP
