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

template <typename Q>
struct seq_trav
{
	template <typename A>
	INLINE auto operator()(A&& a) const
	-> decltype(fwd <A>(a).trav(Q()))
		{ return fwd <A>(a).trav(Q()); }
};

template <typename Q>
struct cont_trav
{
	template <typename A, typename I = begin_of <A> >
	INLINE constexpr iter_trav <Q, I>
	operator()(A&& a) const
		{ return iter_trav <Q, I>(begin(fwd <A>(a)), end(fwd <A>(a))); }
};

//-----------------------------------------------------------------------------

template <typename Q>
using trav_sw = t_switch <
	t_case <is_trav, id_fun>,
	t_case <as_seq,  seq_trav <Q> >,
	t_else <make <inf_atom_trav> >
>;

template <typename Q>
using raw_trav_sw = t_switch <
	t_case <is_iter, id_fun>,
	t_case <as_seq,  seq_trav <Q> >,
	t_case <is_cont, cont_trav <Q> >,
	t_else <make <inf_atom_trav> >
>;

template <typename Q = path>
using trav_on = switch_fun_of <trav_sw <Q> >;

template <typename Q = path>
using raw_trav_on = switch_fun_of <raw_trav_sw <Q> >;

using trav     = trav_on <>;
using raw_trav = raw_trav_on <>;

//-----------------------------------------------------------------------------

template <template <typename> class V, typename Q>
class ends_trav
{
	using R = V <Q>;
	using B = sizes <path_flip <Q>{}, path_in <Q>{}>;

	template <typename I>
	INLINE constexpr R
	trav(sizes <0, 0>, I&& b, I&& e) const { return R(b, e); }

	template <typename I>
	INLINE constexpr R
	trav(sizes <1, 0>, I&& b, I&& e) const { return R(e-1, b-1); }

	template <typename I>
	INLINE constexpr R
	trav(sizes <0, 1>, I&& b, I&& e) const { return R(b, b, e-1); }

	template <typename I>
	INLINE constexpr R
	trav(sizes <1, 1>, I&& b, I&& e) const { return R(e-1, e-1, b); }

public:
	template <typename I>
	INLINE constexpr R
	operator()(I&& b, I&& e) const { return trav(B(), b, e); }
};

//-----------------------------------------------------------------------------

}  // namespace details

using details::trav;
using details::trav_on;
using details::raw_trav;
using details::raw_trav_on;
using details::ends_trav;

//-----------------------------------------------------------------------------

}  // namespace afun

static __attribute__ ((unused)) afun::trav      trav;
static __attribute__ ((unused)) afun::raw_trav  raw_trav;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_TRAV_HPP
