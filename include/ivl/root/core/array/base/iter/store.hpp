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

template <typename T, bool = is_iter <T>()>
struct iter_opt_ : rref_opt_t <T> { };

template <typename T>
struct iter_opt_<T, true> : base_opt_t <T> { };

template <typename T> using iter_opt_t = iter_opt_<T>;
template <typename T> using iter_opt = type_of <iter_opt_t <T> >;

//-----------------------------------------------------------------------------

template <size_t N, typename T>
using iter_elem = elem <N, iter_opt <T> >;

template <size_t N, typename... E>
using iter_elem_at = iter_elem <N, pick <N, E...> >;

template <typename T> using r_iter_ref = r_ref <iter_opt <T> >;
template <typename T> using l_iter_ref = l_ref <iter_opt <T> >;
template <typename T> using c_iter_ref = c_ref <iter_opt <T> >;

template <size_t N, typename... E>
using r_iter_pick = r_iter_ref <pick <N, E...> >;

template <size_t N, typename... E>
using l_iter_pick = l_iter_ref <pick <N, E...> >;

template <size_t N, typename... E>
using c_iter_pick = c_iter_ref <pick <N, E...> >;

//-----------------------------------------------------------------------------

template <typename... E>
struct iter_tuple : raw_tuple <iter_opt <E>...>
	{ using raw_tuple <iter_opt <E>...>::raw_tuple; };

template <>
struct iter_tuple <> { };

//-----------------------------------------------------------------------------

template <typename TR, typename... E> struct iter_store;

template <
	typename I, typename R = seq_ref <I>, typename T = seq_type <I>,
	typename D = seq_diff <I>, typename P = remove_ref <R>*
>
struct iter_traits : iter_store <iter_traits <I, R, T, D, P> >
{
	using traits = iter_traits;
};

//-----------------------------------------------------------------------------

template <
	typename I, typename R, typename T, typename D, typename P,
	typename... E
>
struct iter_store <iter_traits <I, R, T, D, P>, E...> :
	protected iter_tuple <E...>
{
	using iterator_type = I;
	using reference = R;
	using value_type = T;
	using difference_type = D;
	using pointer = P;

	using iter_tuple <E...>::iter_tuple;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_BASE_ITER_STORE_HPP