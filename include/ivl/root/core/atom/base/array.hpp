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
struct seq_data_t <atoms::atom <T, C> > : pack <T> { };

}  // namespace details
}  // namespace arrays

//-----------------------------------------------------------------------------

namespace atoms {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename R = rref_opt <T> >
using atom_traits = seq_traits <R, no_size, _type <R>, atom_iter, atom_trav>;

//-----------------------------------------------------------------------------

template <typename T, typename b>
class atom_base <T, data::seq <>, b> :
	public seq_store <atom_traits <T>, pack <b> >
{
	using TR = atom_traits <T>;
	using B  = seq_store <TR, pack <b> >;
	using S  = seq_size <TR>;

	using IR = r_iter <TR>;
	using IL = l_iter <TR>;
	using IC = c_iter <TR>;

	using VR = r_trav <TR>;
	using VL = l_trav <TR>;
	using VC = c_trav <TR>;

//-----------------------------------------------------------------------------

public:
	using B::B;
	using B::val_f;
	using B::val;

	INLINE constexpr S size() const { return 1; }

	INLINE           IR begin() &&     { return IR(val_f()); }
	INLINE           IL begin() &      { return IL(val()); }
	INLINE constexpr IC begin() const& { return IC(val()); }

	INLINE           IR end() &&     { return IR(val_f()); }
	INLINE           IL end() &      { return IL(val()); }
	INLINE constexpr IC end() const& { return IC(val()); }

//-----------------------------------------------------------------------------

	template <typename... G>
	INLINE VR trav(G...) && { return VR(val_f()); }

	template <typename... G>
	INLINE VL trav(G...) & { return VL(val()); }

	template <typename... G>
	INLINE constexpr VC trav(G...) const& { return VC(val()); }

};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ATOM_BASE_ARRAY_HPP
