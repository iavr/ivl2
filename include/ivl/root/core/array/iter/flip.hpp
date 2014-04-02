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

template <typename D, typename TR>
class flip_iter_base : public derived <D, _false>
{
	using derived <D, _false>::der;

	using R = seq_iref <TR>;
	using d = seq_diff <TR>;

//-----------------------------------------------------------------------------

protected:
	INLINE void inc() { --der().v(); }
	INLINE void dec() { ++der().v(); }

	INLINE void add(d n) { der().v() -= n; }
	INLINE void sub(d n) { der().v() += n; }

	template <typename F, typename O>
	INLINE constexpr bool
	comp(F, O&& o) const { return afun::inv_fun <F>()(der().v(), o.v()); }

	template <typename O>
	INLINE constexpr d
	comp(afun::op::sub, O&& o) const { return o.v() - der().v(); }

//-----------------------------------------------------------------------------

public:
	INLINE constexpr R operator*()     const { return *der().v(); }
	INLINE constexpr R operator[](d n) const { return  der().v()[-n]; }
};

//-----------------------------------------------------------------------------

template <
	typename I, typename R, typename T,
	typename D = flip_iter <I, R, T>,
	typename TR = iter_traits <I, R, T>
>
class flip_iter_impl :
	public flip_iter_base <D, TR>,
	public iter_base <D, TR, I>
{
	using S = flip_iter_base <D, TR>;
	using B = iter_base <D, TR, I>;

	friend base_type_of <B>;

	template <typename, typename>
	friend class flip_iter_base;

//-----------------------------------------------------------------------------

	using iter = iter_elem <0, I>;

	INLINE           l_iter_ref <I> v()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> v() const { return iter::get(); }

//-----------------------------------------------------------------------------

	using S::inc;
	using S::dec;
	using S::add;
	using S::sub;
	using S::comp;

//-----------------------------------------------------------------------------

public:
	using B::B;
	using S::operator*;
	using S::operator[];
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D = flip_trav <Q, V, R, T>,
	typename TR = iter_traits <V, R, T>
>
class flip_trav_impl :
	public flip_iter_base <D, TR>,
	public trav_base <D, TR, Q, V>
{
	using S = flip_iter_base <D, TR>;
	using B = trav_base <D, TR, Q, V>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class flip_iter_base;

//-----------------------------------------------------------------------------

	using trav = iter_elem <0, V>;

	INLINE           l_iter_ref <V> v()       { return trav::get(); }
	INLINE constexpr c_iter_ref <V> v() const { return trav::get(); }

//-----------------------------------------------------------------------------

	template <typename P> INLINE void shift_l(P) { v() >>= P(); }
	template <typename P> INLINE void shift_r(P) { v() <<= P(); }

	INLINE void _swap() { v().swap(); }

//-----------------------------------------------------------------------------

	using S::inc;
	using S::dec;
	using S::add;
	using S::sub;
	using S::comp;

//-----------------------------------------------------------------------------

public:
	using B::B;
	using S::operator*;
	using S::operator[];

	static constexpr bool finite = fin_trav <V>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return v(); }

	INLINE bool operator+() const { return -v(); }
	INLINE bool operator-() const { return +v(); }
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
