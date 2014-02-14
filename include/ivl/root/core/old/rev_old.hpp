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

#ifndef IVL_CORE_ARRAY_ITER_REV_HPP
#define IVL_CORE_ARRAY_ITER_REV_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// TODO: remove
template <typename I>
class iterator <data::rev <>, I> :
	public iter_base <I>,
	private raw_tuple <I>
{
	using R = seq_ref <I>;
	using D = seq_diff <I>;
	using P = seq_ptr <I>;

	using B = iter_base <I>;
	using B::ref;

	using E = raw_tuple <I>;
	using iter = elem <0, I>;

	INLINE           l_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_ref <I> i() const { return iter::get(); }

public:
	using E::E;

	INLINE constexpr R operator*()  const { return ref(*i()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE iterator& operator++() { return --i(), *this; }
	INLINE iterator& operator--() { return ++i(), *this; }

	INLINE iterator operator++(int) { return iterator(i()--); }
	INLINE iterator operator--(int) { return iterator(i()++); }

	INLINE constexpr R operator[](D n) const { return ref(i()[n]); }

	INLINE iterator& operator+=(D n) { return i() -= n, *this; }
	INLINE iterator& operator-=(D n) { return i() += n, *this; }

	INLINE iterator operator+(D n) { return iterator(i() - n); }
	INLINE iterator operator-(D n) { return iterator(i() + n); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_REV_HPP
