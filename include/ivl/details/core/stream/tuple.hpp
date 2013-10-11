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

#ifndef IVL_DETAILS_CORE_STREAM_TUPLE_HPP
#define IVL_DETAILS_CORE_STREAM_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuple_details {

using std::basic_ostream;

//-----------------------------------------------------------------------------

template <typename C, typename R, typename S, typename... A>
inline basic_ostream <C, R>&
operator<<(basic_ostream <C, R>& s, collection <S, A...>&& t)
{
	using T = collection <S, A...>;
	return s << "(",  loop[", "](out_stream(s), fwd <T>(t)),  s << ")";
}

template <typename C, typename R, typename S, typename... A>
inline basic_ostream <C, R>&
operator<<(basic_ostream <C, R>& s, const collection <S, A...>& t)
{
	return s << "(",  loop[", "](out_stream(s), t),  s << ")";
}

//-----------------------------------------------------------------------------

}  // namespace tuple_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_STREAM_TUPLE_HPP
