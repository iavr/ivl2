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

#ifndef IVL_DETAILS_CORE_ATOM_BASE_HPP
#define IVL_DETAILS_CORE_ATOM_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace atoms {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename P>
struct base_atom;

//-----------------------------------------------------------------------------

template <typename D, typename E>
class base_atom <D, _type <E> > :
	public elem_store <pack <elem <0, E> > >, public derived <D>
{
	using P = _type <E>;
	using U = elem_at <0, E>;
	using B = elem_store <pack <U> >;

//-----------------------------------------------------------------------------

public:
	using base_type = base_atom;
	using type = P;
	static constexpr size_t length = 1;

	using B::B;

//-----------------------------------------------------------------------------

public:
	INLINE           rtref <E>  val_f()      { return U::fwd(); }
	INLINE           rtref <E>  val() &&     { return U::fwd(); }
	INLINE           ltref <E>  val() &      { return U::get(); }
	INLINE constexpr cltref <E> val() const& { return U::get(); }

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE rtref <E> at() && { return U::fwd(); }

	template <size_t J>
	INLINE ltref <E> at() & { return U::get(); }

	template <size_t J>
	INLINE constexpr cltref <E> at() const& { return U::get(); }

};

//-----------------------------------------------------------------------------

}  // namespace details

using details::base_atom;

//-----------------------------------------------------------------------------

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ATOM_BASE_HPP