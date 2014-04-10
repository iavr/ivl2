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
	template <typename I> INLINE I next(I i) const { return der().inc(i), i; }
	template <typename I> INLINE I prev(I i) const { return der().dec(i), i; }

	template <typename I, typename d>
	INLINE I rel(I i, d n) const { return der().add(i, n), i; }
};

//-----------------------------------------------------------------------------

class inc_step : public step_base <inc_step>
{
	// TODO: _true (floating) versions
	template <typename S, typename I, typename E>
	INLINE S _size(_false, I&& b, E&& e)
		{ return e >= b ? static_cast <S>(fwd <E>(e) - fwd <I>(b)) : S(); }

	template <typename I, typename E>
	INLINE copy <I> _end(_false, I&& b, E&& e)
		{ return e >= b ? fwd <E>(e) : fwd <B>(b); }

public:
	template <typename I> INLINE void inc(I&& i) const { ++fwd <I>(i); }
	template <typename I> INLINE void dec(I&& i) const { --fwd <I>(i); }

	template <typename I, typename d>
	INLINE void add(I&& i, d n) const { fwd <I>(i) += n; }

	template <typename I, typename d>
	INLINE void sub(I&& i, d n) const { fwd <I>(i) -= n; }

	template <typename F, typename I, typename O>
	INLINE constexpr bool
	comp(F f, I&& i, O&& o) const { return f(fwd <I>(i), fwd <O>(o)); }

	template <
		typename S, typename I, typename E,
		typename F = is_floating <raw_type <I> >
	>
	INLINE constexpr S
	size(I&& b, E&& e) const { return _size <S>(F(), fwd <I>(b), fwd <E>(e)); }

	template <typename I, typename E, typename F = is_floating <raw_type <I> > >
	INLINE constexpr copy <I>
	end(I&& b, E&& e) const { return _end(F(), fwd <I>(b), fwd <E>(e)); }
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
