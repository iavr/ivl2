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
	using d = seq_diff <TR>;
	using P = seq_ptr <TR>;

	using iter = iter_elem <0, I>;

	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

	INLINE           l_iter_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> i() const { return iter::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr R operator*()  const { return *i(); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D&& operator++() && { return --i(), der_f(); }
	INLINE D&  operator++() &  { return --i(), der(); }
	INLINE D&& operator--() && { return ++i(), der_f(); }
	INLINE D&  operator--() &  { return ++i(), der(); }

	INLINE D operator++(int) { return D(i()--); }
	INLINE D operator--(int) { return D(i()++); }

	INLINE constexpr R operator[](d n) const { return i()[-n]; }

	INLINE D&& operator+=(d n) && { return i() -= n, der_f(); }
	INLINE D&  operator+=(d n) &  { return i() -= n, der(); }
	INLINE D&& operator-=(d n) && { return i() += n, der_f(); }
	INLINE D&  operator-=(d n) &  { return i() += n, der(); }

	INLINE D operator+(d n) const { return D(i() - n); }
	INLINE D operator-(d n) const { return D(i() + n); }

	// TODO
	INLINE bool operator!=(D o) { return i() != o.i(); }
};

//-----------------------------------------------------------------------------

template <
	typename V, typename R, typename T,
	typename D = flip_trav <V, R, T>,
	typename TR = iter_traits <V, R, T>
>
class flip_trav_impl : public trav_base <D, TR, V>
{
	using B = trav_base <D, TR, V>;
	using d = seq_diff <TR>;
	using P = seq_ptr <TR>;

	using trav = iter_elem <0, V>;

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

	INLINE constexpr R operator*()  const { return *v(); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D&& operator++() && { return --v(), der_f(); }
	INLINE D&  operator++() &  { return --v(), der(); }
	INLINE D&& operator--() && { return ++v(), der_f(); }
	INLINE D&  operator--() &  { return ++v(), der(); }

	INLINE D operator++(int) { return D(v()--); }
	INLINE D operator--(int) { return D(v()++); }

	INLINE D&& operator+() && { return -v(), der_f(); }
	INLINE D&  operator+() &  { return -v(), der(); }
	INLINE D&& operator-() && { return +v(), der_f(); }
	INLINE D&  operator-() &  { return +v(), der(); }

	INLINE constexpr R operator[](d n) const { return v()[-n]; }

	INLINE D&& operator+=(d n) && { return v() -= n, der_f(); }
	INLINE D&  operator+=(d n) &  { return v() -= n, der(); }
	INLINE D&& operator-=(d n) && { return v() += n, der_f(); }
	INLINE D&  operator-=(d n) &  { return v() += n, der(); }

	INLINE D operator+(d n) const { return D(v() - n); }
	INLINE D operator-(d n) const { return D(v() + n); }
};

//-----------------------------------------------------------------------------

template <typename V, typename R, typename T>
struct iterator <data::flip <>, V, R, T> :
	flip_iter_impl <V, R, T>
{
	using flip_iter_impl <V, R, T>::flip_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename V, typename R, typename T>
struct traversor <data::flip <>, V, R, T> :
	flip_trav_impl <V, R, T>
{
	using flip_trav_impl <V, R, T>::flip_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_FLIP_HPP
