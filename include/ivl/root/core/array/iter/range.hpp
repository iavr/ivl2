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
class range_iter_base : public derived <D, _false>
{
	using derived <D, _false>::der;

	using R = seq_iref <TR>;
	using d = seq_diff <TR>;

//-----------------------------------------------------------------------------

protected:
	INLINE void inc() { der().u().inc(der().i()); }
	INLINE void dec() { der().u().dec(der().i()); }

	INLINE void add(d n) { der().u().add(der().i(), n); }
	INLINE void sub(d n) { der().u().sub(der().i(), n); }

	template <typename F, typename O>
	INLINE constexpr bool
	comp(F f, O&& o) const { return der().u().comp(f, der().i(), o.i()); }

	template <typename O>
	INLINE constexpr d
	comp(afun::op::sub, O&& o) const
		{ return der().u().template diff <d>(der().i(), o.i()); }

//-----------------------------------------------------------------------------

public:
	INLINE R operator*()     const { return der().i(); }
	INLINE R operator[](d n) const { return der().u().rel(der().i(), n); }
};

//-----------------------------------------------------------------------------

template <
	typename I, typename R, typename T, typename U, typename F,
	typename D = range_iter <I, R, T, U, F>,
	typename TR = iter_traits <I, R, T, ptrdiff_t>
>
class range_iter_impl :
	public range_iter_base <D, TR>,
	public iter_base <D, TR, U, I>
{
	using S = range_iter_base <D, TR>;
	using B = iter_base <D, TR, U, I>;

	friend base_type_of <B>;

	template <typename, typename>
	friend class range_iter_base;

//-----------------------------------------------------------------------------

	using delta = iter_elem <0, U>;
	using iter  = iter_elem <1, I>;

	INLINE           l_iter_ref <U> u()       { return delta::get(); }
	INLINE constexpr c_iter_ref <U> u() const { return delta::get(); }

	INLINE           l_iter_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> i() const { return iter::get(); }

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
	typename Q, typename I, typename R, typename T, typename U, typename F,
	typename D = range_trav <Q, I, R, T, U, F>,
	typename TR = iter_traits <I, R, T, ptrdiff_t>,
	bool = F(), bool = path_edge <Q>()
>
class range_trav_impl :
	public range_iter_base <D, TR>,
	public trav_base <D, TR, Q, U, I>
{
	using S = range_iter_base <D, TR>;
	using B = trav_base <D, TR, Q, U, I>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class range_iter_base;

//-----------------------------------------------------------------------------

	using delta = iter_elem <0, U>;
	using iter  = iter_elem <1, I>;

	INLINE           l_iter_ref <U> u()       { return delta::get(); }
	INLINE constexpr c_iter_ref <U> u() const { return delta::get(); }

	INLINE           l_iter_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> i() const { return iter::get(); }

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
	typename Q, typename I, typename R, typename T, typename U, typename F,
	typename D, typename TR
>
class range_trav_impl <Q, I, R, T, U, F, D, TR, true, false> :
	public range_iter_base <D, TR>,
	public trav_base <D, TR, Q, U, I, I>
{
	using S = range_iter_base <D, TR>;
	using B = trav_base <D, TR, Q, U, I, I>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class range_iter_base;

//-----------------------------------------------------------------------------

	using delta = iter_elem <0, U>;
	using iter  = iter_elem <1, I>;
	using end   = iter_elem <2, I>;

	INLINE           l_iter_ref <U> u()       { return delta::get(); }
	INLINE constexpr c_iter_ref <U> u() const { return delta::get(); }

	INLINE           l_iter_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> i() const { return iter::get(); }

	INLINE           l_iter_ref <I> e()       { return end::get(); }
	INLINE constexpr c_iter_ref <I> e() const { return end::get(); }

//-----------------------------------------------------------------------------

	INLINE void _swap() { ivl::swap(i(), e()); }

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

	INLINE constexpr operator bool() const { return i() != e(); }
};

//-----------------------------------------------------------------------------

// edge traversor can only be finite
template <
	typename Q, typename I, typename R, typename T, typename U, typename F,
	typename D, typename TR
>
class range_trav_impl <Q, I, R, T, U, F, D, TR, true, true> :
	public range_iter_base <D, TR>,
	public trav_base <D, TR, Q, U, I, I, I>
{
	using S = range_iter_base <D, TR>;
	using B = trav_base <D, TR, Q, U, I, I, I>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class range_iter_base;

//-----------------------------------------------------------------------------

	using delta = iter_elem <0, U>;
	using first = iter_elem <1, I>;
	using iter  = iter_elem <2, I>;
	using last  = iter_elem <3, I>;

	INLINE           l_iter_ref <U> u()       { return delta::get(); }
	INLINE constexpr c_iter_ref <U> u() const { return delta::get(); }

	INLINE           l_iter_ref <I> f()       { return first::get(); }
	INLINE constexpr c_iter_ref <I> f() const { return first::get(); }

	INLINE           l_iter_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_iter_ref <I> i() const { return iter::get(); }

	INLINE           l_iter_ref <I> l()       { return last::get(); }
	INLINE constexpr c_iter_ref <I> l() const { return last::get(); }

//-----------------------------------------------------------------------------

	INLINE void shift_l(key::iter) {               i() = f(); }
	INLINE void shift_r(key::iter) { if (!empty()) i() = l(); }
	INLINE void shift_l(key::edge) { if (!empty()) l() = i(); }
	INLINE void shift_r(key::edge) {               f() = i(); }

	INLINE void _swap() { if (!empty()) i() = i() == f() ? l() : f(); }

	INLINE constexpr bool empty() const { return f() == u().next(l()); }

//-----------------------------------------------------------------------------

	using S::inc;
	using S::dec;
	using S::add;
	using S::sub;
	using S::comp;

//-----------------------------------------------------------------------------

public:
	using S::operator*;
	using S::operator[];

	template <typename _U, typename _I, typename E>
	INLINE range_trav_impl(_U&& _u, _I&& i, E e) :
		B(fwd <_U>(_u), i, fwd <_I>(i), fwd <E>(e)) { u().dec(l()); }

	static constexpr bool finite = true;

	INLINE constexpr operator bool() const { return i() != u().next(l()); }

	INLINE bool operator+() const { return i() != l(); }
	INLINE bool operator-() const { return i() != f(); }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T, typename U, typename F>
struct iterator <tag::range, I, R, T, U, F> :
	range_iter_impl <I, R, T, U, F>
{
	using range_iter_impl <I, R, T, U, F>::range_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename Q, typename I, typename R, typename T, typename U, typename F>
struct traversor <tag::range, Q, I, R, T, U, F> :
	range_trav_impl <Q, I, R, T, U, F>
{
	using range_trav_impl <Q, I, R, T, U, F>::range_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_RANGE_HPP
