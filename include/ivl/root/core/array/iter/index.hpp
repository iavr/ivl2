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

#ifndef IVL_CORE_ARRAY_ITER_INDEX_HPP
#define IVL_CORE_ARRAY_ITER_INDEX_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T, typename F,
	typename D = index_trav <Q, V, R, T, F>,
	typename TR = iter_traits <V, R, T, ptrdiff_t>,
	bool = path_iter <Q>(), bool = path_edge <Q>()
>
class index_trav_impl :
	public iter_trav_impl <Q, V, R, T, D, TR>
{
	using B = iter_trav_impl <Q, V, R, T, D, TR>;

public:
	template <typename E>
	INLINE constexpr index_trav_impl(E&& e) :
		B(remove_type <V>(), fwd <E>(e)) { }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T, typename F,
	typename D, typename TR
>
class index_trav_impl <Q, V, R, T, F, D, TR, true, false> :
	public trav_trav_impl <Q, V, R, T, D, TR>
{
	using B = trav_trav_impl <Q, V, R, T, D, TR>;

public:
	INLINE constexpr index_trav_impl() : B(remove_type <V>()) { }

	template <typename E>
	INLINE constexpr index_trav_impl(E&& e) : B(fwd <E>(e)) { }
};

//-----------------------------------------------------------------------------

// edge traversor can only be finite
template <
	typename Q, typename V, typename R, typename T,
	typename D, typename TR, bool ITER
>
struct index_trav_impl <Q, V, R, T, _false, D, TR, ITER, true> :  // TODO: undefine
	index_trav_impl <Q, V, R, T, _false, D, TR, ITER, false>
{
	using index_trav_impl <Q, V, R, T, _false, D, TR, ITER, false>
		::index_trav_impl;
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D, typename TR
>
class index_trav_impl <Q, V, R, T, _false, D, TR, false, false> :
	public trav_trav_impl <Q, V, R, T, D, TR>
{
	using B = trav_trav_impl <Q, V, R, T, D, TR>;

	using B::_swap;  // disable

public:
	INLINE constexpr index_trav_impl() : B(remove_type <V>()) { }

	static constexpr bool finite = false;

	INLINE constexpr operator bool() const { return true; }
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T, typename F>
struct traversor <tag::index, Q, V, R, T, F> :
	index_trav_impl <Q, V, R, T, F>
{
	using B = index_trav_impl <Q, V, R, T, F>;
	using d = seq_diff <B>;

public:
	using B::B;

	INLINE R operator*()     const { return B::v(); }
	INLINE R operator[](d n) const { return B::v() + n; }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_INDEX_HPP
