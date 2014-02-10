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

#ifndef IVL_CORE_ATOM_STORE_BASE_HPP
#define IVL_CORE_ATOM_STORE_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {
namespace details {

// extending definition @array/base/base
template <typename T, typename S>
struct seq_data_t <atoms::atom <T, S> > : id_t <T> { };

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
class base_atom :
	public elem_store <elem <0, T> >, public derived <D>,
	public atom_types <T>
{
//-----------------------------------------------------------------------------
// tuple interface
//-----------------------------------------------------------------------------

	using U = elem <0, T>;
	using B = elem_store <U>;

public:
	using type = _type <T>;
	static constexpr size_t length = 1;

	using B::B;

//-----------------------------------------------------------------------------

public:
	INLINE           r_ref <T> val_f()      { return U::fwd(); }
	INLINE           r_ref <T> val() &&     { return U::fwd(); }
	INLINE           l_ref <T> val() &      { return U::get(); }
	INLINE constexpr c_ref <T> val() const& { return U::get(); }

//-----------------------------------------------------------------------------

	template <size_t J> INLINE r_ref <T> at() && { return U::fwd(); }
	template <size_t J> INLINE l_ref <T> at() &  { return U::get(); }

	template <size_t J>
	INLINE constexpr c_ref <T> at() const& { return U::get(); }

//-----------------------------------------------------------------------------
// sequence interface
//-----------------------------------------------------------------------------

private:
	using ST = atom_types <T>;
	using S  = seq_size <ST>;

	using VR = r_trav <ST>;
	using VL = l_trav <ST>;
	using VC = c_trav <ST>;

//-----------------------------------------------------------------------------

public:
	INLINE constexpr S size() const { return 1; }

	INLINE           VR trav() &&     { return VR(U::fwd()); }
	INLINE           VL trav() &      { return VL(U::get()); }
	INLINE constexpr VC trav() const& { return VC(U::get()); }

};

//-----------------------------------------------------------------------------

}  // namespace details

using details::base_atom;

//-----------------------------------------------------------------------------

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ATOM_STORE_BASE_HPP
