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

#ifndef IVL_CORE_TUPLE_BASE_ELEM_HPP
#define IVL_CORE_TUPLE_BASE_ELEM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	size_t I, typename E,
	bool = is_base_opt <E>(), bool C = is_cons <E>()
>
class elem
{
	E e;

public:
	template <typename A = int, only_if <C, A> = 0>
	INLINE constexpr elem() : e() { }

	template <typename A>
	explicit INLINE constexpr elem(A&& a) : e(ivl::fwd <A>(a)) { }

	INLINE           E&&      fwd()         { return ivl::fwd <E>(e); }
	INLINE           E&&      get() &&      { return ivl::fwd <E>(e); }
	INLINE           E&       get() &       { return e; }
	INLINE constexpr const E& get() const&  { return e; }
};

//-----------------------------------------------------------------------------

template <size_t I, typename E>
struct elem <I, E, true, false> : private E
{
	template <typename A>
	explicit INLINE constexpr elem(A&& a) : E(ivl::fwd <A>(a)) { }

	INLINE           E fwd()        { return mv(*this); }
	INLINE           E get() &&     { return mv(*this); }
	INLINE           E get() &      { return *this; }
	INLINE constexpr E get() const& { return *this; }
};

//-----------------------------------------------------------------------------

template <size_t I, typename E>
struct elem <I, E, true, true>
{
	INLINE constexpr elem() { }

	template <typename A>
	explicit INLINE constexpr elem(A&& a) { }

	INLINE           E fwd()        { return E(); }
	INLINE           E get() &&     { return E(); }
	INLINE           E get() &      { return E(); }
	INLINE constexpr E get() const& { return E(); }
};

//-----------------------------------------------------------------------------

template <size_t J, typename... E>
using elem_at = elem <J, pick <J, E...> >;

//-----------------------------------------------------------------------------

}  // namespace details

using details::elem;
using details::elem_at;

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_BASE_ELEM_HPP
