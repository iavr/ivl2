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

#ifndef IVL_CORE_ARRAY_VIEW_TAIL_HPP
#define IVL_CORE_ARRAY_VIEW_TAIL_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename U>
using tail_order = fixed_order <seq_fixed <U>{}, sizes <seq_len <U>{} - 1> >;

template <typename U>
using tail_traits = seq_traits <seq_type <U>, tail_order <U>, U, trav_trav>;

//-----------------------------------------------------------------------------

template <typename U, typename TR = tail_traits <U> >
class tail_seq_impl :
	public seq_base <tail_seq <U>, TR, U>
{
	using B = seq_base <tail_seq <U>, TR, U>;
	friend B;

	using S = seq_size <TR>;

	using IR = r_seq_iter <TR>;
	using IL = l_seq_iter <TR>;
	using IC = c_seq_iter <TR>;

	template <typename Q> using VR = r_seq_trav <TR, Q>;
	template <typename Q> using VL = l_seq_trav <TR, Q>;
	template <typename Q> using VC = c_seq_trav <TR, Q>;

	using under = elem <0, U>;

//-----------------------------------------------------------------------------

	INLINE           r_ref <U> u_f()      { return under::fwd(); }
	INLINE           r_ref <U> u() &&     { return under::fwd(); }
	INLINE           l_ref <U> u() &      { return under::get(); }
	INLINE constexpr c_ref <U> u() const& { return under::get(); }

//-----------------------------------------------------------------------------

	template <template <typename> class VT, typename Q, typename V>
	static INLINE constexpr VT <Q>
	t(V&& v) { return VT <Q>(++fwd <V>(v) >>= edge); }

//-----------------------------------------------------------------------------

	template <typename Q>
	INLINE VR <Q> _trav() && { return t <VR, Q>(u_f().trav(Q())); }

	template <typename Q>
	INLINE VL <Q> _trav() & { return t <VL, Q>(u().trav(Q())); }

	template <typename Q>
	INLINE VC <Q> _trav() const& { return t <VC, Q>(u().trav(Q())); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr S size() const { return u().size() - 1; }

	INLINE           IR begin() &&     { return IR(++u_f().begin()); }
	INLINE           IL begin() &      { return IL(++u().begin()); }
	INLINE constexpr IC begin() const& { return IC(++u().begin()); }

	INLINE           IR end() &&     { return IR(u_f().end()); }
	INLINE           IL end() &      { return IL(u().end()); }
	INLINE constexpr IC end() const& { return IC(u().end()); }

};

//-----------------------------------------------------------------------------

template <typename U>
class sequence <tag::tail, U> : public tail_seq_impl <U>
{
	using B = tail_seq_impl <U>;

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

#endif  // IVL_CORE_ARRAY_VIEW_TAIL_HPP
