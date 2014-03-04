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

#ifndef IVL_CORE_ARRAY_ITER_TRAV_HPP
#define IVL_CORE_ARRAY_ITER_TRAV_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename Q, typename I, typename R, typename T,
	typename D = iter_trav <Q, I, R, T>,
	typename TR = iter_traits <I, R, T>,
	bool = path_in <Q>{}
>
class iter_trav_impl : public trav_base <D, TR, I, I>
{
	using B = trav_base <D, TR, I, I>;
	using d = seq_diff <B>;
	using P = seq_iptr <B>;

	using iter = iter_elem <0, I>;
	using end  = iter_elem <1, I>;

	using derived <D>::der_f;
	using derived <D>::der;
	using B::cast;

//-----------------------------------------------------------------------------

	INLINE           l_iter_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> i() const { return iter::get(); }

	INLINE           l_iter_ref <I> e()       { return end::get(); }
	INLINE constexpr c_iter_ref <I> e() const { return end::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	static constexpr bool finite = true;

	INLINE constexpr operator bool() const { return i() != e(); }

	INLINE constexpr R operator*()  const { return cast(*i()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D&& operator++() && { return ++i(), der_f(); }
	INLINE D&  operator++() &  { return ++i(), der(); }
	INLINE D&& operator--() && { return --i(), der_f(); }
	INLINE D&  operator--() &  { return --i(), der(); }

	INLINE D operator++(int) { return D(i()++, e()); }
	INLINE D operator--(int) { return D(i()--, e()); }

	INLINE constexpr R operator[](d n) const { return cast(i()[n]); }

	INLINE D&& operator+=(d n) && { return i() += n, der_f(); }
	INLINE D&  operator+=(d n) &  { return i() += n, der(); }
	INLINE D&& operator-=(d n) && { return i() -= n, der_f(); }
	INLINE D&  operator-=(d n) &  { return i() -= n, der(); }

	INLINE D operator+(d n) const { return D(i() + n, e()); }
	INLINE D operator-(d n) const { return D(i() - n, e()); }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename I, typename R, typename T,
	typename D, typename TR
>
class iter_trav_impl <Q, I, R, T, D, TR, true> :
	public trav_base <D, TR, I, I, I>
{
	using B = trav_base <D, TR, I, I, I>;
	using d = seq_diff <B>;
	using P = seq_iptr <B>;

	using first = iter_elem <0, I>;
	using iter  = iter_elem <1, I>;
	using last  = iter_elem <2, I>;

	using derived <D>::der_f;
	using derived <D>::der;
	using B::cast;

	using flip    = expr <path_flip <Q>{}>;
	using no_flip = expr <!path_flip <Q>()>;

//-----------------------------------------------------------------------------

	INLINE           l_iter_ref <I> f()       { return first::get(); }
	INLINE constexpr c_iter_ref <I> f() const { return first::get(); }

	INLINE           l_iter_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> i() const { return iter::get(); }

	INLINE           l_iter_ref <I> l()       { return last::get(); }
	INLINE constexpr c_iter_ref <I> l() const { return last::get(); }

//-----------------------------------------------------------------------------

	INLINE constexpr bool more(_true)  const { return i() != l() + 1; }
	INLINE constexpr bool more(_false) const { return i() != l() - 1; }

	INLINE constexpr bool inside(_true)  const { return i() != l(); }
	INLINE constexpr bool inside(_false) const { return i() != f(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	template <typename J, typename E>
	INLINE constexpr iter_trav_impl(J&& i, E&& e) : B(i, i, e) { }

	static constexpr bool finite = true;

	INLINE constexpr operator bool() const { return more(no_flip()); }

	INLINE bool operator+() const { return inside(no_flip()); }
	INLINE bool operator-() const { return inside(flip()); }

	INLINE constexpr R operator*()  const { return cast(*i()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D&& operator++() && { return ++i(), der_f(); }
	INLINE D&  operator++() &  { return ++i(), der(); }
	INLINE D&& operator--() && { return --i(), der_f(); }
	INLINE D&  operator--() &  { return --i(), der(); }

	INLINE D operator++(int) { return D(f(), i()++, l()); }
	INLINE D operator--(int) { return D(f(), i()--, l()); }

	INLINE constexpr R operator[](d n) const { return cast(i()[n]); }

	INLINE D&& operator+=(d n) && { return i() += n, der_f(); }
	INLINE D&  operator+=(d n) &  { return i() += n, der(); }
	INLINE D&& operator-=(d n) && { return i() -= n, der_f(); }
	INLINE D&  operator-=(d n) &  { return i() -= n, der(); }

	INLINE D operator+(d n) const { return D(f(), i() + n, l()); }
	INLINE D operator-(d n) const { return D(f(), i() - n, l()); }
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T>
struct traversor <tag::iter, Q, V, R, T> :
	iter_trav_impl <Q, V, R, T>
{
	using iter_trav_impl <Q, V, R, T>::iter_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_TRAV_HPP
