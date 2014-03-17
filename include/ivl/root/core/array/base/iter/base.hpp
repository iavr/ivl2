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
	public iter_store <D, TR, E...>
{
	using R = seq_iref <TR>;
	using d = seq_diff <TR>;
	using P = seq_iptr <TR>;

protected:
	using derived <D>::der_f;
	using derived <D>::der;

	template <typename A>
	INLINE constexpr R cast(A&& a) const { return static_cast <R>(a); }

//-----------------------------------------------------------------------------

public:
	using base_type = iter_base;

	using iter_store <D, TR, E...>::iter_store;

	INLINE P operator->() const { return &(der().operator*()); }

	INLINE D&& operator++() && { return der_f().inc(), der_f(); }
	INLINE D&  operator++() &  { return der().  inc(), der(); }
	INLINE D&& operator--() && { return der_f().dec(), der_f(); }
	INLINE D&  operator--() &  { return der().  dec(), der(); }

	INLINE D&& operator+=(d n) && { return der_f().add(n), der_f(); }
	INLINE D&  operator+=(d n) &  { return der().  add(n), der(); }
	INLINE D&& operator-=(d n) && { return der_f().sub(n), der_f(); }
	INLINE D&  operator-=(d n) &  { return der().  sub(n), der(); }

//-----------------------------------------------------------------------------

	template <typename V, only_if <iter_comp <D, V>{}> = 0>
	INLINE constexpr bool operator==(V&& v) const
		{ return der().comp(afun::op::eq(), v); }

	template <typename V, only_if <iter_comp <D, V>{}> = 0>
	INLINE constexpr bool operator!=(V&& v) const
		{ return der().comp(afun::op::neq(), v); }

	template <typename V, only_if <iter_comp <D, V>{}> = 0>
	INLINE constexpr bool operator<(V&& v) const
		{ return der().comp(afun::op::lt(), v); }

	template <typename V, only_if <iter_comp <D, V>{}> = 0>
	INLINE constexpr bool operator<=(V&& v) const
		{ return der().comp(afun::op::le(), v); }

	template <typename V, only_if <iter_comp <D, V>{}> = 0>
	INLINE constexpr bool operator>(V&& v) const
		{ return der().comp(afun::op::gt(), v); }

	template <typename V, only_if <iter_comp <D, V>{}> = 0>
	INLINE constexpr bool operator>=(V&& v) const
		{ return der().comp(afun::op::ge(), v); }
};

//-----------------------------------------------------------------------------

template <
	typename D, typename TR, typename Q, typename E,
	bool = path_edge <Q>()
>
class trav_base_spec;

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename Q, typename... E>
class trav_base_spec <D, TR, Q, pack <E...>, false> :
	public iter_base <D, TR, E...>
{
	using B = iter_base <D, TR, E...>;

public:
	using B::B;

	INLINE void flip() { --((--B::der()).swap()); }
};

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename Q, typename... E>
class trav_base_spec <D, TR, Q, pack <E...>, true> :
	public iter_base <D, TR, E...>
{
	using B = iter_base <D, TR, E...>;

public:
	using B::B;

	INLINE void flip() { B::der().swap(); }

};

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename Q, typename... E>
struct trav_base : trav_base_spec <D, TR, Q, pack <E...> >
{
	using B = trav_base_spec <D, TR, Q, pack <E...> >;

protected:
	using B::der_f;
	using B::der;

	template <typename P> INLINE void shift_l(P) { }
	template <typename P> INLINE void shift_r(P) { }

	INLINE void _swap()  { }

//-----------------------------------------------------------------------------

public:
	using B::B;

	using base_trav = trav_base;

	template <typename P>
	INLINE D&& operator<<=(P) && { return der_f().shift_l(P()), der_f(); }

	template <typename P>
	INLINE D&  operator<<=(P) & { return der().shift_l(P()), der(); }

	template <typename P>
	INLINE D&& operator>>=(P) && { return der_f().shift_r(P()), der_f(); }

	template <typename P>
	INLINE D&  operator>>=(P) & { return der().shift_r(P()), der(); }

	INLINE D&& flip() && { return B::flip(), der_f(); }
	INLINE D&  flip() &  { return B::flip(), der(); }

	INLINE D&& swap() && { return der_f()._swap(), der_f(); }  // TODO: should be private?
	INLINE D&  swap() &  { return der().  _swap(), der(); }
};

//-----------------------------------------------------------------------------

template <typename T> using base_trav_of = typename T::base_trav;
template <typename T> using base_impl_of = typename T::base_impl;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_BASE_ITER_BASE_HPP
