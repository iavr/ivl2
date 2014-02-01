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

#ifndef IVL_DETAILS_CORE_ARRAY_STORE_FIXED_HPP
#define IVL_DETAILS_CORE_ARRAY_STORE_FIXED_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, size_t N>
class sequence <T, data::fixed <sizes <N> > >
{
public:
	using value_type = T;

// 	template <typename A = int, only_if <_and <is_cons <E>...>{}, A> = 0>
// 	explicit INLINE constexpr sequence() : B(yes) { }
//
// 	template <typename... A, only_if <tup_conv <pack <A...>, P>{}> = 0>
// 	INLINE constexpr sequence(A&&... a) : B(yes, fwd <A>(a)...) { }
//
// 	template <typename... A, only_if <tup_explicit <P, pack <A...> >{}> = 0>
// 	explicit INLINE constexpr sequence(A&&... a) : B(yes, fwd <A>(a)...) { }
//
// 	template <typename T, only_if <tup_tup_conv <T, P>{}> = 0>
// 	INLINE constexpr sequence(T&& t) : B(fwd <T>(t)) { }
//
// 	template <typename T, only_if <tup_tup_explicit <P, T>{}> = 0>
// 	explicit INLINE constexpr sequence(T&& t) : B(fwd <T>(t)) { }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_STORE_FIXED_HPP
