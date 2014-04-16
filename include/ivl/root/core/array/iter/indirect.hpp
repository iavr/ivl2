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

#ifndef IVL_CORE_ARRAY_ITER_INDIRECT_HPP
#define IVL_CORE_ARRAY_ITER_INDIRECT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename TR>
class indirect_trav_base : public derived <D, _false>
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

	template <typename F, typename O>
	INLINE constexpr bool
	comp(F f, O&& o) const { return f(der().v(), o.v()); }

	template <typename O>
	INLINE constexpr d
	comp(afun::op::sub, O&& o) const { return der().v() - o.v(); }

//-----------------------------------------------------------------------------

public:
	INLINE constexpr R operator*()     const { return der().u()[*der().v()]; }
	INLINE constexpr R operator[](d n) const { return der().u()[der().v()[n]]; }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T, typename U,
	typename D = indirect_trav <Q, V, R, T, U>,
	typename TR = iter_traits <V, R, T>,
	bool = path_iter <Q>()
>
class indirect_trav_impl :
	public indirect_trav_base <D, TR>,
	public iter_base <D, TR, V, U>
{
	using S = indirect_trav_base <D, TR>;
	using B = iter_base <D, TR, V, U>;

	friend base_type_of <B>;

	template <typename, typename>
	friend class indirect_trav_base;

//-----------------------------------------------------------------------------

	using iter  = iter_elem <0, V>;
	using under = iter_elem <1, U>;

	INLINE           l_iter_ref <V> v()       { return iter::get(); }
	INLINE constexpr c_iter_ref <V> v() const { return iter::get(); }

	INLINE           l_iter_ref <U> u()       { return under::get(); }
	INLINE constexpr c_iter_ref <U> u() const { return under::get(); }

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
	typename Q, typename V, typename R, typename T, typename U,
	typename D, typename TR
>
class indirect_trav_impl <Q, V, R, T, U, D, TR, false> :
	public indirect_trav_base <D, TR>,
	public trav_base <D, TR, Q, V, U>
{
	using S = indirect_trav_base <D, TR>;
	using B = trav_base <D, TR, Q, V, U>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class indirect_trav_base;

//-----------------------------------------------------------------------------

	using trav  = iter_elem <0, V>;
	using under = iter_elem <1, U>;

	INLINE           l_iter_ref <V> v()       { return trav::get(); }
	INLINE constexpr c_iter_ref <V> v() const { return trav::get(); }

	INLINE           l_iter_ref <U> u()       { return under::get(); }
	INLINE constexpr c_iter_ref <U> u() const { return under::get(); }

//-----------------------------------------------------------------------------

	template <typename P> INLINE void shift_l(P) { v() <<= P(); }
	template <typename P> INLINE void shift_r(P) { v() >>= P(); }

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

	INLINE bool operator+() const { return v(); }
	INLINE bool operator-() const { return v(); }
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T, typename U>
struct traversor <tag::indirect, Q, V, R, T, U> :
	indirect_trav_impl <Q, V, R, T, U>
{
	using indirect_trav_impl <Q, V, R, T, U>::indirect_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_INDIRECT_HPP
