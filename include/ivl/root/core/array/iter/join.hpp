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

#ifndef IVL_CORE_ARRAY_ITER_JOIN_HPP
#define IVL_CORE_ARRAY_ITER_JOIN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename V, typename R, typename T,
	typename N = sz_rng_of_p <V>, typename D = join_iter <V, R, T>,
	typename TR = iter_traits <V, R, T>
>
struct join_iter_impl;

//-----------------------------------------------------------------------------

template <
	typename... V, typename R, typename T,
	size_t... N, typename D, typename TR
>
class join_iter_impl <pack <V...>, R, T, sizes <N...>, D, TR> :
	public iter_base <D, TR, V...>
{
	using B = iter_base <D, TR, V...>;
	using d = seq_diff <TR>;
	using P = seq_ptr <TR>;

	template <size_t K>
	using trav = iter_elem_at <K, V...>;

	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

	static constexpr size_t L = sizeof...(V);
	size_t k;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return trav <K>::get(); }

//-----------------------------------------------------------------------------

	template <size_t J, size_t K>
	INLINE l_iter_pick <J, V...>
	inc() { return J == K ? v<J>()++ : v<J>(); }

	template <size_t J, size_t K>
	INLINE l_iter_pick <J, V...>
	dec() { return J == K ? v<J>()-- : v<J>(); }

//-----------------------------------------------------------------------------

	struct deref { };
	struct inc_l { };
	struct dec_l { };
	struct inc_r { };
	struct dec_r { };

	template <size_t K> INLINE R    _(deref) const { return *v<K>(); }

	template <size_t K> INLINE void _(inc_l) { ++v<K>() ? k : ++k; }
	template <size_t K> INLINE void _(dec_l) { --v<K>() ? k : ++k; }
	template <size_t K> INLINE D    _(inc_r) { return D(k, inc <N, K>()...); }
	template <size_t K> INLINE D    _(dec_r) { return D(k, dec <N, K>()...); }

	template <typename OP> using   op = afun::lookup_op <L, OP>;
	template <typename OP> friend class afun::lookup_op_fun;

//-----------------------------------------------------------------------------

public:
	template <typename... A>
	INLINE constexpr join_iter_impl(size_t k, A&&... a) :
		k(k), B(fwd <A>(a)...) { }

	INLINE constexpr R operator*()  const { return op <deref>()(k, der()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D&& operator++() && { return op <inc_l>()(k, der_f()), der_f(); }
	INLINE D&  operator++() &  { return op <inc_l>()(k, der()),   der(); }
	INLINE D&& operator--() && { return op <dec_l>()(k, der_f()), der_f(); }
	INLINE D&  operator--() &  { return op <dec_l>()(k, der()),   der(); }

	INLINE D operator++(int) { return op <inc_r>()(k, der()); }
	INLINE D operator--(int) { return op <dec_r>()(k, der()); }

// 	// TODO : lookup binary OP
// 	INLINE bool operator!=(D o) { return k != o.k || ...; }
};

//-----------------------------------------------------------------------------

template <
	typename V, typename R, typename T,
	typename N = sz_rng_of_p <V>, typename D = join_trav <V, R, T>,
	typename TR = iter_traits <V, R, T>
>
struct join_trav_impl;

template <
	typename... V, typename R, typename T,
	size_t... N, typename D, typename TR
>
class join_trav_impl <pack <V...>, R, T, sizes <N...>, D, TR> :
	public trav_base <D, TR, V...>
{
	using B = trav_base <D, TR, V...>;
	using d = seq_diff <B>;
	using P = seq_ptr <B>;

	template <size_t K>
	using trav = iter_elem_at <K, V...>;

	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

	static constexpr size_t L = sizeof...(V);
	size_t k;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return trav <K>::get(); }

//-----------------------------------------------------------------------------

	template <size_t J, size_t K>
	INLINE l_iter_pick <J, V...>
	inc() { return J == K ? v<J>()++ : v<J>(); }  // TODO: k++

	template <size_t J, size_t K>
	INLINE l_iter_pick <J, V...>
	dec() { return J == K ? v<J>()-- : v<J>(); }  // TODO: k--

//-----------------------------------------------------------------------------

	struct more { };
	struct deref { };
	struct inc_l { };
	struct dec_l { };
	struct inc_r { };
	struct dec_r { };

	template <size_t K> INLINE bool _(more)  const { return v<K>(); }
	template <size_t K> INLINE R    _(deref) const { return *v<K>(); }

	template <size_t K> INLINE void _(inc_l) { ++v<K>() ? k : ++k; }
	template <size_t K> INLINE void _(dec_l) { --v<K>() ? k : --k; }  // TODO: make "--v<K>() ?" work
	template <size_t K> INLINE D    _(inc_r) { return D(k, inc <N, K>()...); }
	template <size_t K> INLINE D    _(dec_r) { return D(k, dec <N, K>()...); }

	template <typename OP> using   op = afun::lookup_op <L, OP>;
	template <typename OP> friend class afun::lookup_op_fun;

//-----------------------------------------------------------------------------

public:
	template <typename... A>
	INLINE constexpr join_trav_impl(size_t k, A&&... a) :
		k(k), B(fwd <A>(a)...) { }

	// TODO: finite atom (unit)
	static constexpr bool finite = _and <fin_trav <V>...>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return op <more>()(k, der()); }

	INLINE constexpr R operator*()  const { return op <deref>()(k, der()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D&& operator++() && { return op <inc_l>()(k, der_f()), der_f(); }
	INLINE D&  operator++() &  { return op <inc_l>()(k, der()),   der(); }
	INLINE D&& operator--() && { return op <dec_l>()(k, der_f()), der_f(); }
	INLINE D&  operator--() &  { return op <dec_l>()(k, der()),   der(); }

	INLINE D operator++(int) { return op <inc_r>()(k, der()); }
	INLINE D operator--(int) { return op <dec_r>()(k, der()); }
};

//-----------------------------------------------------------------------------

template <typename V, typename R, typename T>
struct iterator <tag::join, V, R, T> :
	join_iter_impl <V, R, T>
{
	using join_iter_impl <V, R, T>::join_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename V, typename R, typename T>
struct traversor <tag::join, V, R, T> :
	join_trav_impl <V, R, T>
{
	using join_trav_impl <V, R, T>::join_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_JOIN_HPP
