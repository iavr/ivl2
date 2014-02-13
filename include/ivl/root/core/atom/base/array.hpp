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

#ifndef IVL_CORE_ATOM_BASE_ARRAY_HPP
#define IVL_CORE_ATOM_BASE_ARRAY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {
namespace details {

// extending definition @array/base/base
template <typename T, typename C>
struct seq_data_t <atoms::atom <T, C> > : id_t <T> { };

}  // namespace details
}  // namespace arrays

//-----------------------------------------------------------------------------

namespace atoms {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename P = remove_ref <T>*>
using atom_types = seq_types <
	r_ref <T>, P, atom_iter, atom_trav, seq_size <P>
>;

//-----------------------------------------------------------------------------

template <typename D, typename T>
class atom_base <D, T, data::seq <> > :
	public derived <D, data::seq <> >,
	public atom_types <T>
{
	using DER = derived <D, data::seq <> >;
	using DER::der_f;
	using DER::der;

	using ST = atom_types <T>;
	using S  = seq_size <ST>;

	using IR = r_iter <ST>;
	using IL = l_iter <ST>;
	using IC = c_iter <ST>;

	using VR = r_trav <ST>;
	using VL = l_trav <ST>;
	using VC = c_trav <ST>;

//-----------------------------------------------------------------------------

public:
	INLINE constexpr S size() const { return 1; }

	INLINE           IR begin() &&     { return IR(der_f().val()); }
	INLINE           IL begin() &      { return IL(der().val()); }
	INLINE constexpr IC begin() const& { return IC(der().val()); }

	INLINE           IR end() &&     { return IR(der_f().val()); }
	INLINE           IL end() &      { return IL(der().val()); }
	INLINE constexpr IC end() const& { return IC(der().val()); }

	INLINE           VR trav() &&     { return VR(der_f().val()); }
	INLINE           VL trav() &      { return VL(der().val()); }
	INLINE constexpr VC trav() const& { return VC(der().val()); }

};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ATOM_BASE_ARRAY_HPP
