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

#ifndef IVL_DETAILS_CORE_USCORE_USCORE_HPP
#define IVL_DETAILS_CORE_USCORE_USCORE_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace uscore_details {

//-----------------------------------------------------------------------------

class uscore : public afun::rref
{
	template <typename A> using R = fun_atom <base_opt <A&&> >;

public:
	template <typename A>
	INLINE constexpr R <A>
	operator[](A&& a) const { return R <A>(fwd <A>(a)); }
};

//-----------------------------------------------------------------------------

}  // namespace uscore_details

using uscore_details::uscore;

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) uscore _;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_USCORE_USCORE_HPP
