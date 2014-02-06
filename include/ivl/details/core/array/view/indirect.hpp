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

#ifndef IVL_DETAILS_CORE_ARRAY_VIEW_INDIRECT_HPP
#define IVL_DETAILS_CORE_ARRAY_VIEW_INDIRECT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename K, typename U>
using indirect_types =
	seq_types <seq_val <U>, K, indirect_iter, indirect_trav, seq_size <K>, U>;

template <typename K, typename U>
struct seq_data_t <indirect_array <K, U> > : id_t <raw_tuple <K, U> > { };

//-----------------------------------------------------------------------------

template <typename K, typename U>
class sequence <data::indirect <>, K, U> :
	public base_seq <indirect_array <K, U>, indirect_types <K, U> >,
	seq_data <indirect_array <K, U> >
{
	friend base_seq <sequence, indirect_types <K, U> >;

	using ST = indirect_types <K, U>;

	using IR = r_iter <ST>;
	using IL = l_iter <ST>;
	using IC = cl_iter <ST>;

	using VR = r_trav <ST>;
	using VL = l_trav <ST>;
	using VC = cl_trav <ST>;

	using E = raw_tuple <K, U>;
	using idx   = elem <0, K>;
	using under = elem <1, U>;

//-----------------------------------------------------------------------------

	INLINE           r_ref <K>  i_f()      { return idx::fwd(); }
	INLINE           r_ref <K>  i() &&     { return idx::fwd(); }
	INLINE           l_ref <K>  i() &      { return idx::get(); }
	INLINE constexpr cl_ref <K> i() const& { return idx::get(); }

	INLINE           r_ref <U>  u_f()      { return under::fwd(); }
	INLINE           r_ref <U>  u() &&     { return under::fwd(); }
	INLINE           l_ref <U>  u() &      { return under::get(); }
	INLINE constexpr cl_ref <U> u() const& { return under::get(); }

//-----------------------------------------------------------------------------

public:
	using E::E;

	INLINE constexpr size_t size() const { return i().size(); }

	INLINE           IR begin() &&     { return IR(i_f().begin(), u_f()); }
	INLINE           IL begin() &      { return IL(i().begin(),   u()); }
	INLINE constexpr IC begin() const& { return IC(i().begin(),   u()); }

	INLINE           IR end() &&     { return IR(i_f().end(), u_f()); }
	INLINE           IL end() &      { return IL(i().end(),   u()); }
	INLINE constexpr IC end() const& { return IC(i().end(),   u()); }

	INLINE           VR trav() &&     { return VR(i_f().trav(), u_f()); }
	INLINE           VL trav() &      { return VL(i().trav(),   u()); }
	INLINE constexpr VC trav() const& { return VC(i().trav(),   u()); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_VIEW_INDIRECT_HPP
