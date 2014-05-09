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

#ifndef IVL_CORE_ARRAY_VIEW_IOTA_HPP
#define IVL_CORE_ARRAY_VIEW_IOTA_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename N>
using iota_ord = size <N{}>;

template <typename T, typename O, bool F>
using iota_traits_base = id_t <seq_traits <
	id_t <T>, O, _type <T>, iota_trav, id, size_t, expr <F>
> >;

template <typename... N> struct iota_traits_t;
template <typename... N> using  iota_traits = type_of <iota_traits_t <N...> >;

template <>
struct iota_traits_t <> : iota_traits_base <size_t, none, false> { };

template <typename N>
struct iota_traits_t <N> : iota_traits_base <
	copy <const_value <N> >, const_map <iota_ord, N>, true
> { };

//-----------------------------------------------------------------------------

template <typename... N>
struct iota_store;

template <>
struct iota_store <>
{
protected:
	template <typename V, typename I>
	INLINE constexpr V t(I&& i) const& { return V(); }
};

//-----------------------------------------------------------------------------

template <typename N>
struct iota_store <N> : raw_tuple <N>
{
	using TR = iota_traits <N>;
	using T = raw_tuple <N>;
	using S = seq_size <TR>;

//-----------------------------------------------------------------------------

	using count = elem <0, N>;

protected:
	INLINE           r_ref <N> n_f()      { return count::fwd(); }
	INLINE           r_ref <N> n() &&     { return count::fwd(); }
	INLINE           l_ref <N> n() &      { return count::get(); }
	INLINE constexpr c_ref <N> n() const& { return count::get(); }

	template <typename V, typename I>
	INLINE constexpr V
	t(I&& i) const& { return V(fwd <I>(i).n()); }

//-----------------------------------------------------------------------------

public:
	using T::T;

	INLINE constexpr S size() const { return n(); }
};

//-----------------------------------------------------------------------------

// extending definition @array/type/sequence
template <typename... N>
struct seq_data_t <iota_seq <N...> > : pack <iota_store <N...> > { };

//-----------------------------------------------------------------------------

template <
	typename P,
	typename I = embed <iota_store, P>,
	typename D = embed <iota_seq, P>,
	typename TR = embed <iota_traits, P>
>
class iota_seq_impl :
	public based <I>,
	public seq_base <D, TR>
{
	using C = based <I>;
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
	INLINE VR <Q> _trav() && { return I::template t <VR <Q> >(base_f()); }

	template <typename Q>
	INLINE VL <Q> _trav() & { return I::template t <VL <Q> >(base()); }

	template <typename Q>
	INLINE constexpr VC <Q>
	_trav() const& { return I::template t <VC <Q> >(base()); }

//-----------------------------------------------------------------------------

protected:
	using base_type = base_type_of <B>;

//-----------------------------------------------------------------------------

public:
	using C::C;

	INLINE           IR begin() &&     { return IR(); }
	INLINE           IL begin() &      { return IL(); }
	INLINE constexpr IC begin() const& { return IC(); }

	INLINE           IR end() &&     { return IR(I::n_f()); }
	INLINE           IL end() &      { return IL(I::n()); }
	INLINE constexpr IC end() const& { return IC(I::n()); }
};

//-----------------------------------------------------------------------------

template <typename... N>
class sequence <tag::iota, N...> :
	public iota_seq_impl <pack <N...> >
{
	using B = iota_seq_impl <pack <N...> >;

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

#endif  // IVL_CORE_ARRAY_VIEW_IOTA_HPP
