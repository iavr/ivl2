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

template <typename F, typename... A>
using apply_ref = seq_result <decltype(gen <F>()(*gen <A>().begin()...))>;

template <typename T, typename M, typename F, typename A>
using apply_traits_impl = seq_traits <
	T, A, apply_iter, apply_trav, seq_size <A>, M, F
>;

template <typename M, typename F, typename... A>
using apply_traits = apply_traits_impl <apply_ref <F, A...>, M, F, pack <A...> >;

// extending definition @array/base/base
template <typename M, typename F, typename... A>
struct seq_data_t <apply_seq <M, F, A...> > : id_t <raw_tuple <F, A...> > { };

//-----------------------------------------------------------------------------

template <typename M, typename F, typename A, typename N = sz_rng_of_p <A> >
struct apply_seq_impl;

template <typename M, typename F, typename... A, size_t... N>
class apply_seq_impl <M, F, pack <A...>, sizes <N...> > :
	public seq_base <apply_seq <M, F, A...>, apply_traits <M, F, A...> >,
	seq_data <apply_seq <M, F, A...> >
{
	using AP = pack <A...>;
	using TR = apply_traits <M, F, A...>;
	friend seq_base <apply_seq <M, F, A...>, TR>;

	using S = seq_size <TR>;

	using IR = r_iter <TR>;
	using IL = l_iter <TR>;
	using IC = c_iter <TR>;

	using VR = r_trav <TR>;
	using VL = l_trav <TR>;
	using VC = c_trav <TR>;

	using E = raw_tuple <F, A...>;
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
	INLINE r_pk <K, AP>
	a_f() { return arg <K>::fwd(); }

	template <size_t K>
	INLINE r_pk <K, AP>
	a() && { return arg <K>::fwd(); }

	template <size_t K>
	INLINE l_pk <K, AP>
	a() & { return arg <K>::get(); }

	template <size_t K>
	INLINE constexpr c_pk <K, AP>
	a() const& { return arg <K>::get(); }

//-----------------------------------------------------------------------------

public:
	using E::E;

	INLINE constexpr S size() const { return M().size(a<N>()...); }

	INLINE           IR begin() &&     { return IR(f_f(), a_f<N>().begin()...); }
	INLINE           IL begin() &      { return IL(f(),   a<N>().begin()...); }
	INLINE constexpr IC begin() const& { return IC(f(),   a<N>().begin()...); }

	INLINE           IR end() &&     { return IR(f_f(), a_f<N>().end()...); }
	INLINE           IL end() &      { return IL(f(),   a<N>().end()...); }
	INLINE constexpr IC end() const& { return IC(f(),   a<N>().end()...); }

	INLINE           VR trav() &&     { return VR(f_f(), a_f<N>().trav()...); }
	INLINE           VL trav() &      { return VL(f(),   a<N>().trav()...); }
	INLINE constexpr VC trav() const& { return VC(f(),   a<N>().trav()...); }

};

//-----------------------------------------------------------------------------

template <typename M, typename F, typename... A>
struct sequence <data::apply <>, M, F, A...> :
	apply_seq_impl <M, F, pack <A...> >
{
	using apply_seq_impl <M, F, pack <A...> >::apply_seq_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_VIEW_APPLY_HPP
