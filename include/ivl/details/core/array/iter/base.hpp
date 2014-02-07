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

#ifndef IVL_CORE_ARRAY_ITER_BASE_HPP
#define IVL_CORE_ARRAY_ITER_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename I, typename R = seq_ref <I>, typename T = seq_val <I>,
	typename D = seq_diff <I>, typename P = seq_ptr <I>
>
struct base_iter
{
	using iterator_type = I;
	using reference = R;
	using value_type = T;
	using difference_type = D;
	using pointer = P;

protected:
	INLINE constexpr R ref(seq_ref <I> r) const { return static_cast <R>(r); }
};

//-----------------------------------------------------------------------------

template <
	bool F, typename I, typename R = seq_ref <I>, typename T = seq_val <I>,
	typename D = seq_diff <I>, typename P = seq_ptr <I>
>
struct base_trav : base_iter <I, R, T, D, P>
{
	static constexpr bool finite = F;
};

//-----------------------------------------------------------------------------

template <typename I>
class iterator <data::rev <>, I> : public base_iter <I>
{
	using R = seq_ref <I>;
	using D = seq_diff <I>;
	using P = seq_ptr <I>;

	using B = base_iter <I>;
	using B::ref;

	I i;

public:
	INLINE constexpr explicit iterator(I&& i) : i(mv(i)) { }
	INLINE constexpr explicit iterator(const I& i) : i(i) { }

	INLINE constexpr R operator*()  const { return ref(*i); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE iterator& operator++() { return --i, *this; }
	INLINE iterator& operator--() { return ++i, *this; }

	INLINE iterator operator++(int) { return iterator(i--); }
	INLINE iterator operator--(int) { return iterator(i++); }

	INLINE constexpr R operator[](D n) const { return ref(i[n]); }

	INLINE iterator& operator+=(D n) { return i -= n, *this; }
	INLINE iterator& operator-=(D n) { return i += n, *this; }

	INLINE iterator operator+(D n) { return iterator(i - n); }
	INLINE iterator operator-(D n) { return iterator(i + n); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_BASE_HPP
