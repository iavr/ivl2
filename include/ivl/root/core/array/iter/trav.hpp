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

template <typename D, typename TR>
class trav_trav_base : public derived <D, tag::trav>
{
	using derived <D, tag::trav>::der;

	using R = seq_iref <TR>;
	using d = seq_diff <TR>;

//-----------------------------------------------------------------------------

protected:
	INLINE void inc() { ++der().v(); }
	INLINE void dec() { --der().v(); }

	INLINE void add(d n) { der().v() += n; }
	INLINE void sub(d n) { der().v() -= n; }

	template <typename F, typename O>
	INLINE constexpr bool
	comp(F f, O&& o) const { return f(der().v(), o.v()); }

	template <typename O>
	INLINE constexpr d
	comp(afun::op::sub, O&& o) const { return der().v() - o.v(); }

//-----------------------------------------------------------------------------

public:
	INLINE constexpr R operator*() const
		{ return der().cast(*der().v()); }

	INLINE constexpr R operator[](d n) const
		{ return der().cast( der().v()[n]); }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D = trav_trav <Q, V, R, T>,
	typename TR = iter_traits <V, R, T>,
	bool = path_iter <Q>(), bool = path_edge <Q>()  // true, false
>
class trav_trav_impl :
	public trav_trav_base <D, TR>,
	public iter_base <D, TR, V>
{
	using S = trav_trav_base <D, TR>;
	using B = iter_base <D, TR, V>;

	friend base_type_of <B>;

	template <typename, typename>
	friend class trav_trav_base;

//-----------------------------------------------------------------------------

protected:
	using iter = iter_elem <0, V>;

	INLINE           l_iter_ref <V> v()       { return iter::get(); }
	INLINE constexpr c_iter_ref <V> v() const { return iter::get(); }

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
	typename D, typename TR
>
class trav_trav_impl <Q, V, R, T, D, TR, false, false> :
	public trav_trav_base <D, TR>,
	public trav_base <D, TR, Q, V>
{
	using S = trav_trav_base <D, TR>;
	using B = trav_base <D, TR, Q, V>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class trav_trav_base;

//-----------------------------------------------------------------------------

protected:
	using trav = iter_elem <0, V>;

	INLINE           l_iter_ref <V> v()       { return trav::get(); }
	INLINE constexpr c_iter_ref <V> v() const { return trav::get(); }

//-----------------------------------------------------------------------------

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

	static constexpr bool finite = trav_finite <V>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return v(); }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D, typename TR, bool ITER
>
class trav_trav_impl <Q, V, R, T, D, TR, ITER, true> :
	public trav_trav_impl <Q, V, R, T, D, TR, false, false>
{
	using B = trav_trav_impl <Q, V, R, T, D, TR, false, false>;

	friend base_trav_of <B>;
	friend base_type_of <B>;

	template <typename, typename>
	friend class trav_trav_base;

//-----------------------------------------------------------------------------

protected:
	template <typename P> INLINE void shift_l(P) { B::v() <<= P(); }
	template <typename P> INLINE void shift_r(P) { B::v() >>= P(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE bool operator+() const { return +B::v(); }
	INLINE bool operator-() const { return -B::v(); }
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

#endif  // IVL_CORE_ARRAY_ITER_TRAV_HPP
