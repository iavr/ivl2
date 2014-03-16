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
	using d = seq_diff <B>;

	template <size_t K>
	using trav = iter_elem_at <K, V...>;

	friend base_type_of <B>;

	using derived <D>::der_f;
	using derived <D>::der;

	using B::cast;

//-----------------------------------------------------------------------------

	size_t k;

	static constexpr size_t M = size_t(-1);
	static constexpr size_t L = sizeof...(V);

	using SM = size <M>;
	using SL = size <L>;

	template <typename OP> using    op = afun::lookup_op <0, L-1, OP>;
	template <typename OP> using  op_M = afun::lookup_op <M, L-1, OP>;
	template <typename OP> using  op_L = afun::lookup_op <0, L, OP>;
	template <typename OP> using op_ML = afun::lookup_op <M, L, OP>;
	template <typename OP> friend  class afun::lookup_op_fun;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return trav <K>::get(); }

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void next(size <K>) { ++k, next_cond(size <K + 1>()); }

	template <size_t K>
	INLINE void prev(size <K>) { --k, prev_cond(size <K - 1>()); }

	template <size_t K>
	INLINE void next_cond(size <K> s) { if (!v<K>()) next(s); }

	template <size_t K>
	INLINE void prev_cond(size <K> s) { if (!v<K>()) prev(s); }

	INLINE void next(SL)  { }
	INLINE void prev(SM)  { }

	INLINE void next_cond(SL) { }
	INLINE void prev_cond(SM) { }

//-----------------------------------------------------------------------------

	struct deref  { };
	struct _inc   { };
	struct _dec   { };
	struct comp   { };

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE R _(deref, size <K>) const { return cast(*v<K>()); }

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void
	_(_inc, size <K>) { +v<K>() ? _do(++v<K>()) : next(size <K>()); }

	template <size_t K>
	INLINE void
	_(_dec, size <K>) { -v<K>() ? _do(--v<K>()) : prev(size <K>()); }

	INLINE void _(_inc, SM) { next(SM()); }
	INLINE void _(_dec, SL) { prev(SL()); }

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE bool _(comp, size <K>, const D& o) const
		{ return v<K>() != o.template v<K>(); }

	INLINE bool _(comp, SM, const D& o) const { return false; }
	INLINE bool _(comp, SL, const D& o) const { return false; }

//-----------------------------------------------------------------------------

	INLINE void inc() { op_M <_inc>()(k, der()); }
	INLINE void dec() { op_L <_dec>()(k, der()); }

//-----------------------------------------------------------------------------

public:
	template <typename... A>
	INLINE constexpr join_iter_impl(size_t k, A&&... a) :
		k(k), B(fwd <A>(a)...) { }

	INLINE constexpr R operator*() const { return op <deref>()(k, der()); }

//-----------------------------------------------------------------------------

	// TODO
	INLINE constexpr bool operator!=(const D& o) const
		{ return k != o.k || op_ML <comp>()(k, der(), o); }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename D = join_trav <Q, V, R, T>,
	typename TR = iter_traits <V, R, T>,
	typename N = sz_rng_of_p <V>,
	bool = path_edge <Q>()
>
struct join_trav_impl;

template <
	typename Q, typename... V, typename R, typename T,
	typename D, typename TR, size_t... N
>
class join_trav_impl <Q, pack <V...>, R, T, D, TR, sizes <N...>, false> :
	public trav_base <D, TR, Q, V...>
{
protected:

	using B = trav_base <D, TR, Q, V...>;
	using d = seq_diff <B>;

	template <size_t K>
	using trav = iter_elem_at <K, V...>;

	using E = arrays::edge;

	friend base_type_of <B>;
	friend base_trav_of <B>;

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

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return trav <K>::get(); }

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void next(size <K>) { ++k, next_cond(size <K + 1>()); }

	template <size_t K>
	INLINE void prev(size <K>) { --k, prev_cond(size <K - 1>()); }

	template <size_t K>
	INLINE void next_cond(size <K> s) { if (!v<K>()) next(s); }

	template <size_t K>
	INLINE void prev_cond(size <K> s) { if (!v<K>()) prev(s); }

	INLINE void next(SL)  { }
	INLINE void prev(SM)  { }

	INLINE void next_cond(SL) { }
	INLINE void prev_cond(SM) { }

