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
	typename T, typename L = no_size, typename B = remove_ref <T>*,
	template <typename...> class I = iter_iter,
	template <typename...> class V = iter_trav,
	typename S = seq_size <B>, typename... U
>
struct seq_traits : seq_store <seq_traits <T, L, B, I, V, S, U...> >
{
	using traits = seq_traits;
};

//-----------------------------------------------------------------------------

template <
	typename T, typename L, typename B, template <typename...> class I,
	template <typename...> class V, typename S, typename... U,
	typename... E
>
struct seq_store <seq_traits <T, L, B, I, V, S, U...>, E...> :
	public seq_tuple <E...>
{
	using VT = remove_type <T>;

	using value_type = VT;
	using length_type = L;
	using size_type = S;

	using fwd_iterator   = I <r_iter <B>, r_ref <T>, VT, r_ref <U>...>;
	using iterator       = I <l_iter <B>, l_ref <T>, VT, l_ref <U>...>;
	using const_iterator = I <c_iter <B>, c_ref <T>, VT, c_ref <U>...>;

	using fwd_traversor   = V <r_trav <B>, r_ref <T>, VT, r_ref <U>...>;
	using traversor       = V <l_trav <B>, l_ref <T>, VT, l_ref <U>...>;
	using const_traversor = V <c_trav <B>, c_ref <T>, VT, c_ref <U>...>;

	using fwd_reference   = seq_ref <fwd_iterator>;
	using reference       = seq_ref <iterator>;
	using const_reference = seq_ref <const_iterator>;

	using pointer         = seq_ptr <iterator>;
	using const_pointer   = seq_ptr <const_iterator>;

	using difference_type = seq_diff <iterator>;

	static constexpr bool   finite = traversor::finite;
	static constexpr bool   fixed  = is_size <L>();
	static constexpr size_t length = to_size <L>();

	using seq_tuple <E...>::seq_tuple;
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