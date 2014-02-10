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
using apply_ref = seq_ret <decltype(gen <F>()(*gen <A>().begin()...))>;

template <typename T, typename F, typename A>
using apply_types_impl =
	seq_types <T, A, apply_iter, apply_trav, seq_size <A>, F>;

template <typename F, typename... A>
using apply_types = apply_types_impl <apply_ref <F, A...>, F, pack <A...> >;

// extending definition @array/base/base
template <typename F, typename... A>
struct seq_data_t <apply_seq <F, A...> > : id_t <raw_tuple <F, A...> > { };

//-----------------------------------------------------------------------------

template <typename F, typename A, typename N = sz_rng_of_p <A> >
struct apply_seq_impl;

template <typename F, typename... A, size_t... N>
class apply_seq_impl <F, pack <A...>, sizes <N...> > :
	public base_seq <apply_seq <F, A...>, apply_types <F, A...> >,
	seq_data <apply_seq <F, A...> >
{
	using AP = pack <A...>;
	using ST = apply_types <F, A...>;
	friend base_seq <apply_seq <F, A...>, ST>;

	using S = seq_size <ST>;

	using IR = r_iter <ST>;
	using IL = l_iter <ST>;
	using IC = c_iter <ST>;

	using VR = r_trav <ST>;
	using VL = l_trav <ST>;
	using VC = c_trav <ST>;

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

	INLINE constexpr S size() const { return val_min(a<N>().size()...); }

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

template <typename F, typename... A>
struct sequence <data::apply <>, F, A...> : apply_seq_impl <F, pack <A...> >
{
	using apply_seq_impl <F, pack <A...> >::apply_seq_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_VIEW_APPLY_HPP
