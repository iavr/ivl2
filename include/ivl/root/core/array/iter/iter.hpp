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
class edge_trav_base : public derived <D, edge_path <> >
{
	using derived <D, edge_path <> >::der;

//-----------------------------------------------------------------------------

protected:
	INLINE void shift_l(key::iter) {               der().v() = der().f(); }
	INLINE void shift_r(key::iter) { if (!empty()) der().v() = der().l(); }
	INLINE void shift_l(key::edge) { if (!empty()) der().l() = der().v(); }
	INLINE void shift_r(key::edge) {               der().f() = der().v(); }

	INLINE void _swap()
	{
		if (!empty()) der().v() = der().v() == der().f() ? der().l() : der().f();
	}

	INLINE constexpr bool empty() const { return der().f() == der().end(); }

//-----------------------------------------------------------------------------

public:
	INLINE constexpr operator bool() const { return der().v() != der().end(); }

	INLINE bool operator+() const { return der().v() != der().l(); }
	INLINE bool operator-() const { return der().v() != der().f(); }
};

//-----------------------------------------------------------------------------

template <typename D, typename TR>
struct iter_trav_base : trav_trav_base <D, TR>
{
	static constexpr bool finite = true;
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D = iter_trav <Q, V, R, T>,
	typename TR = iter_traits <V, R, T>,
	bool = path_iter <Q>(), bool = path_edge <Q>()
>
struct iter_trav_impl : trav_trav_impl <Q, V, R, T, D, TR>
{
	using trav_trav_impl <Q, V, R, T, D, TR>::trav_trav_impl;
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D, typename TR
>
class iter_trav_impl <Q, V, R, T, D, TR, false, false> :
	public iter_trav_base <D, TR>,
	public trav_base <D, TR, Q, V, V>
{
	using S = iter_trav_base <D, TR>;
	using B = trav_base <D, TR, Q, V, V>;

	friend base_type_of <B>;
	friend base_trav_of <B>;

	template <typename, typename>
	friend class trav_trav_base;

//-----------------------------------------------------------------------------

	using iter = iter_elem <0, V>;
	using end  = iter_elem <1, V>;

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

	INLINE constexpr operator bool() const { return v() != e(); }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D, typename TR, bool ITER
>
class iter_trav_impl <Q, V, R, T, D, TR, ITER, true> :
	public edge_trav_base <D, TR>,
	public iter_trav_base <D, TR>,
	public trav_base <D, TR, Q, V, V, V>
{
	using E = edge_trav_base <D, TR>;
	using S = iter_trav_base <D, TR>;
	using B = trav_base <D, TR, Q, V, V, V>;

	friend base_type_of <B>;
	friend base_trav_of <B>;

	template <typename, typename> friend class edge_trav_base;
	template <typename, typename> friend class trav_trav_base;

//-----------------------------------------------------------------------------

	using first = iter_elem <0, V>;
	using iter  = iter_elem <1, V>;
	using last  = iter_elem <2, V>;

	INLINE           l_iter_ref <V> f()       { return first::get(); }
	INLINE constexpr c_iter_ref <V> f() const { return first::get(); }

	INLINE           l_iter_ref <V> v()       { return iter::get(); }
	INLINE constexpr c_iter_ref <V> v() const { return iter::get(); }

	INLINE           l_iter_ref <V> l()       { return last::get(); }
	INLINE constexpr c_iter_ref <V> l() const { return last::get(); }

	INLINE constexpr iter_val <V> end() const { return l() + 1; }

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

	template <typename _V, typename E>
	INLINE iter_trav_impl(_V&& v, E&& e) :
		B(v, fwd <_V>(v), fwd <E>(e)) { --l(); }
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

#endif  // IVL_CORE_ARRAY_ITER_ITER_HPP
