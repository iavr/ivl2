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

   You should have received u copy of the GNU General Public License
   and u copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_ARRAY_VIEW_JOIN_HPP
#define IVL_CORE_ARRAY_VIEW_JOIN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename... U>
using join_length =
	if_size <_and <fix_seq <U>...>{}, sz_sum <id, seq_len <U>...> >;

template <typename U, typename UP = U>
struct join_traits;

template <typename... U, typename UP>
struct join_traits <pack <U...>, UP> : seq_traits <
	common <u_seq_ref <U>...>, join_length <U...>, UP,  // TODO: common & references
	join_iter, join_trav
> { };

//-----------------------------------------------------------------------------

template <
	typename U, typename N = sz_rng_of_p <U>,
	typename TR = traits_of <join_traits <U> >
>
struct join_seq_impl;

template <typename... U, size_t... N, typename TR>
class join_seq_impl <pack <U...>, sizes <N...>, TR> :
	public seq_base <join_seq <U...>, TR, U...>
{
	using B = seq_base <join_seq <U...>, TR, U...>;
	friend B;

	using S = seq_size <TR>;

	using IR = r_iter <TR>;
	using IL = l_iter <TR>;
	using IC = c_iter <TR>;

	using VR = r_trav <TR>;
	using VL = l_trav <TR>;
	using VC = c_trav <TR>;

	template <size_t K>
	using under = elem_at <K, U...>;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE r_pick <K, U...>
	u_f() { return under <K>::fwd(); }

	template <size_t K>
	INLINE r_pick <K, U...>
	u() && { return under <K>::fwd(); }

	template <size_t K>
	INLINE l_pick <K, U...>
	u() & { return under <K>::get(); }

	template <size_t K>
	INLINE constexpr c_pick <K, U...>
	u() const& { return under <K>::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr S size() const { return val_sum(u<N>().size()...); }

	INLINE           IR begin() &&     { return IR(u_f<N>().begin()...); }
	INLINE           IL begin() &      { return IL(u<N>().begin()...); }
	INLINE constexpr IC begin() const& { return IC(u<N>().begin()...); }

	INLINE           IR end() &&     { return IR(u_f<N>().end()...); }
	INLINE           IL end() &      { return IL(u<N>().end()...); }
	INLINE constexpr IC end() const& { return IC(u<N>().end()...); }

//-----------------------------------------------------------------------------

	template <typename... G>
	INLINE VR trav(G... g) && { return VR(0, u_f<N>().trav(g...)...); }

	template <typename... G>
	INLINE VL trav(G... g) & { return VL(0, u<N>().trav(g...)...); }

	template <typename... G>
	INLINE constexpr VC trav(G... g) const& { return VC(0, u<N>().trav(g...)...); }

};

//-----------------------------------------------------------------------------

template <typename... U>
struct sequence <tag::join, U...> :
	join_seq_impl <pack <U...> >
{
	using join_seq_impl <pack <U...> >::join_seq_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_VIEW_JOIN_HPP
