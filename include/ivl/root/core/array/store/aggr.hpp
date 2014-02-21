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
class sequence <tag::aggr, T, sizes <N> >
{
	using RR = T&&;
	using RL = T&;
	using RC = const T&;

	using PL = T*;
	using PC = const T*;

	using IR = iter_iter <PL, RR, T>;
	using IL = iter_iter <PL, RL, T>;
	using IC = iter_iter <PC, RC, T>;

	using VR = iter_trav <PL, RR, T>;
	using VL = iter_trav <PL, RL, T>;
	using VC = iter_trav <PC, RC, T>;

//-----------------------------------------------------------------------------

	INLINE RR f(RL r) { return fwd <RR>(r); }

//-----------------------------------------------------------------------------

	INLINE PL b()       { return data(); }
	INLINE PC b() const { return data(); }
	INLINE PL e()       { return data() + N; }
	INLINE PC e() const { return data() + N; }

//-----------------------------------------------------------------------------

public:
	aggr_store <T, N> a;

	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

	using fwd_reference   = RR;
	using reference       = RL;
	using const_reference = RC;

	using pointer       = PL;
	using const_pointer = PC;

	using fwd_iterator   = IR;
	using iterator       = IL;
	using const_iterator = IC;

	using fwd_traversor   = VR;
	using traversor       = VL;
	using const_traversor = VC;

	static constexpr bool   finite = true;
	static constexpr bool   fixed  = true;
	static constexpr size_t length = N;

//-----------------------------------------------------------------------------

	INLINE constexpr size_t size()     const { return N; }
	INLINE constexpr size_t max_size() const { return N; }
	INLINE constexpr bool   empty()    const { return N == 0; }

	INLINE           IR begin() &&     { return IR(b()); }
	INLINE           IL begin() &      { return IL(b()); }
	INLINE constexpr IC begin() const& { return IC(b()); }

	INLINE           IR end() &&     { return IR(e()); }
	INLINE           IL end() &      { return IL(e()); }
	INLINE constexpr IC end() const& { return IC(e()); }

	INLINE           VR trav() &&     { return VR(b(), e()); }
	INLINE           VL trav() &      { return VL(b(), e()); }
	INLINE constexpr VC trav() const& { return VC(b(), e()); }

	INLINE           RR operator[](size_t n) &&     { return f(b()[n]); }
	INLINE           RL operator[](size_t n) &      { return b()[n]; }
	INLINE constexpr RC operator[](size_t n) const& { return b()[n]; }

	INLINE           RR front() &&     { return f(*b()); }
	INLINE           RL front() &      { return *b(); }
	INLINE constexpr RC front() const& { return *b(); }

	INLINE           RR back() &&     { return f(*(e() - 1)); }
	INLINE           RL back() &      { return *(e() - 1); }
	INLINE constexpr RC back() const& { return *(e() - 1); }

	INLINE PL data()       { return aggr_ptr <T>(a); }
	INLINE PC data() const { return aggr_ptr <T>(a); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_STORE_AGGR_HPP
