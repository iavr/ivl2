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

#ifndef IVL_DETAILS_CORE_ARRAY_FUN_TRAV_HPP
#define IVL_DETAILS_CORE_ARRAY_FUN_TRAV_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct ptr_iter
{
	template <typename T>
	INLINE constexpr iter_iter <T*, T&>
	operator()(T* p) const { return iter_iter <T*, T&>(p); }
};

struct rng_trav
{
	template <typename A, typename I = decltype(begin(gen <A>()))>
	INLINE constexpr iter_trav <I, seq_ref <I> >
	operator()(A&& a) const
		{ return iter_trav <I, seq_ref <I> >(begin(fwd <A>(a)), end(fwd <A>(a))); }
};

//-----------------------------------------------------------------------------

struct trav
{
	template <typename A, only_if <is_array <A>{}> = 0>
	INLINE auto operator()(A&& a) const
	-> decltype(fwd <A>(a).trav())
		{ return fwd <A>(a).trav(); }

	template <typename A, only_if <is_trav <A>{}> = 0>
	INLINE A&& operator()(A&& a) const { return fwd <A>(a); }

	template <typename A, only_if <!is_array <A>() && !is_trav <A>()> = 0>
	INLINE constexpr atom_trav <A>
	operator()(A&& a) const { return atom_trav <A>(fwd <A>(a)); }
};

//-----------------------------------------------------------------------------

}  // namespace details

using details::ptr_iter;
using details::rng_trav;
using details::trav;

//-----------------------------------------------------------------------------

}  // namespace afun

static __attribute__ ((unused)) afun::trav  trav;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_FUN_TRAV_HPP
