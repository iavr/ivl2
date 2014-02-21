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

#ifndef IVL_CORE_ARRAY_STORE__PRE_FIXED__HPP
#define IVL_CORE_ARRAY_STORE__PRE_FIXED__HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, size_t N, bool C = is_cons <T>()>
class fixed_store
{
	T a[N];

protected:
	INLINE T*       data()       { return a; }
	INLINE const T* data() const { return a; }

public:
	template <typename A = int, only_if <C, A> = 0>
	INLINE constexpr fixed_store() : a{} { }

	template <typename... E, only_if <sizeof...(E) == N> = 0>
	INLINE constexpr fixed_store(E&&... e) : a{fwd <T>(e)...} { }

// 	// TODO: remove
// 	INLINE fixed_store(initializer_list <T>&& l)
// 		{ afun::seq_loop()(construct, afun::iter()(a), mv(l)); }
};

template <typename T, bool C>
struct fixed_store <T, 0, C>
{
protected:
	INLINE T*       data()       { return nullptr; }
	INLINE const T* data() const { return nullptr; }
};

//-----------------------------------------------------------------------------

// extending definition @array/type/sequence
template <typename T, size_t N>
struct seq_data_t <pre_fixed_array <T, N> > : pack <fixed_store <T, N> > { };

//-----------------------------------------------------------------------------

template <typename T, size_t N>
class sequence <tag::pre_fixed, T, sizes <N> > :
	public seq_base <pre_fixed_array <T, N>, seq_traits <T, size <N> > >,
	fixed_store <T, N>
{
	using TR = seq_traits <T, types::size <N> >;
	using B = seq_base <pre_fixed_array <T, N>, TR>;
	using S = fixed_store <T, N>;
	friend B;

	using IR = r_iter <TR>;
	using IL = l_iter <TR>;
	using IC = c_iter <TR>;

	using VR = r_trav <TR>;
	using VL = l_trav <TR>;
	using VC = c_trav <TR>;

	using F = tag::flip;

//-----------------------------------------------------------------------------

	INLINE T*       b()       { return S::data(); }
	INLINE const T* b() const { return S::data(); }
	INLINE T*       e()       { return S::data() + N; }
	INLINE const T* e() const { return S::data() + N; }

//-----------------------------------------------------------------------------

public:
	using S::S;

	INLINE constexpr size_t size() const { return N; }

	INLINE           IR begin() &&     { return IR(b()); }
	INLINE           IL begin() &      { return IL(b()); }
	INLINE constexpr IC begin() const& { return IC(b()); }

	INLINE           IR end() &&     { return IR(e()); }
	INLINE           IL end() &      { return IL(e()); }
	INLINE constexpr IC end() const& { return IC(e()); }

	INLINE           IR data() &&     { return IR(b()); }
	INLINE           IL data() &      { return IL(b()); }
	INLINE constexpr IC data() const& { return IC(b()); }

//-----------------------------------------------------------------------------

	template <typename... G>
	INLINE VR trav(G...) && { return VR(b(), e()); }

	template <typename... G>
	INLINE VL trav(G...) & { return VL(b(), e()); }

	template <typename... G>
	INLINE constexpr VC trav(G...) const& { return VC(b(), e()); }

//-----------------------------------------------------------------------------

	INLINE           VR trav(F) &&     { return VR(e()-1, b()-1); }
	INLINE           VL trav(F) &      { return VL(e()-1, b()-1); }
	INLINE constexpr VC trav(F) const& { return VC(e()-1, b()-1); }

};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_STORE__PRE_FIXED__HPP
