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
	typename D = join_iter <V, R, T>,
	typename TR = iter_traits <V, R, T>,
	typename N = sz_rng_of_p <V>
>
struct join_iter_impl;

//-----------------------------------------------------------------------------

template <
	typename... V, typename R, typename T,
	typename D, typename TR, size_t... N
>
class join_iter_impl <pack <V...>, R, T, D, TR, sizes <N...> > :
	public iter_base <D, TR, V...>
{
	using B = iter_base <D, TR, V...>;
	using d = seq_diff <TR>;
	using P = seq_ptr <TR>;

	template <size_t K>
	using trav = iter_elem_at <K, V...>;

	using derived <D>::der_f;
	using derived <D>::der;

	using B::cast;

//-----------------------------------------------------------------------------

	size_t k;

	static constexpr size_t M = size_t(-1);
	static constexpr size_t L = sizeof...(V);

	using SM = size <M>;
	using SL = size <L>;

	template <typename OP> using   op = afun::lookup_op <0, L-1, OP>;
	template <typename OP> friend class afun::lookup_op_fun;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return trav <K>::get(); }

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void next(size <K>, _true = yes) { ++k, next(size <K + 1>(), no); }

	template <size_t K>
	INLINE void prev(size <K>, _true = yes) { --k, prev(size <K - 1>(), no); }

	template <size_t K>
	INLINE void next(size <K> s, _false) { if (!v<K>()) next(s); }

	template <size_t K>
	INLINE void prev(size <K> s, _false) { if (!v<K>()) prev(s); }

	INLINE void next(SL, _true)  { }
	INLINE void next(SL, _false) { }
	INLINE void prev(SM, _true)  { }
	INLINE void prev(SM, _false) { }

//-----------------------------------------------------------------------------

	struct deref  { };
	struct inc_l  { };
	struct dec_l  { };
	struct inc_r  { };
	struct dec_r  { };

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE R _(deref, size <K>) const { return cast(*v<K>()); }

	template <size_t K>
	INLINE void
	_(inc_l, size <K>) { +v<K>() ? _do(++v<K>()) : next(size <K>()); }

	template <size_t K>
	INLINE void
	_(dec_l, size <K>) { -v<K>() ? _do(--v<K>()) : prev(size <K>()); }

	template <size_t K>
	INLINE D _(inc_r, size <K>) { return D(K,
		N == K ? +v<K>() ? v<N>()++ : next(size <K>()), v<N>() : v<N>()
	...); }

	template <size_t K>
	INLINE D _(dec_r, size <K>) { return D(K,
		N == K ? -v<K>() ? v<N>()-- : prev(size <K>()), v<N>() : v<N>()
	...); }

	INLINE void _(inc_l, SM) { next(SM()); }
	INLINE void _(dec_l, SL) { prev(SL()); }

	INLINE D _(inc_r, SM) { return D((next(SM()), M), v<N>()...); }
	INLINE D _(dec_r, SL) { return D((prev(SL()), L), v<N>()...); }

//-----------------------------------------------------------------------------

