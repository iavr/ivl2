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

#ifndef IVL_CORE_ARRAY_VIEW_FLIP_HPP
#define IVL_CORE_ARRAY_VIEW_FLIP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename U, typename T = seq_type <U> >
using flip_traits = seq_traits <
	T, seq_length <U>, U, flip_iter, flip_trav
>;

//-----------------------------------------------------------------------------

template <typename U, typename TR = flip_traits <U> >
class flip_seq_impl :
	public seq_base <flip_seq <U>, TR, U>
{
	using B = seq_base <flip_seq <U>, TR, U>;
	friend B;

	using S = seq_size <TR>;

	using IR = r_iter <TR>;
	using IL = l_iter <TR>;
	using IC = c_iter <TR>;

	using VR = r_trav <TR>;
	using VL = l_trav <TR>;
	using VC = c_trav <TR>;

	using under = elem <0, U>;

//-----------------------------------------------------------------------------

	INLINE           r_ref <U> u_f()      { return under::fwd(); }
	INLINE           r_ref <U> u() &&     { return under::fwd(); }
	INLINE           l_ref <U> u() &      { return under::get(); }
	INLINE constexpr c_ref <U> u() const& { return under::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr S size() const { return u().size(); }

	INLINE           IR begin() &&     { return IR(--u_f().end()); }
	INLINE           IL begin() &      { return IL(--u().end()); }
	INLINE constexpr IC begin() const& { return IC(--u().end()); }

	INLINE           IR end() &&     { return IR(--u_f().begin()); }
	INLINE           IL end() &      { return IL(--u().begin()); }
	INLINE constexpr IC end() const& { return IC(--u().begin()); }

	INLINE           VR trav() &&     { return VR(mv(-u_f().trav())); }
	INLINE           VL trav() &      { return VL((-u().trav())); }
	INLINE           VC trav() const& { return VC((-u().trav())); }
};

//-----------------------------------------------------------------------------

template <typename U>
struct sequence <data::flip <>, U> : flip_seq_impl <U>
{
	using flip_seq_impl <U>::flip_seq_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_VIEW_FLIP_HPP
