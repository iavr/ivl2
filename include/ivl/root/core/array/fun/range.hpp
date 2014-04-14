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

#ifndef IVL_CORE_ARRAY_FUN_RANGE_HPP
#define IVL_CORE_ARRAY_FUN_RANGE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

class range
{
	using F = uref_of <range_seq>;

	template <typename U, only_if <!is_uscore <U>{}> = 0>
	INLINE constexpr U&&
	delta(U&& u) const { return fwd <U>(u); }

	template <typename U, only_if <is_uscore <U>{}> = 0>
	INLINE constexpr auto
	delta(U&& u) const
	-> decltype(++u)
		{ return ++u; }

public:
	template <typename B, typename U, typename... E>
	INLINE constexpr auto
	operator()(B&& b, U&& u, E&&... e) const
	-> decltype(F()(fwd <B>(b), delta(fwd <U>(u)), fwd <E>(e)...))
		{ return F()(fwd <B>(b), delta(fwd <U>(u)), fwd <E>(e)...); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::range;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_RANGE_HPP