public:
	template <typename... A>
	INLINE constexpr join_iter_impl(size_t k, A&&... a) :
		k(k), B(fwd <A>(a)...) { }

	INLINE constexpr R operator*()  const { return op <deref>()(k, der()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D&& operator++() && { return op <inc_l>()(k, der()), der_f(); }
	INLINE D&  operator++() &  { return op <inc_l>()(k, der()), der(); }
	INLINE D&& operator--() && { return op <dec_l>()(k, der()), der_f(); }
	INLINE D&  operator--() &  { return op <dec_l>()(k, der()), der(); }

	INLINE D operator++(int) { return op <inc_r>()(k, der()); }
	INLINE D operator--(int) { return op <dec_r>()(k, der()); }

// 	// TODO : lookup binary OP
// 	INLINE bool operator!=(D o) { return k != o.k || ...; }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D = join_trav <Q, V, R, T>,
	typename TR = iter_traits <V, R, T>,
	typename N = sz_rng_of_p <V>
>
struct join_trav_impl;

template <
	typename Q, typename... V, typename R, typename T,
	typename D, typename TR, size_t... N
>
class join_trav_impl <Q, pack <V...>, R, T, D, TR, sizes <N...> > :
	public trav_base <D, TR, V...>
{
	using B = trav_base <D, TR, V...>;
	using d = seq_diff <B>;
	using P = seq_ptr <B>;

	template <size_t K>
	using trav = iter_elem_at <K, V...>;

	using derived <D>::der_f;
	using derived <D>::der;

	using B::cast;

//-----------------------------------------------------------------------------

	size_t k, e;

	static constexpr size_t M = size_t(-1);
	static constexpr size_t L = sizeof...(V);

	using SM = size <M>;
	using SL = size <L>;

	template <typename OP> using    op = afun::lookup_op <0, L-1, OP>;
	template <typename OP> using  op_M = afun::lookup_op <M, L-1, OP>;
	template <typename OP> using  op_L = afun::lookup_op <0, L, OP>;
	template <typename OP> using op_ML = afun::lookup_op <M, L, OP>;
	template <typename OP> friend  class afun::lookup_op_fun;

	using flipped = expr <path_flip <Q>{}>;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return trav <K>::get(); }

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void next(size <K>, _true = yes) { ++k, next(size <K + 1>(), no); }

	template <size_t K>
	INLINE void prev(size <K>, _true = yes) { --k, prev(size <K - 1>(), no); }

	template <size_t K>
	INLINE void next(size <K> s, _false) { if (!v<K>()) next(s); }

	template <size_t K>
	INLINE void prev(size <K> s, _false) { if (!v<K>()) prev(s); }

	INLINE void next(SL, _true)  { }
	INLINE void next(SL, _false) { }
	INLINE void prev(SM, _true)  { }
	INLINE void prev(SM, _false) { }

	template <size_t K> INLINE void advance(_true)  { prev(size <K>(), no); }
	template <size_t K> INLINE void advance(_false) { next(size <K>(), no); }

//-----------------------------------------------------------------------------

	struct init   { };
	struct deref  { };
	struct inc_l  { };
	struct dec_l  { };
	struct inc_r  { };
	struct dec_r  { };

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void _(init, size <K>) { advance <K>(flipped()); }
	INLINE void _(init, SM)       { }
	INLINE void _(init, SL)       { }

	template <size_t K>
	INLINE R _(deref, size <K>) const { return cast(*v<K>()); }

	template <size_t K>
	INLINE void
	_(inc_l, size <K>) { +v<K>() ? _do(++v<K>()) : next(size <K>()); }

	template <size_t K>
	INLINE void
	_(dec_l, size <K>) { -v<K>() ? _do(--v<K>()) : prev(size <K>()); }

	template <size_t K>
	INLINE D _(inc_r, size <K>) { return D(K,
		N == K ? +v<K>() ? v<N>()++ : next(size <K>()), v<N>() : v<N>()
	...); }

	template <size_t K>
	INLINE D _(dec_r, size <K>) { return D(K,
		N == K ? -v<K>() ? v<N>()-- : prev(size <K>()), v<N>() : v<N>()
	...); }

	INLINE void _(inc_l, SM) { next(SM()); }
	INLINE void _(dec_l, SL) { prev(SL()); }

	INLINE D _(inc_r, SM) { return D((next(SM()), M), v<N>()...); }
	INLINE D _(dec_r, SL) { return D((prev(SL()), L), v<N>()...); }

//-----------------------------------------------------------------------------

public:
	template <typename... A>
	INLINE join_trav_impl(size_t k, size_t e, A&&... a) :
		k(k), e(e), B(fwd <A>(a)...) { op_ML <init>()(k, der()); }

	// TODO: finite atom (unit)
	static constexpr bool finite = _and <fin_trav <V>...>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return k != e; }

	INLINE constexpr R operator*()  const { return op <deref>()(k, der()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D&& operator++() && { return op_M <inc_l>()(k, der()), der_f(); }
	INLINE D&  operator++() &  { return op_M <inc_l>()(k, der()), der(); }
	INLINE D&& operator--() && { return op_L <dec_l>()(k, der()), der_f(); }
	INLINE D&  operator--() &  { return op_L <dec_l>()(k, der()), der(); }

	INLINE D operator++(int) { return op_M <inc_r>()(k, der()); }
	INLINE D operator--(int) { return op_L <dec_r>()(k, der()); }
};

//-----------------------------------------------------------------------------

template <typename V, typename R, typename T>
struct iterator <tag::join, V, R, T> :
	join_iter_impl <V, R, T>
{
	using join_iter_impl <V, R, T>::join_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T>
struct traversor <tag::join, Q, V, R, T> :
	join_trav_impl <Q, V, R, T>
{
	using join_trav_impl <Q, V, R, T>::join_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_JOIN_HPP
