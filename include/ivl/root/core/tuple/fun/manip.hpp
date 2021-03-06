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

#ifndef IVL_CORE_TUPLE_FUN_MANIP_HPP
#define IVL_CORE_TUPLE_FUN_MANIP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

using tup_join = uref_of <join_tup, all_tuple>;
using tup      = uref_of <join_tuple>;

using tup_zip   = uref_of <zip_tup,   all_tuple>;
using tup_inner = uref_of <zip_tuple, any_tuple>;

//-----------------------------------------------------------------------------

struct tup_head
{
	template <typename T>
	INLINE constexpr auto operator()(T&& t) const
	-> decltype(at()._<0>(fwd <T>(t)))
		{ return at()._<0>(fwd <T>(t)); }
};

template <template <typename...> class F = base_opt>
using tup_tail_as = make_as <F, tail_tup>;

template <template <typename...> class F = base_opt>
using tup_flip_as = make_as <F, flip_tup>;

using tup_tail = tup_tail_as <>;
using tup_flip = tup_flip_as <>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::tup;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::tup  tup;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_FUN_MANIP_HPP
