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

#ifndef IVL_DETAILS_CORE_ARRAY_ITER_ITER_HPP
#define IVL_DETAILS_CORE_ARRAY_ITER_ITER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename I, typename T = it_val <I>, typename D = it_diff <I>,
	typename R = it_ref <I>, typename P = it_ptr <I>
>
struct base_iter
{
	using iterator_type = I;
	using value_type = T;
	using difference_type = D;
	using reference = R;
	using pointer = P;
};

//-----------------------------------------------------------------------------

template <
	typename I, typename T = it_val <I>, typename D = it_diff <I>,
	typename R = it_ref <I>, typename P = it_ptr <I>, bool F = true
>
struct base_trav : base_iter <I, T, D, R, P>
{
	static constexpr bool finite = F;
};

//-----------------------------------------------------------------------------

template <typename I>
class iterator <I, data::rev <> > : public base_iter <I>
{
	using T = it_val <I>;
	using D = it_diff <I>;
	using R = it_ref <I>;
	using P = it_ptr <I>;

	I p;

public:
	INLINE constexpr explicit iterator(I p) : p(p) { }

	INLINE constexpr R operator*()  const { return *--I(p); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE iterator& operator++() { return --p, *this; }
	INLINE iterator& operator--() { return ++p, *this; }

	INLINE iterator& operator++(int) { return iterator(p--); }
	INLINE iterator& operator--(int) { return iterator(p++); }

	INLINE constexpr R operator[](D n) const { return *(p - n); }

	INLINE iterator& operator+=(D n) { return p -= n, *this; }
	INLINE iterator& operator-=(D n) { return p += n, *this; }

	INLINE iterator& operator+(D n) { return iterator(p - n); }
	INLINE iterator& operator-(D n) { return iterator(p + n); }

	INLINE I base() const { return p; }
};

//-----------------------------------------------------------------------------

template <typename I>
class iterator <I, data::iter <> > : public base_iter <I>
{
	using T = it_val <I>;
	using D = it_diff <I>;
	using R = it_ref <I>;
	using P = it_ptr <I>;

	I p;

public:
	INLINE constexpr explicit iterator(I p) : p(p) { }

	INLINE constexpr R operator*()  const { return *p; }
	INLINE           P operator->() const { return p; }

	INLINE iterator& operator++() { return ++p, *this; }
	INLINE iterator& operator--() { return --p, *this; }

	INLINE iterator& operator++(int) { return iterator(p++); }
	INLINE iterator& operator--(int) { return iterator(p--); }

	INLINE constexpr R operator[](D n) const { return p[n]; }

	INLINE iterator& operator+=(D n) { return p += n, *this; }
	INLINE iterator& operator-=(D n) { return p -= n, *this; }

	INLINE iterator& operator+(D n) { return iterator(p + n); }
	INLINE iterator& operator-(D n) { return iterator(p - n); }

	INLINE I base() const { return p; }
};

//-----------------------------------------------------------------------------

template <typename I>
class traversor <I, data::iter <> > : public base_trav <I>
{
	using T = it_val <I>;
	using D = it_diff <I>;
	using R = it_ref <I>;
	using P = it_ptr <I>;

	I p, e;

public:
	INLINE constexpr explicit traversor(I p, I e) : p(p), e(e) { }

	INLINE constexpr operator bool()  const { return p != e; }

	INLINE constexpr R operator*()  const { return *p; }
	INLINE           P operator->() const { return p; }

	INLINE traversor& operator++() { return ++p, *this; }
	INLINE traversor& operator--() { return --p, *this; }

	INLINE traversor& operator++(int) { return traversor(p++, e); }
	INLINE traversor& operator--(int) { return traversor(p--, e); }

	INLINE constexpr R operator[](D n) const { return p[n]; }

	INLINE traversor& operator+=(D n) { return p += n, *this; }
	INLINE traversor& operator-=(D n) { return p -= n, *this; }

	INLINE traversor& operator+(D n) { return traversor(p + n, e); }
	INLINE traversor& operator-(D n) { return traversor(p - n, e); }
};

//-----------------------------------------------------------------------------

template <typename T>
class traversor <T, data::atom <> >
{
	using F = remove_ref <T>;
	T&& a;

public:
	using iterator_type = F*;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using reference = T&;
	using pointer = F*;
	static constexpr bool finite = false;

	INLINE constexpr explicit traversor(T&& a) : a(fwd <T>(a)) { }

	INLINE constexpr operator bool()  const { return true; }

	INLINE constexpr T&& operator*() const { return fwd <T>(a); }
	INLINE           F* operator->() const { return &fwd <T>(a); }

	INLINE traversor& operator++() { return *this; }
	INLINE traversor& operator--() { return *this; }

	INLINE traversor& operator++(int) { return *this; }
	INLINE traversor& operator--(int) { return *this; }

	INLINE constexpr T&& operator[](ptrdiff_t n) const { return fwd <T>(a); }

	INLINE traversor& operator+=(ptrdiff_t n) { return *this; }
	INLINE traversor& operator-=(ptrdiff_t n) { return *this; }

	INLINE traversor& operator+(ptrdiff_t n) { return *this; }
	INLINE traversor& operator-(ptrdiff_t n) { return *this; }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_ITER_ITER_HPP
