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

#ifndef IVL_CORE_TYPE_CONST_ARRAY_HPP
#define IVL_CORE_TYPE_CONST_ARRAY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

template <typename T, T... N>
class constant <tag::int_array, non_type <T, N...> > :
	public seq <sizeof...(N)>,
	public details::const_base <const T(&)[sizeof...(N)], c_int_array <T, N...> >
{
	using V = value_type_of <constant>;

	class store
	{
		T a[sizeof...(N)];
	public:
		INLINE store() : a{N...} { }
		static INLINE V data() { static store s; return s.a; }
	};

public:
	INLINE constexpr operator V() const { return store::data(); }
};

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <template <typename...> class C, typename T, typename... A>
class c_array_cons :
	public seq <sizeof...(A)>,
	public const_base <const T(&)[sizeof...(A)], c_array_cons <C, T, A...> >
{
	using V = value_type_of <c_array_cons>;

	class store
	{
		T a[sizeof...(A)];
	public:
		INLINE store() : a{embed <C, cons <T, A> >()...} { }
		static INLINE V data() { static store s; return s.a; }
	};

public:
	INLINE constexpr operator V() const { return store::data(); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename T, typename... A>
struct constant <tag::array, T, A...> :
	details::c_array_cons <c_cons, T, A...> { };

template <typename T, typename... A>
struct constant <tag::array_list, T, A...> :
	details::c_array_cons <c_cons_list, T, A...> { };

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CONST_ARRAY_HPP
