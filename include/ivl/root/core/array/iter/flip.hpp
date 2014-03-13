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

#ifndef IVL_CORE_ARRAY_ITER_FLIP_HPP
#define IVL_CORE_ARRAY_ITER_FLIP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename I, typename R, typename T,
	typename D = flip_iter <I, R, T>,
	typename TR = iter_traits <I, R, T>
>
class flip_iter_impl : public iter_base <D, TR, I>
{
	using B = iter_base <D, TR, I>;
	using d = seq_diff <B>;

	using iter = iter_elem <0, I>;

	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

	INLINE           l_iter_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> i() const { return iter::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr R operator*() const { return *i(); }

//-----------------------------------------------------------------------------

	INLINE D&& operator++() && { return --i(), der_f(); }
	INLINE D&  operator++() &  { return --i(), der(); }
	INLINE D&& operator--() && { return ++i(), der_f(); }
	INLINE D&  operator--() &  { return ++i(), der(); }

	INLINE D operator++(int) { return D(i()--); }
	INLINE D operator--(int) { return D(i()++); }

//-----------------------------------------------------------------------------

	INLINE constexpr R operator[](d n) const { return i()[-n]; }

	INLINE D&& operator+=(d n) && { return i() -= n, der_f(); }
	INLINE D&  operator+=(d n) &  { return i() -= n, der(); }
	INLINE D&& operator-=(d n) && { return i() += n, der_f(); }
	INLINE D&  operator-=(d n) &  { return i() += n, der(); }

	INLINE D operator+(d n) const { return D(i() - n); }
	INLINE D operator-(d n) const { return D(i() + n); }

//-----------------------------------------------------------------------------

	// TODO
	INLINE bool operator!=(const D& o) { return i() != o.i(); }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D = flip_trav <Q, V, R, T>,
	typename TR = iter_traits <V, R, T>
>
class flip_trav_impl : public trav_base <D, TR, Q, V>
{
	using B = trav_base <D, TR, Q, V>;
	using d = seq_diff <B>;

	using trav = iter_elem <0, V>;

	using P = iter;
	using E = edge;

	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

	INLINE           l_iter_ref <V> v()       { return trav::get(); }
	INLINE constexpr c_iter_ref <V> v() const { return trav::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	static constexpr bool finite = fin_trav <V>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return v(); }

	INLINE constexpr R operator*() const { return *v(); }

//-----------------------------------------------------------------------------

	INLINE D&& operator++() && { return --v(), der_f(); }
	INLINE D&  operator++() &  { return --v(), der(); }
	INLINE D&& operator--() && { return ++v(), der_f(); }
	INLINE D&  operator--() &  { return ++v(), der(); }

	INLINE D operator++(int) { return D(v()--); }
	INLINE D operator--(int) { return D(v()++); }

//-----------------------------------------------------------------------------

	INLINE constexpr R operator[](d n) const { return v()[-n]; }

	INLINE D&& operator+=(d n) && { return v() -= n, der_f(); }
	INLINE D&  operator+=(d n) &  { return v() -= n, der(); }
	INLINE D&& operator-=(d n) && { return v() += n, der_f(); }
	INLINE D&  operator-=(d n) &  { return v() += n, der(); }

	INLINE D operator+(d n) const { return D(v() - n); }
	INLINE D operator-(d n) const { return D(v() + n); }

//-----------------------------------------------------------------------------

	INLINE bool operator+() const { return -v(); }
	INLINE bool operator-() const { return +v(); }

	INLINE D&& operator<<=(P) && { return v() >>= P(), der_f(); }
	INLINE D&  operator<<=(P) &  { return v() >>= P(), der(); }
	INLINE D&& operator>>=(P) && { return v() <<= P(), der_f(); }
	INLINE D&  operator>>=(P) &  { return v() <<= P(), der(); }

	INLINE D&& operator<<=(E) && { return v() >>= E(), der_f(); }
	INLINE D&  operator<<=(E) &  { return v() >>= E(), der(); }
	INLINE D&& operator>>=(E) && { return v() <<= E(), der_f(); }
	INLINE D&  operator>>=(E) &  { return v() <<= E(), der(); }

	INLINE D&& swap() && { return v().swap(), der_f(); }
	INLINE D&  swap() &  { return v().swap(), der(); }

//-----------------------------------------------------------------------------

	// TODO
	INLINE bool operator!=(const D& o) { return v() != o.v(); }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T>
struct iterator <tag::flip, I, R, T> :
	flip_iter_impl <I, R, T>
{
	using flip_iter_impl <I, R, T>::flip_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T>
struct traversor <tag::flip, Q, V, R, T> :
	flip_trav_impl <Q, V, R, T>
{
	using flip_trav_impl <Q, V, R, T>::flip_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_FLIP_HPP