//-----------------------------------------------------------------------------

	struct deref  { };
	struct _inc   { };
	struct _dec   { };
	struct comp   { };
	struct elem_l { };
	struct elem_r { };

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE R _(deref, size <K>) const { return cast(*v<K>()); }

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void
	_(_inc, size <K>) { +v<K>() ? _do(++v<K>()) : next(size <K>()); }

	template <size_t K>
	INLINE void
	_(_dec, size <K>) { -v<K>() ? _do(--v<K>()) : prev(size <K>()); }

	INLINE void _(_inc, SM) { next(SM()); }
	INLINE void _(_dec, SL) { prev(SL()); }

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void _(elem_l, size <K>) { v<K>() <<= E(); }

	template <size_t K>
	INLINE void _(elem_r, size <K>) { v<K>() >>= E(); }

	INLINE void _(elem_l, SM) { }
	INLINE void _(elem_l, SL) { }

	INLINE void _(elem_r, SM) { }
	INLINE void _(elem_r, SL) { }

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE bool _(comp, size <K>, const D& o) const
		{ return v<K>() != o.template v<K>(); }

	INLINE bool _(comp, SM, const D& o) const { return false; }
	INLINE bool _(comp, SL, const D& o) const { return false; }

//-----------------------------------------------------------------------------

	INLINE void inc() { op_M <_inc>()(k, der()); }
	INLINE void dec() { op_L <_dec>()(k, der()); }

	INLINE void shift_l(E) { op_ML <elem_l>()(k, der()); }
	INLINE void shift_r(E) { op_ML <elem_r>()(k, der()); }

	INLINE void _swap() { std::swap(k, e), elem_flip(); }

	INLINE void elem_flip() { thru{v<N>().flip()...}; }

//-----------------------------------------------------------------------------

public:
	template <typename... A>
	INLINE constexpr join_trav_impl(size_t k, size_t, size_t e, A&&... a) :
		k(k), e(e), B(fwd <A>(a)...) { }

	// TODO: finite atom (unit)
	static constexpr bool finite = _and <fin_trav <V>...>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return k != e; }

	INLINE constexpr R operator*() const { return op <deref>()(k, der()); }

//-----------------------------------------------------------------------------

	// TODO
	INLINE constexpr bool operator!=(const D& o) const
		{ return k != o.k || op_ML <comp>()(k, der(), o); }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename... V, typename R, typename T,
	typename D, typename TR, size_t... N
>
class join_trav_impl <Q, pack <V...>, R, T, D, TR, sizes <N...>, true> :
	public join_trav_impl <Q, pack <V...>, R, T, D, TR, sizes <N...>, false>
{
	using B = join_trav_impl <Q, pack <V...>, R, T, D, TR, sizes <N...>, false>;

	using P = arrays::iter;
	using E = arrays::edge;

	friend base_type_of <B>;
	friend base_trav_of <B>;

	using B::elem_flip;

	using B::der_f;
	using B::der;

	using B::_;

//-----------------------------------------------------------------------------

	size_t f;

	using B::k;

	      size_t& l()       { return B::e; }
	const size_t& l() const { return B::e; }

	template <typename OP> using op = typename B::template op <OP>;
	template <typename OP> friend class afun::lookup_op_fun;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return B::template v<K>(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return B::template v<K>(); }

//-----------------------------------------------------------------------------

	struct plus  { };
	struct minus { };

	template <size_t K> INLINE bool _(plus,  size <K>) const { return +v<K>(); }
	template <size_t K> INLINE bool _(minus, size <K>) const { return -v<K>(); }

//-----------------------------------------------------------------------------

	INLINE constexpr bool empty() const { return f == l() + 1; }

	INLINE void elem_l() { thru{v<N>() <<= P()...}; }
	INLINE void elem_r() { thru{v<N>() >>= P()...}; }

	INLINE void shift_l(P) {               k = f,   elem_l(); }
	INLINE void shift_r(P) { if (!empty()) k = l(), elem_r(); }
	INLINE void shift_l(E) { B::shift_l(E()); if (!empty()) l() = k; }
	INLINE void shift_r(E) { B::shift_r(E());               f   = k; }

	INLINE void _swap() { if (!empty()) k = k == f ? l() : f, elem_flip(); }

//-----------------------------------------------------------------------------

public:
	template <typename... A>
	INLINE constexpr join_trav_impl(size_t k, size_t l, size_t, A&&... a) :
		B(k, l, l, fwd <A>(a)...), f(k) { }

	INLINE constexpr operator bool() const { return k != l() + 1; }

	INLINE bool operator+() const { return k != l() || op <plus> ()(k, der()); }
	INLINE bool operator-() const { return k != f   || op <minus>()(k, der()); }

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
