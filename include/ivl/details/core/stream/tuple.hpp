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

#ifndef IVL_CORE_STREAM_TUPLE_HPP
#define IVL_CORE_STREAM_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename S, typename T,
	only_if <is_stream <S>() && is_tuple <T>()>
= 0>
INLINE S&&
operator<<(S&& s, T&& t)
{
	return
		fwd <S>(s) << "(",
		loop[", "](bind_left(fwd <S>(s)), fwd <T>(t)),
		fwd <S>(s) << ")";
}

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_STREAM_TUPLE_HPP
