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

#ifndef IVL_CORE_ARRAY_STORE_FIXED_HPP
#define IVL_CORE_ARRAY_STORE_FIXED_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// extending definition @array/type/sequence
template <typename T, size_t N>
struct seq_data_t <fixed_array <T, N> > : pack <fixed_store <T, N> > { };

//-----------------------------------------------------------------------------

template <typename T, size_t N, typename I = sz_rng_of_i <N> >
struct fixed_impl;

template <typename T, size_t N, size_t... I>
class fixed_impl <T, N, sizes <I...> > :
	public pre_fixed_array <T, N>
{
	using B = pre_fixed_array <T, N>;

public:
	explicit INLINE constexpr fixed_impl(_true) : B() { }

	template <typename... A>
	explicit INLINE constexpr fixed_impl(_true, A&&... a) : B(fwd <A>(a)...) { }

	template <typename A>
	INLINE constexpr fixed_impl(A&& a) : B(fwd <A>(a)[I]...) { }
};

//-----------------------------------------------------------------------------

template <typename T, size_t N>
class sequence <tag::fixed, T, sizes <N> > :
	public fixed_impl <T, N>
{
	using B = fixed_impl <T, N>;

//-----------------------------------------------------------------------------

public:
	template <typename A = int, only_if <is_cons <T>{}, A> = 0>
	explicit INLINE constexpr sequence() : B(yes) { }

	template <typename... A, only_if <is_conv <common <A...>, T>{}> = 0>
	INLINE constexpr sequence(A&&... a) : B(yes, fwd <A>(a)...) { }

	template <typename... A, only_if <is_explicit <T, common <A...> >{}> = 0>
	explicit INLINE constexpr sequence(A&&... a) : B(yes, fwd <A>(a)...) { }

	template <typename A, only_if <seq_conv <A, T>{}> = 0>
	INLINE constexpr sequence(A&& a) : B(fwd <A>(a)) { }

	template <typename A, only_if <seq_explicit <T, A>{}> = 0>
	explicit INLINE constexpr sequence(A&& a) : B(fwd <A>(a)) { }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_STORE_FIXED_HPP
