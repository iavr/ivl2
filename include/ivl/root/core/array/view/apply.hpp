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

#ifndef IVL_CORE_ARRAY_VIEW_APPLY_HPP
#define IVL_CORE_ARRAY_VIEW_APPLY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename M, typename... A>
using apply_order = seq_order <term_pick <M, A...> >;

template <typename M, typename F, typename A, typename AP = A>
struct apply_traits;

template <typename M, typename F, typename... A, typename AP>
struct apply_traits <M, F, pack <A...>, AP> : seq_traits <
	F(pack <seq_type <A>...>), apply_order <M, A...>, AP,
	apply_trav, id, seq_size <AP>, term_get <M, A...>, F
> { };

//-----------------------------------------------------------------------------

template <
	typename M, typename F, typename A, typename N = sz_rng_of_p <A>,
	typename TR = traits_of <apply_traits <M, F, A> >
>
struct apply_seq_impl;

template <typename M, typename F, typename... A, size_t... N, typename TR>
class apply_seq_impl <M, F, pack <A...>, sizes <N...>, TR> :
	public seq_base <apply_seq <M, F, A...>, TR, F, A...>
{
	using B = seq_base <apply_seq <M, F, A...>, TR, F, A...>;
	friend B;

	using S = seq_size <TR>;
	using G = term_get <M, A...>;

	using IR = r_seq_iter <TR>;
	using IL = l_seq_iter <TR>;
	using IC = c_seq_iter <TR>;

	template <typename Q> using VR = r_seq_trav <TR, Q>;
	template <typename Q> using VL = l_seq_trav <TR, Q>;
	template <typename Q> using VC = c_seq_trav <TR, Q>;

	using fun = elem <0, F>;

	template <size_t K>
	using arg = elem_at <K + 1, F, A...>;

//-----------------------------------------------------------------------------

	INLINE           r_ref <F> f_f()      { return fun::fwd(); }
	INLINE           r_ref <F> f() &&     { return fun::fwd(); }
	INLINE           l_ref <F> f() &      { return fun::get(); }
	INLINE constexpr c_ref <F> f() const& { return fun::get(); }

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

	template <typename Q>
	INLINE VR <Q>
	_trav() && { return VR <Q>(f_f(), a_f<N>().trav(Q())...); }

	template <typename Q>
	INLINE VL <Q>
	_trav() & { return VL <Q>(f(), a<N>().trav(Q())...); }

	template <typename Q>
	INLINE constexpr VC <Q>
	_trav() const& { return VC <Q>(f(), a<N>().trav(Q())...); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr S size() const { return G()(a<N>()...).size(); }

	INLINE           IR begin() &&     { return IR(f_f(), a_f<N>().begin()...); }
	INLINE           IL begin() &      { return IL(f(), a<N>().begin()...); }
	INLINE constexpr IC begin() const& { return IC(f(), a<N>().begin()...); }

	INLINE           IR end() &&     { return IR(f_f(), a_f<N>().end()...); }
	INLINE           IL end() &      { return IL(f(), a<N>().end()...); }
	INLINE constexpr IC end() const& { return IC(f(), a<N>().end()...); }

};

//-----------------------------------------------------------------------------

template <typename M, typename F, typename... A>
class sequence <tag::apply, M, F, A...> :
	public apply_seq_impl <M, F, pack <A...> >
{
	using B = apply_seq_impl <M, F, pack <A...> >;

public:
	using B::B;
	using B::base_type::operator=;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_VIEW_APPLY_HPP
