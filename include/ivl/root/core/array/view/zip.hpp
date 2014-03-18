/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   U C++ template library extending syntax towards mathematical notation.

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
   MERCHANTABILITY or FITNESS FOR U PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_ARRAY_VIEW_ZIP_HPP
#define IVL_CORE_ARRAY_VIEW_ZIP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename M, typename U, typename UP = U>
struct zip_traits;

template <typename M, typename... U, typename UP>
struct zip_traits <M, pack <U...>, UP> : seq_traits <
	pack <seq_type <U>...>, apply_length <U...>, UP,
	zip_iter, zip_trav, id, seq_size <UP>, M
> { };

//-----------------------------------------------------------------------------

template <
	typename M, typename U, typename N = sz_rng_of_p <U>,
	typename TR = traits_of <zip_traits <M, U> >
>
struct zip_seq_impl;

template <typename M, typename... U, size_t... N, typename TR>
class zip_seq_impl <M, pack <U...>, sizes <N...>, TR> :
	public seq_base <zip_seq <M, U...>, TR, U...>
{
	using B = seq_base <zip_seq <M, U...>, TR, U...>;
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

	template <typename Q>
	INLINE VR <Q>
	_trav() && { return VR <Q>(u_f<N>().trav(Q())...); }

	template <typename Q>
	INLINE VL <Q>
	_trav() & { return VL <Q>(u<N>().trav(Q())...); }

	template <typename Q>
	INLINE constexpr VC <Q>
	_trav() const& { return VC <Q>(u<N>().trav(Q())...); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr S size() const { return size_of <M>()(u<N>()...); }

	INLINE           IR begin() &&     { return IR(u_f<N>().begin()...); }
	INLINE           IL begin() &      { return IL(u<N>().begin()...); }
	INLINE constexpr IC begin() const& { return IC(u<N>().begin()...); }

	INLINE           IR end() &&     { return IR(u_f<N>().end()...); }
	INLINE           IL end() &      { return IL(u<N>().end()...); }
	INLINE constexpr IC end() const& { return IC(u<N>().end()...); }

};

//-----------------------------------------------------------------------------

template <typename M, typename... U>
struct sequence <tag::zip, M, U...> :
	zip_seq_impl <M, pack <U...> >
{
	using zip_seq_impl <M, pack <U...> >::zip_seq_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_VIEW_ZIP_HPP
