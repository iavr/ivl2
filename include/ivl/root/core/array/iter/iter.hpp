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

#ifndef IVL_CORE_ARRAY_ITER_ITER_HPP
#define IVL_CORE_ARRAY_ITER_ITER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename I, typename R, typename T, typename D = iter_iter <I, R, T>,
	typename TR = iter_traits <I, R, T>
>
class iter_iter_impl : public iter_base <D, TR, I>
{
	using B = iter_base <D, TR, I>;
	using d = seq_diff <TR>;
	using P = seq_ptr <TR>;

	using iter = iter_elem <0, I>;

	using derived <D>::der;
	using B::ref;

//-----------------------------------------------------------------------------

	INLINE           l_iter_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> i() const { return iter::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr R operator*()  const { return ref(*i()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D& operator++() { return ++i(), der(); }
	INLINE D& operator--() { return --i(), der(); }

	INLINE D operator++(int) { return D(i()++); }
	INLINE D operator--(int) { return D(i()--); }

	INLINE constexpr R operator[](d n) const { return ref(i()[n]); }

	INLINE D& operator+=(d n) { return i() += n, der(); }
	INLINE D& operator-=(d n) { return i() -= n, der(); }

	INLINE D operator+(d n) { return D(i() + n); }
	INLINE D operator-(d n) { return D(i() - n); }
};

//-----------------------------------------------------------------------------

template <
	typename I, typename R, typename T, typename D = iter_trav <I, R, T>,
	typename TR = iter_traits <I, R, T>
>
class iter_trav_impl : public trav_base <D, TR, I, I>
{
	using B = trav_base <D, TR, I, I>;
	using d = seq_diff <TR>;
	using P = seq_ptr <TR>;

	using iter = iter_elem <0, I>;
	using end  = iter_elem <1, I>;

	using derived <D>::der;
	using B::ref;

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

	INLINE constexpr R operator*()  const { return ref(*i()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D& operator++() { return ++i(), der(); }
	INLINE D& operator--() { return --i(), der(); }

	INLINE D operator++(int) { return D(i()++, e); }
	INLINE D operator--(int) { return D(i()--, e); }

	INLINE constexpr R operator[](d n) const { return ref(i()[n]); }

	INLINE D& operator+=(d n) { return i() += n, der(); }
	INLINE D& operator-=(d n) { return i() -= n, der(); }

	INLINE D operator+(d n) { return D(i() + n, e); }
	INLINE D operator-(d n) { return D(i() - n, e); }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T>
struct iterator <data::iter <>, I, R, T> : iter_iter_impl <I, R, T>
{
	using iter_iter_impl <I, R, T>::iter_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename V, typename R, typename T>
struct traversor <data::iter <>, V, R, T> : iter_trav_impl <V, R, T>
{
	using iter_trav_impl <V, R, T>::iter_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_ITER_HPP
