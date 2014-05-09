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

#ifndef IVL_CORE_ARRAY_VIEW_SLICE_HPP
#define IVL_CORE_ARRAY_VIEW_SLICE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename B, typename U, typename... N>
using slice_traits = seq_traits <
	id_t <copy <const_value <B> > >, seq_order <iota_traits <N...> >,
	pack <range_seq <B, U>, iota_seq <N...> >,
	slice_trav, id, size_t
>;

//-----------------------------------------------------------------------------

template <typename B, typename U, typename... N>
struct slice_store;

template <typename B, typename U>
struct slice_store <B, U> : raw_tuple <B, U>
{
	using T = raw_tuple <B, U>;

//-----------------------------------------------------------------------------

	using begin = elem <0, B>;
	using delta = elem <1, U>;

protected:
	INLINE           r_ref <B> b_f()      { return begin::fwd(); }
	INLINE           r_ref <B> b() &&     { return begin::fwd(); }
	INLINE           l_ref <B> b() &      { return begin::get(); }
	INLINE constexpr c_ref <B> b() const& { return begin::get(); }

	INLINE           r_ref <U> u_f()      { return delta::fwd(); }
	INLINE           r_ref <U> u() &&     { return delta::fwd(); }
	INLINE           l_ref <U> u() &      { return delta::get(); }
	INLINE constexpr c_ref <U> u() const& { return delta::get(); }

	template <typename V, typename S>
	INLINE constexpr V t(S&& s) const&
		{ return V(fwd <S>(s).u(), fwd <S>(s).b()); }

//-----------------------------------------------------------------------------

public:
	using T::T;
};

//-----------------------------------------------------------------------------

template <typename B, typename U, typename N>
struct slice_store <B, U, N> : raw_tuple <B, U, N>
{
	using TR = slice_traits <B, U, N>;
	using T = raw_tuple <B, U, N>;
	using S = seq_size <TR>;

//-----------------------------------------------------------------------------

	using begin = elem <0, B>;
	using delta = elem <1, U>;
	using count = elem <2, N>;

protected:
	INLINE           r_ref <B> b_f()      { return begin::fwd(); }
	INLINE           r_ref <B> b() &&     { return begin::fwd(); }
	INLINE           l_ref <B> b() &      { return begin::get(); }
	INLINE constexpr c_ref <B> b() const& { return begin::get(); }

	INLINE           r_ref <U> u_f()      { return delta::fwd(); }
	INLINE           r_ref <U> u() &&     { return delta::fwd(); }
	INLINE           l_ref <U> u() &      { return delta::get(); }
	INLINE constexpr c_ref <U> u() const& { return delta::get(); }

	INLINE           r_ref <N> n_f()      { return count::fwd(); }
	INLINE           r_ref <N> n() &&     { return count::fwd(); }
	INLINE           l_ref <N> n() &      { return count::get(); }
	INLINE constexpr c_ref <N> n() const& { return count::get(); }

	template <typename V, typename S>
	INLINE constexpr V
	t(S&& s) const&
		{ return V(fwd <S>(s).u(), fwd <S>(s).b(), fwd <S>(s).n()); }

//-----------------------------------------------------------------------------

public:
	using T::T;

	INLINE constexpr S size() const { return n(); }
};

//-----------------------------------------------------------------------------

// extending definition @array/type/sequence
template <typename B, typename U, typename... N>
struct seq_data_t <slice_seq <B, U, N...> > :
	pack <slice_store <B, U, N...> > { };

//-----------------------------------------------------------------------------

template <
	typename P,
	typename S = embed <slice_store, P>,
	typename D = embed <slice_seq, P>,
	typename TR = embed <slice_traits, P>
>
class slice_seq_impl :
	public based <S>,
	public seq_base <D, TR>
{
	using C = based <S>;
	using B = seq_base <D, TR>;
	friend B;

	using IR = r_seq_iter <TR>;
	using IL = l_seq_iter <TR>;
	using IC = c_seq_iter <TR>;

	template <typename Q> using VR = r_seq_trav <TR, Q>;
	template <typename Q> using VL = l_seq_trav <TR, Q>;
	template <typename Q> using VC = c_seq_trav <TR, Q>;

	using C::base_f;
	using C::base;

//-----------------------------------------------------------------------------

	template <typename Q>
	INLINE VR <Q> _trav() && { return S::template t <VR <Q> >(base_f()); }

	template <typename Q>
	INLINE VL <Q> _trav() & { return S::template t <VL <Q> >(base()); }

	template <typename Q>
	INLINE constexpr VC <Q>
	_trav() const& { return S::template t <VC <Q> >(base()); }

//-----------------------------------------------------------------------------

protected:
	using base_type = base_type_of <B>;

//-----------------------------------------------------------------------------

public:
	using C::C;

	INLINE           IR begin() &&     { return IR(S::u_f(), S::b_f()); }
	INLINE           IL begin() &      { return IL(S::u(),   S::b()); }
	INLINE constexpr IC begin() const& { return IC(S::u(),   S::b()); }

	INLINE           IR end() &&     { return IR(S::u_f(), S::b_f(), S::n_f()); }
	INLINE           IL end() &      { return IL(S::u(),   S::b(),   S::n()); }
	INLINE constexpr IC end() const& { return IC(S::u(),   S::b(),   S::n()); }
};

//-----------------------------------------------------------------------------

template <typename _B, typename U, typename... N>
class sequence <tag::slice, _B, U, N...> :
	public slice_seq_impl <pack <_B, U, N...> >
{
	using B = slice_seq_impl <pack <_B, U, N...> >;

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

#endif  // IVL_CORE_ARRAY_VIEW_SLICE_HPP
