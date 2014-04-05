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

#ifndef IVL_CORE_ARRAY_STORE_RANGE_HPP
#define IVL_CORE_ARRAY_STORE_RANGE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D>
class step_base : public derived <D>
{
	using derived <D>::der;

public:
	template <typename I> INLINE I next(I i) const { der().inc(i); return i; }
	template <typename I> INLINE I prev(I i) const { der().dec(i); return i; }

	template <typename I, typename d>
	INLINE I rel(I i, d n) const { der().add(i, n); return i; }
};

//-----------------------------------------------------------------------------

class inc_step : public step_base <inc_step>
{
	template <typename I>
	INLINE I _size(_false, I b, I e) { return e > b ? e - b : I(0); }

// 	// TODO
// 	template <typename I>
// 	INLINE I _size(_true, I b, I e) { }

public:
	template <typename I> INLINE void inc(I& i) const { ++i; }
	template <typename I> INLINE void dec(I& i) const { --i; }

	template <typename I, typename d>
	INLINE void add(I& i, d n) const { i += n; }

	template <typename I, typename d>
	INLINE void sub(I& i, d n) const { i -= n; }

	template <typename F, typename I, typename O>
	INLINE constexpr bool comp(F f, I i, O o) const { return f(i, o); }

	template <typename I, typename F = is_floating <I> >
	INLINE constexpr I size(I b, I e) const { return _size(F(), b, e); }

	template <typename I>
	INLINE constexpr I end(I b, I e) const { return b + size(b, e); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::inc_step;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_STORE_RANGE_HPP
