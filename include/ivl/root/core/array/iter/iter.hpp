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

template <typename D, typename TR>
class iter_iter_base : public derived <D, _false>
{
	using derived <D, _false>::der;

	using R = seq_iref <TR>;
	using d = seq_diff <TR>;

//-----------------------------------------------------------------------------

protected:
	INLINE void inc() { ++der().v(); }
	INLINE void dec() { --der().v(); }

	INLINE void add(d n) { der().v() += n; }
	INLINE void sub(d n) { der().v() -= n; }

	template <typename F, typename V>
	INLINE constexpr bool
	comp(F f, V&& v) const { return f(der().v(), v.v()); }

//-----------------------------------------------------------------------------

public:
	INLINE constexpr R operator*() const
		{ return der().cast(*der().v()); }

	INLINE constexpr R operator[](d n) const
		{ return der().cast( der().v()[n]); }
};

//-----------------------------------------------------------------------------

template <
	typename I, typename R, typename T,
	typename D = iter_iter <I, R, T>,
	typename TR = iter_traits <I, R, T>
>
class iter_iter_impl :
	public iter_iter_base <D, TR>,
	public iter_base <D, TR, I>
{
	using B = iter_base <D, TR, I>;

	friend base_type_of <B>;

	template <typename, typename>
	friend class iter_iter_base;

//-----------------------------------------------------------------------------

	using iter = iter_elem <0, I>;

	INLINE           l_iter_ref <I> v()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> v() const { return iter::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D = trav_trav <Q, V, R, T>,
	typename TR = iter_traits <V, R, T>
>
class trav_trav_impl :
	public iter_iter_base <D, TR>,
	public trav_base <D, TR, Q, V>
{
	using B = trav_base <D, TR, Q, V>;
	using d = seq_diff <B>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class iter_iter_base;

//-----------------------------------------------------------------------------

	using trav = iter_elem <0, V>;

	INLINE           l_iter_ref <V> v()       { return trav::get(); }
	INLINE constexpr c_iter_ref <V> v() const { return trav::get(); }

//-----------------------------------------------------------------------------

	template <typename P> INLINE void shift_l(P) { v() <<= P(); }
	template <typename P> INLINE void shift_r(P) { v() >>= P(); }

	INLINE void _swap() { v().swap(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	static constexpr bool finite = fin_trav <V>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return v(); }

	INLINE bool operator+() const { return +v(); }
	INLINE bool operator-() const { return -v(); }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T>
struct iterator <tag::iter, I, R, T> :
	iter_iter_impl <I, R, T>
{
	using iter_iter_impl <I, R, T>::iter_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T>
struct traversor <tag::trav, Q, V, R, T> :
	trav_trav_impl <Q, V, R, T>
{
	using trav_trav_impl <Q, V, R, T>::trav_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_ITER_HPP
