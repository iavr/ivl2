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

#ifndef IVL_CORE_ARRAY_BASE_ITER_STORE_HPP
#define IVL_CORE_ARRAY_BASE_ITER_STORE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename... E>
struct iter_tuple : der_tuple <D, iter_opt <E>...>
{
	using der_tuple <D, iter_opt <E>...>::der_tuple;
};

template <typename D>
struct iter_tuple <D> { };

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename... E> struct iter_store;

template <
	typename I, typename R = seq_iref <I>, typename T = seq_val <I>,
	typename d = seq_diff <I>, typename P = remove_ref <R>*
>
struct iter_traits : iter_store <nat, iter_traits <I, R, T, d, P> >
{
	using traits = iter_traits;
};

//-----------------------------------------------------------------------------

template <
	typename D,
	typename I, typename R, typename T, typename d, typename P,
	typename... E
>
struct iter_store <D, iter_traits <I, R, T, d, P>, E...> :
	protected iter_tuple <D, E...>
{
	using iterator_type = I;
	using reference = R;
	using value_type = T;
	using difference_type = d;
	using pointer = P;

	using iter_tuple <D, E...>::iter_tuple;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_BASE_ITER_STORE_HPP
