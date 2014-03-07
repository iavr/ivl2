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
	_type <seq_type <U>...>, join_length <U...>, UP,
	join_iter, join_trav, edge_on
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

	using IR = r_seq_iter <TR>;
	using IL = l_seq_iter <TR>;
	using IC = c_seq_iter <TR>;

	template <typename Q> using VR = r_seq_trav <TR, Q>;
	template <typename Q> using VL = l_seq_trav <TR, Q>;
	template <typename Q> using VC = c_seq_trav <TR, Q>;

	template <size_t K>
	using under = elem_at <K, U...>;

//-----------------------------------------------------------------------------

	using E  = edge;
	using EP = edge_on <path>;

	using FF = afun::val_first;
	using FL = afun::val_last;

	template <template <typename> class VT, typename Q>
	using FV = join_ends <VT, Q>;

	static constexpr size_t L = sizeof...(U);

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

	template <typename IT, typename... V>
	static INLINE constexpr IT
	b(V&&... v) { return IT(FF()(v...), v...); }

	template <typename IT, typename... V>
	static INLINE constexpr IT
	e(V&&... v) { return IT(L, v >>= E()...); }

	template <template <typename> class VT, typename Q, typename... V>
	static INLINE constexpr VT <Q>
	t(V&&... v) { return FV <VT, Q>()(FF()(v...), FL()(v...), v...); }

//-----------------------------------------------------------------------------

	template <typename Q>
	INLINE VR <Q>
	_trav() && { return t <VR, Q>(u_f<N>().trav(edge_on <Q>())...); }

	template <typename Q>
	INLINE VL <Q>
	_trav() & { return t <VL, Q>(u<N>().trav(edge_on <Q>())...); }

	template <typename Q>
	INLINE constexpr VC <Q>
	_trav() const& { return t <VC, Q>(u<N>().trav(edge_on <Q>())...); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr S size() const { return val_sum(u<N>().size()...); }

	INLINE           IR begin() &&     { return b <IR>(u_f<N>().trav(EP())...); }
	INLINE           IL begin() &      { return b <IL>(u  <N>().trav(EP())...); }
	INLINE constexpr IC begin() const& { return b <IC>(u  <N>().trav(EP())...); }

	INLINE           IR end() &&     { return e <IR>(u_f<N>().trav(EP())...); }
	INLINE           IL end() &      { return e <IL>(u  <N>().trav(EP())...); }
	INLINE constexpr IC end() const& { return e <IC>(u  <N>().trav(EP())...); }

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
