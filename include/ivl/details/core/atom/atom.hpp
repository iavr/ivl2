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

#ifndef IVL_DETAILS_CORE_ATOM_ATOM_HPP
#define IVL_DETAILS_CORE_ATOM_ATOM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace atom_details {

//-----------------------------------------------------------------------------

template <typename A>
class store : public base_tup <atom <A>, _type <A> >
{
	using P = _type <A>;
	using B = base_type_of <store>;
	friend B;
	A a;

//-----------------------------------------------------------------------------

	template <size_t J> inline A&& _at() && { return fwd <A>(a); }
	template <size_t J> inline A&  _at() &  { return a; }
	template <size_t J> inline constexpr const A& _at() const& { return a; }

//-----------------------------------------------------------------------------

public:
	using B::operator=;

	template <typename T, enable_if <is_conv <T, A>{}> = 0>
	inline constexpr store(T&& a) : a(fwd <T>(a)) { }

	template <typename T, enable_if <is_explicit <A, T>{}> = 0>
	explicit inline constexpr store(T&& a) : a(fwd <T>(a)) { }
};

//-----------------------------------------------------------------------------

template <typename A>
class atom : public store <A>
{
	using B = store <A>;

public:
	using B::B;
};

//-----------------------------------------------------------------------------

}  // namespace atom_details

using atom_details::atom;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ATOM_ATOM_HPP
