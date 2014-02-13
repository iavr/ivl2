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

#ifndef IVL_CORE_ATOM_BASE_TUPLE_HPP
#define IVL_CORE_ATOM_BASE_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {
namespace details {

// extending definition @tuple/type/collection
template <typename T, typename C>
struct tup_data_t <atoms::atom <T, C> > : pack <T> { };

}  // namespace tuples
}  // namespace details

//-----------------------------------------------------------------------------

namespace atoms {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename T>
class atom_base <D, T, data::tup <> > :
	public derived <D, data::tup <> >
{
	using DER = derived <D, data::tup <> >;
	using DER::der_f;
	using DER::der;

public:
	using type = _type <T>;
	static constexpr size_t length = 1;

//-----------------------------------------------------------------------------

	template <size_t J> INLINE r_ref <T> at() && { return der_f().val(); }
	template <size_t J> INLINE l_ref <T> at() &  { return der().val(); }

	template <size_t J>
	INLINE constexpr c_ref <T> at() const& { return der().val(); }

};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ATOM_BASE_TUPLE_HPP
