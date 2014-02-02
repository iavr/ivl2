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

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, size_t N>
struct fixed_store
{
	T a[N];

	INLINE T*       data()       { return a; }
	INLINE const T* data() const { return a; }
};

template <typename T>
struct fixed_store <T, 0>
{
	INLINE T*       data()       { return nullptr; }
	INLINE const T* data() const { return nullptr; }
};

//-----------------------------------------------------------------------------

template <typename T, size_t N>
class sequence <T, data::fixed <sizes <N> > > :
	public base_seq <T, sequence <T, data::fixed <sizes <N> > > >,
	private fixed_store <T, N>
{
	using S  = size_t;
	using R  = T&;
	using CR = const T&;
	using P  = T*;
	using CP = const T*;
	using I  = T*;
	using CI = const T*;

	using D = fixed_store <T, N>;
	using D::data;

	using B = base_seq <T, sequence>;
	friend B;

//-----------------------------------------------------------------------------

	INLINE           R  _at(S n)       { return data()[n]; }
	INLINE constexpr CR _at(S n) const { return data()[n]; }

//-----------------------------------------------------------------------------

public:

	INLINE constexpr size_t size()     const { return N; }
	INLINE constexpr size_t max_size() const { return N; }
	INLINE constexpr bool   empty()    const { return N == 0; }

	INLINE I  begin()       { return data(); }
	INLINE CI begin() const { return data(); }
	INLINE I  end()         { return data() + N; }
	INLINE CI end()   const { return data() + N; }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_STORE_FIXED_HPP
