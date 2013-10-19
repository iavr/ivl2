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

#ifndef IVL_DETAILS_CORE_FUN_SWAP_HPP
#define IVL_DETAILS_CORE_FUN_SWAP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuple_details {

//-----------------------------------------------------------------------------

struct swap_fun : public afun::swap
{
	using afun::swap::operator();

	template <typename T, typename U, enable_if <all_tuple <T, U>{}> = 0>
	INLINE void
	operator()(T&& t, U&& u) const { loop(*this, fwd <T>(t), fwd <U>(u)); }
};

//-----------------------------------------------------------------------------
// defined in same namespace as collection
// to be selected via ADL over std::swap

template <typename T, typename U, enable_if <all_tuple <T, U>{}> = 0>
INLINE void
swap(T&& t, U&& u) { swap_fun()(fwd <T>(t), fwd <U>(u)); }

//-----------------------------------------------------------------------------

}  // namespace tuple_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_FUN_SWAP_HPP
