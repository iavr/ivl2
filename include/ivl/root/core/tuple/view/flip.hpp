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

#ifndef IVL_CORE_TUPLE_VIEW_FLIP_HPP
#define IVL_CORE_TUPLE_VIEW_FLIP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename U>
class collection <data::flip <>, U> : public
	tup_base <flip_tup <U>, flip_p <tup_types <U> > >
{
	using P = flip_p <tup_types <U> >;
	using B = tup_base <flip_tup <U>, P>;
	using E = elem <0, U>;

	friend base_type_of <B>;

	static constexpr size_t M = P::length - 1;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE r_pick_p <J, P>
	call_at() && { return _at._<M - J>(E::fwd()); }

	template <size_t J>
	INLINE l_pick_p <J, P>
	call_at() & { return _at._<M - J>(E::get()); }

	template <size_t J>
	INLINE constexpr c_pick_p <J, P>
	call_at() const& { return _at._<M - J>(E::get()); }

//-----------------------------------------------------------------------------

public:
	using B::B;
	using B::base_type::operator=;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_VIEW_FLIP_HPP
