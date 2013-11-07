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

#ifndef IVL_DETAILS_CORE_TUPLE_ELEM_HPP
#define IVL_DETAILS_CORE_TUPLE_ELEM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuple_details {

//-----------------------------------------------------------------------------

template <size_t I, typename E, bool = is_base_opt <E>()>
class elem
{
	E e;
	elem& operator=(const elem&) = delete;

public:
	INLINE constexpr elem(elem&& e) : e(e.fwd()) { }

	template <typename A, enable_if <is_cons <E, A>{}> = 0>
	explicit INLINE constexpr elem(A&& a) : e(ivl::fwd <A>(a)) { }

	template <typename A>
	INLINE elem& operator=(A&& a) { return e = ivl::fwd <A>(a), *this; }

	INLINE           E&&      fwd()         { return ivl::fwd <E>(e); }
	INLINE           E&&      get() &&      { return ivl::fwd <E>(e); }
	INLINE           E&       get() &       { return e; }
	INLINE constexpr const E& get() const&  { return e; }
};

//-----------------------------------------------------------------------------

template <size_t I, typename E>
class elem <I, E, true> : private E
{
	elem& operator=(const elem&) = delete;

public:
	INLINE constexpr elem(elem&& e) : E(e.fwd()) { }

	template <typename A, enable_if <is_cons <E, A>{}> = 0>
	explicit INLINE constexpr elem(A&& a) : E(ivl::fwd <A>(a)) { }

	template <typename A>
	INLINE elem& operator=(A&& a) { return E::operator=(ivl::fwd <A>(a)), *this; }

	INLINE           E&& fwd()        { return ivl::fwd <E>(*this); }
	INLINE           E&& get() &&     { return ivl::fwd <E>(*this); }
	INLINE           E   get() &      { return *this; }
	INLINE constexpr E   get() const& { return *this; }
};

//-----------------------------------------------------------------------------

}  // namespace tuple_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_ELEM_HPP
