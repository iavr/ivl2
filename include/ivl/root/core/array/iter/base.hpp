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

#ifndef IVL_CORE_ARRAY_ITER_BASE_HPP
#define IVL_CORE_ARRAY_ITER_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename I, typename R = seq_ref <I>, typename T = seq_val <I>,
	typename D = seq_diff <I>, typename P = remove_ref <R>*
>
struct base_iter
{
	using iterator_type = I;
	using reference = R;
	using value_type = T;
	using difference_type = D;
	using pointer = P;

protected:
	template <typename A>
	INLINE constexpr R ref(A&& a) const { return static_cast <R>(a); }
};

//-----------------------------------------------------------------------------

template <
	bool F, typename V, typename R = seq_ref <V>, typename T = seq_val <V>,
	typename D = seq_diff <V>, typename P = remove_ref <R>*
>
struct base_trav : base_iter <V, R, T, D, P>
{
	static constexpr bool finite = F;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_BASE_HPP
