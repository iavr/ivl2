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

#ifndef IVL_DETAILS_CORE_ARRAY_FUN_LOGIC_HPP
#define IVL_DETAILS_CORE_ARRAY_FUN_LOGIC_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct _and
{
	INLINE constexpr bool operator()() const { return true; }

	template <typename A, typename... An>
	INLINE constexpr bool operator()(A&& a, An&&... an) const
		{ return fwd <A>(a) && operator()(fwd <An>(an)...); }
};

struct _or
{
	INLINE constexpr bool operator()() const { return false; }

	template <typename A, typename... An>
	INLINE constexpr bool operator()(A&& a, An&&... an) const
		{ return fwd <A>(a) || operator()(fwd <An>(an)...); }
};

//-----------------------------------------------------------------------------

}  // namespace details

using details::_and;
using details::_or;

//-----------------------------------------------------------------------------

}  // namespace afun

static __attribute__ ((unused)) afun::_and _and;
static __attribute__ ((unused)) afun::_or _or;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_FUN_LOGIC_HPP
