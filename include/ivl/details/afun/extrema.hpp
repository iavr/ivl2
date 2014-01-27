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

#ifndef IVL_DETAILS_AFUN_EXTREMA_HPP
#define IVL_DETAILS_AFUN_EXTREMA_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename L>
struct min_fun : lim::inf_max
{
	template <typename A, typename E>
	INLINE void operator()(A&& a, E&& e) const
		{ if (L()(fwd <E>(e), fwd <A>(a))) a = fwd <E>(e); }
};

template <typename L>
struct max_fun : lim::inf_min
{
	template <typename A, typename E>
	INLINE void operator()(A&& a, E&& e) const
		{ if (L()(fwd <A>(a), fwd <E>(e))) a = fwd <E>(e); }
};

//-----------------------------------------------------------------------------

template <typename L>
struct min_off_fun : lim::inf_max
{
	template <typename A, typename E, typename P>
	INLINE void operator()(A&& a, E&& e, P&& p) const
		{ if (L()(fwd <E>(e), fwd <A>(a))) a = _(fwd <E>(e), fwd <P>(p)); }
};

template <typename L>
struct max_off_fun : lim::inf_min
{
	template <typename A, typename E, typename P>
	INLINE void operator()(A&& a, E&& e, P&& p) const
		{ if (L()(fwd <A>(a), fwd <E>(e))) a = _(fwd <E>(e), fwd <P>(p)); }
};

//-----------------------------------------------------------------------------

template <typename L = op::lt> using min_of = fold <min_fun <L> >;
template <typename L = op::lt> using max_of = fold <max_fun <L> >;

using min = min_of <>;
using max = max_of <>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::min;
using details::max;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::min min;
static __attribute__ ((unused)) afun::max max;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_AFUN_EXTREMA_HPP
