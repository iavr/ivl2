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

#ifndef IVL_CORE_ARRAY_FUN_TERM_HPP
#define IVL_CORE_ARRAY_FUN_TERM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename S, typename M>
struct iter_term
{
	template <typename... A>
	INLINE constexpr auto
	size(A&&... a) const
	-> decltype(S()(fwd <A>(a).size()...))
		{ return S()(fwd <A>(a).size()...); }

	template <typename... A>
	INLINE constexpr bool
	more(A&&... a) const { return M()(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

using all_term = iter_term <val_min, _and>;

//-----------------------------------------------------------------------------

struct prim_term
{
	template <typename... A>
	INLINE constexpr auto
	size(A&&... a) const
	-> decltype(get <prim_seq <A...>{}>()(fwd <A>(a)...).size())
		{ return get <prim_seq <A...>{}>()(fwd <A>(a)...).size(); }

	template <typename... A>
	INLINE constexpr bool
	more(A&&... a) const { return get <prim_trav <A...>{}>()(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_TERM_HPP