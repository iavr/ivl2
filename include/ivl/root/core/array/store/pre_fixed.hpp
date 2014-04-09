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
	using E = seq_elem <T>;

	E a[N];

protected:
	INLINE E*       data()       { return a; }
	INLINE const E* data() const { return a; }

public:
	template <typename A = int, only_if <C, A> = 0>
	INLINE constexpr fixed_store() : a{} { }

	template <typename... A, only_if <sizeof...(A) == N> = 0>
	INLINE constexpr fixed_store(A&&... a) : a{static_cast <T>(fwd <A>(a))...} { }

// 	// TODO: remove
// 	INLINE fixed_store(initializer_list <T>&& l)
// 		{ afun::seq_loop()(construct, afun::iter()(a), mv(l)); }
};

template <typename T, bool C>
struct fixed_store <T, 0, C>
{
	using E = seq_elem <T>;

protected:
	INLINE E*       data()       { return nullptr; }
	INLINE const E* data() const { return nullptr; }
};

//-----------------------------------------------------------------------------

// extending definition @array/type/sequence
template <typename T, size_t N>
struct seq_data_t <pre_fixed_array <T, N> > : pack <fixed_store <T, N> > { };

//-----------------------------------------------------------------------------

template <
	typename T, size_t N,
	typename D = pre_fixed_array <T, N>,
	typename TR = seq_traits <T, sizes <N> >
>
class pre_fixed_seq_impl :
	public seq_base <D, TR>,
	fixed_store <T, N>
{
	using B = seq_base <D, TR>;
	using S = fixed_store <T, N>;
	friend B;

	using IR = r_seq_iter <TR>;
	using IL = l_seq_iter <TR>;
	using IC = c_seq_iter <TR>;

	template <typename Q> using VR = r_seq_trav <TR, Q>;
	template <typename Q> using VL = l_seq_trav <TR, Q>;
	template <typename Q> using VC = c_seq_trav <TR, Q>;

//-----------------------------------------------------------------------------

	using E = seq_elem <T>;

	INLINE E*       b()       { return S::data(); }
	INLINE const E* b() const { return S::data(); }
	INLINE E*       e()       { return S::data() + N; }
	INLINE const E* e() const { return S::data() + N; }

//-----------------------------------------------------------------------------

	template <typename Q>
	INLINE VR <Q> _trav() && { return VR <Q>(b(), e()); }

	template <typename Q>
	INLINE VL <Q> _trav() & { return VL <Q>(b(), e()); }

	template <typename Q>
	INLINE constexpr VC <Q> _trav() const& { return VC <Q>(b(), e()); }

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

};

//-----------------------------------------------------------------------------

template <typename T, size_t N>
class sequence <tag::pre_fixed, T, sizes <N> > :
	public pre_fixed_seq_impl <T, N>
{
	using B = pre_fixed_seq_impl <T, N>;

public:
	using B::B;
	using B::base_type::operator=;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_STORE__PRE_FIXED__HPP
