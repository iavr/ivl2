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

#ifndef IVL_CORE_ARRAY_VIEW_INDIRECT_HPP
#define IVL_CORE_ARRAY_VIEW_INDIRECT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename K, typename U>
using indirect_traits = seq_traits <
	U(_type <seq_type <K> >), seq_order <K>, K,
	indirect_trav, id, seq_size <K>, U
>;

//-----------------------------------------------------------------------------

template <typename K, typename U, typename TR = indirect_traits <K, U> >
class indirect_seq_impl :
	public seq_base <indirect_seq <K, U>, TR, K, U>
{
	using B = seq_base <indirect_seq <K, U>, TR, K, U>;
	friend B;

	using S = seq_size <TR>;

	using IR = r_seq_iter <TR>;
	using IL = l_seq_iter <TR>;
	using IC = c_seq_iter <TR>;

	template <typename Q> using VR = r_seq_trav <TR, Q>;
	template <typename Q> using VL = l_seq_trav <TR, Q>;
	template <typename Q> using VC = c_seq_trav <TR, Q>;

	using idx   = elem <0, K>;
	using under = elem <1, U>;

//-----------------------------------------------------------------------------

	INLINE           r_ref <K> i_f()      { return idx::fwd(); }
	INLINE           r_ref <K> i() &&     { return idx::fwd(); }
	INLINE           l_ref <K> i() &      { return idx::get(); }
	INLINE constexpr c_ref <K> i() const& { return idx::get(); }

	INLINE           r_ref <U> u_f()      { return under::fwd(); }
	INLINE           r_ref <U> u() &&     { return under::fwd(); }
	INLINE           l_ref <U> u() &      { return under::get(); }
	INLINE constexpr c_ref <U> u() const& { return under::get(); }

//-----------------------------------------------------------------------------

	template <typename Q>
	INLINE VR <Q>
	_trav() && { return VR <Q>(i_f().trav(Q()), u_f()); }

	template <typename Q>
	INLINE VL <Q>
	_trav() & { return VL <Q>(i().trav(Q()), u()); }

	template <typename Q>
	INLINE constexpr VC <Q>
	_trav() const& { return VC <Q>(i().trav(Q()), u()); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr S size() const { return i().size(); }

	INLINE           IR begin() &&     { return IR(i_f().begin(), u_f()); }
	INLINE           IL begin() &      { return IL(i().begin(),   u()); }
	INLINE constexpr IC begin() const& { return IC(i().begin(),   u()); }

	INLINE           IR end() &&     { return IR(i_f().end(), u_f()); }
	INLINE           IL end() &      { return IL(i().end(),   u()); }
	INLINE constexpr IC end() const& { return IC(i().end(),   u()); }

};

//-----------------------------------------------------------------------------

template <typename K, typename U>
class sequence <tag::indirect, K, U> : public indirect_seq_impl <K, U>
{
	using B = indirect_seq_impl <K, U>;

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

#endif  // IVL_CORE_ARRAY_VIEW_INDIRECT_HPP
