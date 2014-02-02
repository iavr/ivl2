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

#ifndef IVL_DETAILS_CORE_ARRAY_BASE_BASE_HPP
#define IVL_DETAILS_CORE_ARRAY_BASE_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename D> class base_seq;

template <typename T, typename C>
class base_seq <T, sequence <T, C> > :
	public derived <sequence <T, C> >
{
	using S  = size_t;
	using D  = ptrdiff_t;
	using R  = T&;
	using CR = const T&;
	using P  = T*;
	using CP = const T*;
	using I  = seq_iter <T, C>;
	using CI = seq_citer <T, C>;
	using U  = iter_trav <I>;
	using CU = iter_trav <CI>;

	template <typename J> using V = rev_iter <J>;

	using B = derived <sequence <T, C> >;

//-----------------------------------------------------------------------------

	INLINE I  b()       { return der().begin(); }
	INLINE CI b() const { return der().begin(); }
	INLINE I  e()       { return der().end(); }
	INLINE CI e() const { return der().end(); }

//-----------------------------------------------------------------------------

protected:
	using B::der;

//-----------------------------------------------------------------------------

public:
	using value_type = T;
	using size_type = S;
	using difference_type = D;

	using reference = R;
	using const_reference = CR;
	using pointer = P;
	using const_pointer = CP;

	using iterator = I;
	using const_iterator = CI;
	using reverse_iterator = V <I>;
	using const_reverse_iterator = V <CI>;
	using traversor = U;
	using const_traversor = CU;

//-----------------------------------------------------------------------------

	INLINE           U  trav()        { return U(b(), e()); }
	INLINE constexpr CU trav()  const { return CU(b(), e()); }
	INLINE constexpr CU ctrav() const { return trav(); }

	INLINE V <I>  rbegin()       { return V <I>(e()); }
	INLINE V <CI> rbegin() const { return V <CI>(e()); }
	INLINE V <I>  rend()         { return V <I>(b()); }
	INLINE V <CI> rend()   const { return V <CI>(b()); }

	INLINE CI     cbegin()  const { return b(); }
	INLINE CI     cend()    const { return e(); }
	INLINE V <CI> crbegin() const { return rbegin(); }
	INLINE V <CI> crend()   const { return rend(); }

	INLINE           R  front()       { return *b(); }
	INLINE constexpr CR front() const { return *b(); }
	INLINE           R  back()        { return *(e() - 1); }
	INLINE constexpr CR back()  const { return *(e() - 1); }

//-----------------------------------------------------------------------------

	INLINE           R  operator[](S n)       { return der()._at(n); }
	INLINE constexpr CR operator[](S n) const { return der()._at(n); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_BASE_BASE_HPP
