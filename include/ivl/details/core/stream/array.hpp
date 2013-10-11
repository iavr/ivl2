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

#ifndef IVL_DETAILS_CORE_STREAM_ARRAY_HPP
#define IVL_DETAILS_CORE_STREAM_ARRAY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace array_details {

using std::basic_ostream;

//-----------------------------------------------------------------------------

template <typename C, typename R, typename T, typename S>
inline basic_ostream <C, R>&
operator<<(basic_ostream <C, R>& s, array <T, S>&& a)
{
	using A = array <T, S>;
	return s << "[ ",  loop[" "](out_stream(s), fwd <A>(a)),  s << " ]";
}

template <typename C, typename R, typename T, typename S>
inline basic_ostream <C, R>&
operator<<(basic_ostream <C, R>& s, const array <T, S>& a)
{
	return s << "[ ",  loop[" "](out_stream(s), a),  s << " ]";
}

//-----------------------------------------------------------------------------

}  // namespace array_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_STREAM_ARRAY_HPP
