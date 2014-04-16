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
   MERCHANTABILITY or FITNESS FOR A PArTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_ARRAY_ITER_ATOM_HPP
#define IVL_CORE_ARRAY_ITER_ATOM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename TR>
class atom_trav_base : public derived <D, _false>
{
	using derived <D, _false>::der;

	using R = seq_iref <TR>;
	using d = seq_diff <TR>;

//-----------------------------------------------------------------------------

protected:
	INLINE void inc() { }
	INLINE void dec() { }

	INLINE void add(d n) { }
	INLINE void sub(d n) { }

	template <typename O>
	INLINE constexpr bool comp(afun::op::eq, O&&) const { return false; }

	template <typename O>
	INLINE constexpr bool comp(afun::op::neq, O&&) const { return true; }

//-----------------------------------------------------------------------------

public:
	INLINE constexpr R operator*() const
		{ return der().cast(der().val()); }

	INLINE constexpr R operator[](d n) const
		{ return der().cast(der().val()); }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D = atom_trav <Q, V, R, T>,
	typename TR = iter_traits <V, R, T, ptrdiff_t>,
	bool = path_iter <Q>(), bool = path_finite <Q>()
>
class atom_trav_impl :
	public atom_trav_base <D, TR>,
	public iter_base <D, TR, R>
{
	using S = atom_trav_base <D, TR>;
	using B = iter_base <D, TR, R>;

	friend base_type_of <B>;

	template <typename, typename>
	friend class atom_trav_base;

	using B::val;
	using B::cast;

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
class atom_trav_impl <Q, V, R, T, D, TR, false, false> :
	public atom_trav_base <D, TR>,
	public trav_base <D, TR, Q, R>
{
	using S = atom_trav_base <D, TR>;
	using B = trav_base <D, TR, Q, R>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class atom_trav_base;

	using B::val;
	using B::cast;

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

	INLINE bool operator+() const { return true; }
	INLINE bool operator-() const { return true; }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D, typename TR
>
struct atom_trav_impl <Q, V, R, T, D, TR, false, true> :
	public atom_trav_base <D, TR>,
	public trav_base <D, TR, Q, R>
{
	using S = atom_trav_base <D, TR>;
	using B = trav_base <D, TR, Q, R>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename>
	friend class atom_trav_base;

	using d = seq_diff <TR>;

	using B::val;
	using B::cast;

//-----------------------------------------------------------------------------

	size_t k = 0;

//-----------------------------------------------------------------------------

	INLINE void inc() { ++k; }
	INLINE void dec() { --k; }

	INLINE void add(d n) { k += n; }
	INLINE void sub(d n) { k -= n; }

	template <typename F, typename O>
	INLINE constexpr bool
	comp(F f, O&& o) const { return f(k, o.k); }

	template <typename O>
	INLINE constexpr d
	comp(afun::op::sub, O&& o) const { return k - o.k; }

//-----------------------------------------------------------------------------

public:
	using B::B;
	using S::operator*;
	using S::operator[];

	static constexpr bool finite = true;

	INLINE constexpr operator bool() const { return k != 1; }

	INLINE bool operator+() const { return k != 0; }
	INLINE bool operator-() const { return k != 0; }
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T>
struct traversor <tag::atom, Q, V, R, T> :
	atom_trav_impl <Q, V, R, T>
{
	using atom_trav_impl <Q, V, R, T>::atom_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_ATOM_HPP
