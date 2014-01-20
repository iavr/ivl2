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

#ifndef IVL_DETAILS_CORE_TUPLE_VIEW_INDIRECT_HPP
#define IVL_DETAILS_CORE_TUPLE_VIEW_INDIRECT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename K, typename U>
class collection <data::indirect <>, K, U> : public
	base_tup <indirect_tup <K, U>, choose_p <K, tup_types <U> > >
{
	using P = choose_p <K, tup_types <U> >;
	using B = base_tup <indirect_tup <K, U>, P>;
	using E = elem <0, U>;

	template <size_t J> using off = pick_i <J, K>;

	friend base_type_of <B>;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE rtel <J, P>
	ref_at() && { return _at._<off <J>{}>(E::fwd()); }

	template <size_t J>
	INLINE ltel <J, P>
	ref_at() & { return _at._<off <J>{}>(E::get()); }

	template <size_t J>
	INLINE constexpr cltel <J, P>
	ref_at() const& { return _at._<off <J>{}>(E::get()); }

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

#endif  // IVL_DETAILS_CORE_TUPLE_VIEW_INDIRECT_HPP
