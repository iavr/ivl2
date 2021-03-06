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

#ifndef IVL_CORE_ARRAY_ITER_RANGE_HPP
#define IVL_CORE_ARRAY_ITER_RANGE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename TR>
class range_trav_base : public derived <D, tag::range>
{
	using derived <D, tag::range>::der;

	using R = seq_iref <TR>;
	using d = seq_diff <TR>;

//-----------------------------------------------------------------------------

protected:
	INLINE void inc() { der().u().inc(der().v()); }
	INLINE void dec() { der().u().dec(der().v()); }

	INLINE void add(d n) { der().u().add(der().v(), n); }
	INLINE void sub(d n) { der().u().sub(der().v(), n); }

	template <typename F, typename O>
	INLINE constexpr bool
	comp(F f, O&& o) const { return der().u().comp(f, der().v(), o.v()); }

	template <typename O>
	INLINE constexpr d
	comp(afun::op::sub, O&& o) const
		{ return der().u().template diff <d>(der().v(), o.v()); }

//-----------------------------------------------------------------------------

public:
	INLINE R operator*()     const { return der().v(); }
	INLINE R operator[](d n) const { return der().u().rel(der().v(), n); }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T, typename U, typename F,
	typename D = range_trav <Q, V, R, T, U, F>,
	typename TR = iter_traits <V, R, T, ptrdiff_t>,
	bool = path_iter <Q>(), bool = path_edge <Q>()  // default: F = any, true, false
>
class range_trav_impl :
	public range_trav_base <D, TR>,
	public iter_base <D, TR, U, V>
{
	using S = range_trav_base <D, TR>;
	using B = iter_base <D, TR, U, V>;

	friend base_type_of <B>;

	template <typename, typename>
	friend class range_trav_base;

//-----------------------------------------------------------------------------

	using delta = iter_elem <0, U>;
	using iter  = iter_elem <1, V>;

	INLINE           l_iter_ref <U> u()       { return delta::get(); }
	INLINE constexpr c_iter_ref <U> u() const { return delta::get(); }

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
	typename Q, typename V, typename R, typename T, typename U,
	typename D, typename TR
>
class range_trav_impl <Q, V, R, T, U, _false, D, TR, false, false> :
	public range_trav_base <D, TR>,
	public trav_base <D, TR, Q, U, V>
{
	using S = range_trav_base <D, TR>;
	using B = trav_base <D, TR, Q, U, V>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class range_trav_base;

//-----------------------------------------------------------------------------

	using delta = iter_elem <0, U>;
	using iter  = iter_elem <1, V>;

	INLINE           l_iter_ref <U> u()       { return delta::get(); }
	INLINE constexpr c_iter_ref <U> u() const { return delta::get(); }

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

	static constexpr bool finite = false;

	INLINE constexpr operator bool() const { return true; }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T, typename U,
	typename D, typename TR
>
class range_trav_impl <Q, V, R, T, U, _true, D, TR, false, false> :
	public range_trav_base <D, TR>,
	public trav_base <D, TR, Q, U, V, V>
{
	using S = range_trav_base <D, TR>;
	using B = trav_base <D, TR, Q, U, V, V>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class range_trav_base;

//-----------------------------------------------------------------------------

	using delta = iter_elem <0, U>;
	using iter  = iter_elem <1, V>;
	using end   = iter_elem <2, V>;

	INLINE           l_iter_ref <U> u()       { return delta::get(); }
	INLINE constexpr c_iter_ref <U> u() const { return delta::get(); }

	INLINE           l_iter_ref <V> v()       { return iter::get(); }
	INLINE constexpr c_iter_ref <V> v() const { return iter::get(); }

	INLINE           l_iter_ref <V> e()       { return end::get(); }
	INLINE constexpr c_iter_ref <V> e() const { return end::get(); }

//-----------------------------------------------------------------------------

	INLINE void _swap() { ivl::swap(v(), e()); }

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

	static constexpr bool finite = true;

	INLINE constexpr operator bool() const { return v() != e(); }
};

//-----------------------------------------------------------------------------

// edge traversor can only be finite
template <
	typename Q, typename V, typename R, typename T, typename U,
	typename D, typename TR, bool ITER
>
struct range_trav_impl <Q, V, R, T, U, _false, D, TR, ITER, true> :  // TODO: undefine
	range_trav_impl <Q, V, R, T, U, _false, D, TR, ITER, false>
{
	using range_trav_impl <Q, V, R, T, U, _false, D, TR, ITER, false>
		::range_trav_impl;
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T, typename U,
	typename D, typename TR, bool ITER
>
class range_trav_impl <Q, V, R, T, U, _true, D, TR, ITER, true> :
	public edge_trav_base <D, TR>,
	public range_trav_base <D, TR>,
	public trav_base <D, TR, Q, U, V, V, V>
{
	using E = edge_trav_base <D, TR>;
	using S = range_trav_base <D, TR>;
	using B = trav_base <D, TR, Q, U, V, V, V>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename> friend class edge_trav_base;
	template <typename, typename> friend class range_trav_base;

//-----------------------------------------------------------------------------

	using delta = iter_elem <0, U>;
	using first = iter_elem <1, V>;
	using iter  = iter_elem <2, V>;
	using last  = iter_elem <3, V>;

	INLINE           l_iter_ref <U> u()       { return delta::get(); }
	INLINE constexpr c_iter_ref <U> u() const { return delta::get(); }

	INLINE           l_iter_ref <V> f()       { return first::get(); }
	INLINE constexpr c_iter_ref <V> f() const { return first::get(); }

	INLINE           l_iter_ref <V> v()       { return iter::get(); }
	INLINE constexpr c_iter_ref <V> v() const { return iter::get(); }

	INLINE           l_iter_ref <V> l()       { return last::get(); }
	INLINE constexpr c_iter_ref <V> l() const { return last::get(); }

	INLINE constexpr iter_val <V> end() const { return u().next(l()); }

//-----------------------------------------------------------------------------

	using S::inc;
	using S::dec;
	using S::add;
	using S::sub;
	using S::comp;
	using E::shift_l;
	using E::shift_r;
	using E::_swap;

//-----------------------------------------------------------------------------

public:
	using S::operator*;
	using S::operator[];
	using E::operator bool;
	using E::operator+;
	using E::operator-;

	template <typename _U, typename _V, typename E>
	INLINE range_trav_impl(_U&& _u, _V&& v, E&& e) :
		B(fwd <_U>(_u), v, fwd <_V>(v), fwd <E>(e)) { u().dec(l()); }

	static constexpr bool finite = true;
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T, typename U, typename F>
struct traversor <tag::range, Q, V, R, T, U, F> :
	range_trav_impl <Q, V, R, T, U, F>
{
	using range_trav_impl <Q, V, R, T, U, F>::range_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_RANGE_HPP
