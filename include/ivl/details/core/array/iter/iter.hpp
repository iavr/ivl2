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
	typename I, typename R = it_ref <I>, typename T = it_val <I>,
	typename D = it_diff <I>, typename P = it_ptr <I>
>
struct base_iter
{
	using iterator_type = I;
	using reference = R;
	using value_type = T;
	using difference_type = D;
	using pointer = P;
};

//-----------------------------------------------------------------------------

template <
	bool F, typename I, typename R = it_ref <I>, typename T = it_val <I>,
	typename D = it_diff <I>, typename P = it_ptr <I>
>
struct base_trav : base_iter <I, R, T, D, P>
{
	static constexpr bool finite = F;
};

//-----------------------------------------------------------------------------

template <typename I>
class iterator <data::rev <>, I> : public base_iter <I>
{
	using T = it_val <I>;
	using R = it_ref <T>;
	using D = it_diff <I>;
	using P = it_ptr <I>;

	I i;

public:
	INLINE constexpr explicit iterator(I&& i) : i(mv(i)) { }
	INLINE constexpr explicit iterator(const I& i) : i(i) { }

	INLINE constexpr R operator*()  const { return *--I(i); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE iterator& operator++() { return --i, *this; }
	INLINE iterator& operator--() { return ++i, *this; }

	INLINE iterator operator++(int) { return iterator(i--); }
	INLINE iterator operator--(int) { return iterator(i++); }

	INLINE constexpr R operator[](D n) const { return *(i - n); }

	INLINE iterator& operator+=(D n) { return i -= n, *this; }
	INLINE iterator& operator-=(D n) { return i += n, *this; }

	INLINE iterator operator+(D n) { return iterator(i - n); }
	INLINE iterator operator-(D n) { return iterator(i + n); }

	INLINE I&&      base() &&     { return i; }
	INLINE I&       base() &      { return i; }
	INLINE const I& base() const& { return i; }
};

//-----------------------------------------------------------------------------

template <typename I, typename R>
class iterator <data::iter <>, I, R> : public base_iter <I, R>
{
	using T = it_val <I>;
	using D = it_diff <I>;
	using P = it_ptr <I>;

	I i;

public:
	INLINE constexpr explicit iterator(I&& i) : i(mv(i)) { }
	INLINE constexpr explicit iterator(const I& i) : i(i) { }

	INLINE constexpr R operator*()  const { return *i; }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE iterator& operator++() { return ++i, *this; }
	INLINE iterator& operator--() { return --i, *this; }

	INLINE iterator operator++(int) { return iterator(i++); }
	INLINE iterator operator--(int) { return iterator(i--); }

	INLINE constexpr R operator[](D n) const { return i[n]; }

	INLINE iterator& operator+=(D n) { return i += n, *this; }
	INLINE iterator& operator-=(D n) { return i -= n, *this; }

	INLINE iterator operator+(D n) { return iterator(i + n); }
	INLINE iterator operator-(D n) { return iterator(i - n); }

	INLINE I&&      base() &&     { return i; }
	INLINE I&       base() &      { return i; }
	INLINE const I& base() const& { return i; }
};

//-----------------------------------------------------------------------------

template <typename I, typename R>
class traversor <data::iter <>, I, R> : public base_trav <true, I, R>
{
	using T = it_val <I>;
	using D = it_diff <I>;
	using P = it_ptr <I>;

	I i, e;

public:
	template <typename J, typename E>
	INLINE constexpr explicit traversor(J&& j, E&& e) :
		i(fwd <J>(j)), e(fwd <E>(e)) { }

	INLINE constexpr operator bool()  const { return i != e; }

	INLINE constexpr R operator*()  const { return *i; }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE traversor& operator++() { return ++i, *this; }
	INLINE traversor& operator--() { return --i, *this; }

	INLINE traversor operator++(int) { return traversor(i++, e); }
	INLINE traversor operator--(int) { return traversor(i--, e); }

	INLINE constexpr R operator[](D n) const { return i[n]; }

	INLINE traversor& operator+=(D n) { return i += n, *this; }
	INLINE traversor& operator-=(D n) { return i -= n, *this; }

	INLINE traversor operator+(D n) { return traversor(i + n, e); }
	INLINE traversor operator-(D n) { return traversor(i - n, e); }
};

//-----------------------------------------------------------------------------

template <typename U>
class traversor <data::atom <>, U> :
	public base_trav <false, remove_ref <U>*>,
	private raw_tuple <uref_opt <U> >
{
	using T = uref_opt <U>;
	using B = raw_tuple <T>;
	using F = remove_ref <U>;
	using P = F*;
	using PC = _if <is_lref <T>{}, F*, const F*>;

public:
	INLINE constexpr explicit traversor(T&& a) : B(fwd <T>(a)) { }

	INLINE constexpr operator bool()  const { return true; }

	INLINE           rtref <T>  operator*() &&     { return B::val_f(); }
	INLINE           ltref <T>  operator*() &      { return B::val(); }
	INLINE constexpr cltref <T> operator*() const& { return B::val(); }

	INLINE           P  operator->()       { return &(operator*()); }
	INLINE           PC operator->() const { return &(operator*()); }

	INLINE traversor& operator++() { return *this; }
	INLINE traversor& operator--() { return *this; }

	INLINE traversor& operator++(int) { return *this; }
	INLINE traversor& operator--(int) { return *this; }

	INLINE           rtref <T>  operator[](ptrdiff_t n) &&     { return B::val_f(); }
	INLINE           ltref <T>  operator[](ptrdiff_t n) &      { return B::val(); }
	INLINE constexpr cltref <T> operator[](ptrdiff_t n) const& { return B::val(); }

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
