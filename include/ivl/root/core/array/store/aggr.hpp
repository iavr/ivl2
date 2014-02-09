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

#ifndef IVL_CORE_ARRAY_STORE_AGGR_HPP
#define IVL_CORE_ARRAY_STORE_AGGR_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, size_t N>
struct aggr_store_t : id_t <T[N]> { };

template <typename T>
struct aggr_store_t <T, 0> { struct type { }; };

template <typename T, size_t N>
using aggr_store = type_of <aggr_store_t <T, N> >;

template <typename T, size_t N>
INLINE T* aggr_ptr(T (&a)[N]) { return a; }

template <typename T, size_t N>
INLINE const T* aggr_ptr(const T (&a)[N]) { return a; }

template <typename T, typename A>
INLINE T* aggr_ptr(A&&) { return nullptr; }

//-----------------------------------------------------------------------------

template <typename T, size_t N>
class sequence <data::aggr <>, T, sizes <N> >
{
	using R  = T&;
	using CR = const T&;
	using I  = T*;
	using CI = const T*;
	using U  = iter_trav <T*, R>;
	using CU = iter_trav <const T*, CR>;

	template <typename J> using V = rev_iter <J>;

//-----------------------------------------------------------------------------

public:
	aggr_store <T, N> a;

	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;

	using traversor = U;
	using const_traversor = CU;
	using iterator = I;
	using const_iterator = CI;
	using reverse_iterator = V <I>;
	using const_reverse_iterator = V <CI>;

	static constexpr bool finite = true;

//-----------------------------------------------------------------------------

	INLINE           U  trav()        { return U(begin(), end()); }
	INLINE constexpr CU trav()  const { return CU(begin(), end()); }
	INLINE constexpr CU ctrav() const { return trav(); }

	INLINE I  begin()       { return data(); }
	INLINE CI begin() const { return data(); }
	INLINE I  end()         { return data() + N; }
	INLINE CI end()   const { return data() + N; }

	INLINE V <I>  rbegin()       { return V <I> (end() - 1); }
	INLINE V <CI> rbegin() const { return V <CI>(end() - 1); }
	INLINE V <I>  rend()         { return V <I> (begin() - 1); }
	INLINE V <CI> rend()   const { return V <CI>(begin() - 1); }

	INLINE CI     cbegin()  const { return begin(); }
	INLINE CI     cend()    const { return end(); }
	INLINE V <CI> crbegin() const { return rbegin(); }
	INLINE V <CI> crend()   const { return rend(); }

	INLINE constexpr size_t size()     const { return N; }
	INLINE constexpr size_t max_size() const { return N; }
	INLINE constexpr bool   empty()    const { return N == 0; }

	INLINE           R  operator[](size_t n)       { return data()[n]; }
	INLINE constexpr CR operator[](size_t n) const { return data()[n]; }

	INLINE           R  front()       { return *begin(); }
	INLINE constexpr CR front() const { return *begin(); }
	INLINE           R  back()        { return *(end() - 1); }
	INLINE constexpr CR back()  const { return *(end() - 1); }

	INLINE T*       data()       { return aggr_ptr <T>(a); }
	INLINE const T* data() const { return aggr_ptr <T>(a); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_STORE_AGGR_HPP
