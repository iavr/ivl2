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

template <typename M, typename A, typename AP = A>
struct zip_traits;

template <typename M, typename... A, typename AP>
struct zip_traits <M, pack <A...>, AP> : seq_traits <
	pack <u_seq_ref <A>...>, apply_length <A...>, AP,
	zip_iter, zip_trav, seq_size <AP>, M
> { };

//-----------------------------------------------------------------------------

template <
	typename M, typename A, typename N = sz_rng_of_p <A>,
	typename TR = traits_of <zip_traits <M, A> >
>
struct zip_seq_impl;

template <typename M, typename... A, size_t... N, typename TR>
class zip_seq_impl <M, pack <A...>, sizes <N...>, TR> :
	public seq_base <zip_seq <M, A...>, TR, A...>
{
	using B = seq_base <zip_seq <M, A...>, TR, A...>;
	friend B;

	using S = seq_size <TR>;

	using IR = r_iter <TR>;
	using IL = l_iter <TR>;
	using IC = c_iter <TR>;

	using VR = r_trav <TR>;
	using VL = l_trav <TR>;
	using VC = c_trav <TR>;

	template <size_t K>
	using arg = elem_at <K, A...>;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE r_pick <K, A...>
	a_f() { return arg <K>::fwd(); }

	template <size_t K>
	INLINE r_pick <K, A...>
	a() && { return arg <K>::fwd(); }

	template <size_t K>
	INLINE l_pick <K, A...>
	a() & { return arg <K>::get(); }

	template <size_t K>
	INLINE constexpr c_pick <K, A...>
	a() const& { return arg <K>::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr S size() const { return M().size(a<N>()...); }

	INLINE           IR begin() &&     { return IR(a_f<N>().begin()...); }
	INLINE           IL begin() &      { return IL(a<N>().begin()...); }
	INLINE constexpr IC begin() const& { return IC(a<N>().begin()...); }

	INLINE           IR end() &&     { return IR(a_f<N>().end()...); }
	INLINE           IL end() &      { return IL(a<N>().end()...); }
	INLINE constexpr IC end() const& { return IC(a<N>().end()...); }

	INLINE           VR trav() &&     { return VR(a_f<N>().trav()...); }
	INLINE           VL trav() &      { return VL(a<N>().trav()...); }
	INLINE constexpr VC trav() const& { return VC(a<N>().trav()...); }
};

//-----------------------------------------------------------------------------

template <typename M, typename... A>
struct sequence <data::zip <>, M, A...> :
	zip_seq_impl <M, pack <A...> >
{
	using zip_seq_impl <M, pack <A...> >::zip_seq_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_VIEW_ZIP_HPP
