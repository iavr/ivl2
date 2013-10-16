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
	inline constexpr elem() : e() { }
	inline constexpr elem(elem&& e) : e(mv(e).get()) { }
	inline constexpr elem(const elem& e) : e(e.get()) { }

	template <typename A, enable_if <is_cons <E, A>{}> = 0>
	explicit inline constexpr elem(A&& a) : e(fwd <A>(a)) { }

	template <typename A>
	inline elem& operator=(A&& a) { return e = fwd <A>(a), *this; }

	inline           E&&      get() &&      { return fwd <E>(e); }
	inline           E&       get() &       { return e; }
	inline constexpr const E& get() const&  { return e; }
};

//-----------------------------------------------------------------------------

template <size_t I, typename E>
class elem <I, E, true> : private E
{
	elem& operator=(const elem&) = delete;

public:
	inline constexpr elem() : E() { }
	inline constexpr elem(elem&& e) : E(mv(e).get()) { }
	inline constexpr elem(const elem& e) : E(e.get()) { }

	template <typename A, enable_if <is_cons <E, A>{}> = 0>
	explicit inline constexpr elem(A&& a) : E(fwd <A>(a)) { }

	template <typename A>
	inline elem& operator=(A&& a) { return E::operator=(fwd <A>(a)), *this; }

	inline           E&&      get() &&     { return fwd <E>(*this); }
	inline           E&       get() &      { return *this; }
	inline constexpr const E& get() const& { return *this; }
};

//-----------------------------------------------------------------------------

}  // namespace tuple_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_ELEM_HPP
