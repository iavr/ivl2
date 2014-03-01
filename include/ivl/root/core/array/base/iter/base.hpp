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

#ifndef IVL_CORE_ARRAY_BASE_ITER_BASE_HPP
#define IVL_CORE_ARRAY_BASE_ITER_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename... E>
class iter_common : public derived <D>, public iter_store <TR, E...>
{
	using R = seq_iref <TR>;
	using T = seq_type <TR>;
	using d = seq_diff <TR>;
	using P = seq_iptr <TR>;

protected:
	template <typename A>
	INLINE constexpr R cast(A&& a) const { return static_cast <R>(a); }

public:
	using iter_store <TR, E...>::iter_store;
};

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename... E>
using iter_base = iter_common <D, TR, E...>;

template <typename D, typename TR, typename... E>
using trav_base = iter_common <D, TR, E...>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_BASE_ITER_BASE_HPP
