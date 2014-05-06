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

#ifndef IVL_CORE_TYPE_CORE_ID_HPP
#define IVL_CORE_TYPE_CORE_ID_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

class type_id_t
{
	using S = type_id_t();

	template <typename T>
	friend type_id_t type_id();
	friend std::hash <type_id_t>;

//-----------------------------------------------------------------------------

	S* id;
	INLINE type_id_t(S* id) : id{id} { }

	INLINE size_t hash() { return std::hash <S*>()(id); }

public:
	INLINE bool operator==(type_id_t o) const { return id == o.id; }
	INLINE bool operator!=(type_id_t o) const { return id != o.id; }
	INLINE bool operator< (type_id_t o) const { return id <  o.id; }
	INLINE bool operator> (type_id_t o) const { return id >  o.id; }
	INLINE bool operator<=(type_id_t o) const { return id <= o.id; }
	INLINE bool operator>=(type_id_t o) const { return id >= o.id; }
};

template <typename T>
type_id_t type_id() { return type_id <T>; }

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

using types::type_id_t;
using types::type_id;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

namespace std {

//-----------------------------------------------------------------------------

template <>
struct hash <ivl::type_id_t>
{
	size_t operator()(ivl::type_id_t x) const { return x.hash(); }
};

//-----------------------------------------------------------------------------

}  // namespace std

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CORE_ID_HPP
