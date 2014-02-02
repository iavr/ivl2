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

#ifndef IVL_DETAILS_CORE_ARRAY_VIEW_INDIRECT_HPP
#define IVL_DETAILS_CORE_ARRAY_VIEW_INDIRECT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename K, typename U>
class sequence <T, data::indirect <K, U> > :
	public base_seq <T, sequence <T, data::indirect <K, U> > >,
	private raw_tuple <K, U>
{
// 	using S  = size_t;
// 	using R  = T&;
// 	using CR = const T&;
// 	using P  = T*;
// 	using CP = const T*;
// 	using I  = indirect_iter <T, K, U>;
// 	using CI = indirect_iter <const T, K, U>;
//
// 	using B = base_seq <T, sequence>;
// 	friend B;
//
// //-----------------------------------------------------------------------------
//
// 	INLINE           R  _at(S n)       { return data()[n]; }
// 	INLINE constexpr CR _at(S n) const { return data()[n]; }
//
// //-----------------------------------------------------------------------------
//
// public:
//
// 	INLINE constexpr size_t size()     const { return N; }
// 	INLINE constexpr size_t max_size() const { return N; }
// 	INLINE constexpr bool   empty()    const { return N == 0; }
//
// 	INLINE I  begin()       { return data(); }
// 	INLINE CI begin() const { return data(); }
// 	INLINE I  end()         { return data() + N; }
// 	INLINE CI end()   const { return data() + N; }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_VIEW_INDIRECT_HPP
