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

#ifndef IVL_CORE_ARRAY_FUN_TRAV_HPP
#define IVL_CORE_ARRAY_FUN_TRAV_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct seq_trav
{
	template <typename A>
	INLINE auto operator()(A&& a) const
	-> decltype(fwd <A>(a).trav())
		{ return fwd <A>(a).trav(); }
};

struct cont_trav
{
	template <typename A, typename I = begin_of <A> >
	INLINE constexpr iter_trav <I>
	operator()(A&& a) const
		{ return iter_trav <I>(begin(fwd <A>(a)), end(fwd <A>(a))); }
};

struct atom_trav
{
	template <typename A>
	INLINE auto operator()(A&& a) const
	-> decltype(raw_atom_trav <A>(fwd <A>(a)))
		{ return raw_atom_trav <A>(fwd <A>(a)); }
};

//-----------------------------------------------------------------------------

template <typename A>
using trav_sw = _switch <
	_case <is_trav <A>{}, id_fun>,
	_case <as_seq <A>{},  seq_trav>,
	atom_trav
>;

template <typename A>
using raw_trav_sw = _switch <
	_case <is_iter <A>{}, id_fun>,
	_case <as_seq <A>{},  seq_trav>,
	_case <is_cont <A>{}, cont_trav>,
	atom_trav
>;

using trav     = switch_fun <trav_sw>;
using raw_trav = switch_fun <raw_trav_sw>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::trav;
using details::raw_trav;

//-----------------------------------------------------------------------------

}  // namespace afun

static __attribute__ ((unused)) afun::trav      trav;
static __attribute__ ((unused)) afun::raw_trav  raw_trav;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_TRAV_HPP
