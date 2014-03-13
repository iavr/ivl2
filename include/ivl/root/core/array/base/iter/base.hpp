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
class iter_base :
	public derived <D>,
	public iter_store <TR, E...>
{
	using R = seq_iref <TR>;
	using d = seq_diff <TR>;
	using P = seq_iptr <TR>;

protected:
	using derived <D>::der_f;
	using derived <D>::der;

	template <typename A>
	INLINE constexpr R cast(A&& a) const { return static_cast <R>(a); }

public:
	using iter_store <TR, E...>::iter_store;

	INLINE P operator->() const { return &(der().operator*()); }
};

//-----------------------------------------------------------------------------

template <
	typename D, typename TR, typename Q, typename E,
	bool = path_edge <Q>()
>
class trav_base_impl;

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename Q, typename... E>
class trav_base_impl <D, TR, Q, pack <E...>, false> :
	public iter_base <D, TR, E...>
{
	using B = iter_base <D, TR, E...>;

protected:
	using B::der_f;
	using B::der;

public:
	using B::B;

	INLINE D&& operator<<=(edge) && { return der_f(); }
	INLINE D&  operator<<=(edge) &  { return der(); }
	INLINE D&& operator>>=(edge) && { return der_f(); }
	INLINE D&  operator>>=(edge) &  { return der(); }

	INLINE D&& flip() && { return --((--der_f()).swap()); }
	INLINE D&  flip() &  { return --((--der  ()).swap()); }

};

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename Q, typename... E>
class trav_base_impl <D, TR, Q, pack <E...>, true> :
	public trav_base_impl <D, TR, Q, pack <E...>, false>
{
	using B = trav_base_impl <D, TR, Q, pack <E...>, false>;

protected:
	using B::der_f;
	using B::der;

public:
	using B::B;

	INLINE D&& flip() && { return der_f().swap(); }
	INLINE D&  flip() &  { return der  ().swap(); }

};

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename Q, typename... E>
using trav_base = trav_base_impl <D, TR, Q, pack <E...> >;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_BASE_ITER_BASE_HPP
