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

#ifndef IVL_CORE_ARRAY_BASE_SEQ_STORE_HPP
#define IVL_CORE_ARRAY_BASE_SEQ_STORE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename... E>
struct seq_tuple : raw_tuple <E...> { using raw_tuple <E...>::raw_tuple; };

template <typename... B>
struct seq_tuple <pack <B...> > : der_cons <B...>
	{ using der_cons <B...>::der_cons; };

template <>
struct seq_tuple <> { };

//-----------------------------------------------------------------------------

template <typename A, typename E, typename D = seq_data <A> >
struct seq_data_tuple_;

template <typename A, typename... E, typename... D>
struct seq_data_tuple_<A, pack <E...>, pack <D...> > :
	id_t <seq_tuple <D..., E...> > { };

template <typename A, typename... E>
using seq_data_tuple = type_of <seq_data_tuple_<A, pack <E...> > >;

//-----------------------------------------------------------------------------

template <typename TR, typename... E> struct seq_store;

template <
	typename T, typename O = none, typename B = seq_elem <T>*,
	template <typename...> class I = iter_iter,
	template <typename...> class V = iter_trav,
	template <typename...> class F = id,
	typename S = seq_size <B>, typename... U
>
struct seq_traits : seq_store <seq_traits <T, O, B, I, V, F, S, U...> >
{
	using traits = seq_traits;
};

//-----------------------------------------------------------------------------

template <
	typename T, typename O, typename B, template <typename...> class I,
	template <typename...> class V, template <typename...> class F,
	typename S, typename... U, typename... E
>
struct seq_store <seq_traits <T, O, B, I, V, F, S, U...>, E...> :
	seq_tuple <E...>
{
	using value_type = T;
	using order_type = O;
	using size_type = S;

	using r_iterator = I <r_iter <B, F <path> >, r_ref <T>, T, r_ref <U>...>;
	using l_iterator = I <l_iter <B, F <path> >, l_ref <T>, T, l_ref <U>...>;
	using c_iterator = I <c_iter <B, F <path> >, c_ref <T>, T, c_ref <U>...>;

	template <typename Q = path>
	using r_traversor = V <Q, r_trav <B, F <Q> >, r_ref <T>, T, r_ref <U>...>;

	template <typename Q = path>
	using l_traversor = V <Q, l_trav <B, F <Q> >, l_ref <T>, T, l_ref <U>...>;

	template <typename Q = path>
	using c_traversor = V <Q, c_trav <B, F <Q> >, c_ref <T>, T, c_ref <U>...>;

	using r_reference = seq_iref <r_iterator>;
	using l_reference = seq_iref <l_iterator>;
	using c_reference = seq_iref <c_iterator>;

	using l_pointer = seq_iptr <l_iterator>;
	using c_pointer = seq_iptr <c_iterator>;

	using difference_type = seq_diff <l_iterator>;

	static constexpr bool finite = l_traversor <>::finite;

	using seq_tuple <E...>::seq_tuple;

//-----------------------------------------------------------------------------

	// for std only
	using iterator        = l_iterator;
	using const_iterator  = c_iterator;
	using reference       = l_reference;
	using const_reference = c_reference;
	using pointer         = l_pointer;
	using const_pointer   = c_pointer;

};

//-----------------------------------------------------------------------------

}  // namespace details

using details::seq_traits;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_BASE_SEQ_STORE_HPP
