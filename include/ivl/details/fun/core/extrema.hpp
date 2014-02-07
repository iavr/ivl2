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

#ifndef IVL_FUN_CORE_EXTREMA_HPP
#define IVL_FUN_CORE_EXTREMA_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace fun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// TODO: vec-min_off
template <typename L = op::lt>
struct min_of : afun::vec_fold <afun::min_of <L> >, afun::lim::min
{
	template <typename M, typename P, typename A>
	void io(M& m, P& p, sep, A&& a)
		{ lref(m, p) = afun::min_off_of <L>()(fwd <A>(a)); }
};

template <typename L = op::lt>
struct max_of : afun::vec_fold <afun::max_of <L> >, afun::lim::max
{
	template <typename M, typename P, typename A>
	void io(M& m, P& p, sep, A&& a)
		{ lref(m, p) = afun::max_off_of <L>()(fwd <A>(a)); }
};

using min = min_of <>;
using max = max_of <>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::min_of;
using details::max_of;
using details::min;
using details::max;

//-----------------------------------------------------------------------------

}  // namespace fun

//-----------------------------------------------------------------------------

IVL_KEY_TMP(min, fun::min)
IVL_KEY_TMP(max, fun::max)

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_FUN_CORE_EXTREMA_HPP
