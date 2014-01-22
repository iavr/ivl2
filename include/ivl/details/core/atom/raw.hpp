/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   T C++ template library extending syntax towards mathematical notation.

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
   MERCHANTABILITY or FITNESS FOR T PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_DETAILS_CORE_ATOM_RAW_HPP
#define IVL_DETAILS_CORE_ATOM_RAW_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace atoms {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T>
class atom <T, data::raw <> > : public access <raw_atom <T>, T>
{
	using P = _type <T>;
	using B = access <raw_atom <T>, T>;
	using U = elem_at <0, T>;

//-----------------------------------------------------------------------------

public:
	using type = P;
	static constexpr size_t length = P::length;

	using B::B;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE rtref <T> at() && { return U::fwd(); }

	template <size_t J>
	INLINE ltref <T> at() & { return U::get(); }

	template <size_t J>
	INLINE constexpr cltref <T> at() const& { return U::get(); }

};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ATOM_RAW_HPP
