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

#ifndef IVL_CORE_ARRAY_FUN_MANIP_HPP
#define IVL_CORE_ARRAY_FUN_MANIP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// TODO
// using seq = ....

//-----------------------------------------------------------------------------

using seq_join = uref_of <join_seq, all_seq>;
using arr      = uref_of <join_sequence>;

// no alias: entry point
template <typename M = prim_term>
struct seq_zip_on : uref_map <zip_seq_on <M>, all_seq> { };

template <typename M = prim_term>
struct seq_inner_on : uref_map <zip_sequence_on <M>, any_seq> { };

using seq_zip   = seq_zip_on <>;
using seq_inner = seq_inner_on <>;

//-----------------------------------------------------------------------------

struct seq_head
{
	template <typename A>
	INLINE constexpr auto operator()(A&& a) const
	-> decltype(fwd <A>(a)[0])
		{ return fwd <A>(a)[0]; }
};

template <template <typename...> class F = base_opt>
using seq_tail_as = make_as <F, tail_seq>;

template <template <typename...> class F = base_opt>
using seq_flip_as = make_as <F, flip_seq>;

using seq_tail = seq_tail_as <>;
using seq_flip = seq_flip_as <>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::arr;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_MANIP_HPP
