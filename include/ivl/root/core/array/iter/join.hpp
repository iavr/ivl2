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

template <typename D, typename TR, typename N>
class join_iter_base;

template <typename D, typename TR, size_t... N>
class join_iter_base <D, TR, sizes <N...> > :
	public derived <D, _false>
{
	using derived <D, _false>::der;

	using R = seq_iref <TR>;
	using d = seq_diff <TR>;

//-----------------------------------------------------------------------------

protected:
	size_t k;

	static constexpr size_t M = size_t(-1);
	static constexpr size_t L = sizeof...(N);

	using SM = size <M>;
	using SL = size <L>;

	template <typename OP> using    op = afun::lookup_op <0, L-1, OP>;
	template <typename OP> using  op_M = afun::lookup_op <M, L-1, OP>;
	template <typename OP> using  op_L = afun::lookup_op <0, L, OP>;
	template <typename OP> using op_ML = afun::lookup_op <M, L, OP>;
	template <typename OP> friend  class afun::lookup_op_fun;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void next(size <K>) { ++k, next_cond(size <K + 1>()); }

	template <size_t K>
	INLINE void prev(size <K>) { --k, prev_cond(size <K - 1>()); }

	template <size_t K>
	INLINE void next_cond(size <K> s) { if (!der().template v<K>()) next(s); }

	template <size_t K>
	INLINE void prev_cond(size <K> s) { if (!der().template v<K>()) prev(s); }

	INLINE void next(SL) { }
	INLINE void prev(SM) { }

	INLINE void next_cond(SL) { }
	INLINE void prev_cond(SM) { }

//-----------------------------------------------------------------------------

	struct deref  { };
	struct _inc   { };
	struct _dec   { };
	struct _comp  { };

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE R
	_(deref, size <K>) const { return der().cast(*der().template v<K>()); }

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void _(_inc, size <K>)
	{
		+der().template v<K>() ? _do(++der().template v<K>()) : next(size <K>());
	}

	template <size_t K>
	INLINE void _(_dec, size <K>)
	{
		-der().template v<K>() ? _do(--der().template v<K>()) : prev(size <K>());
	}

	INLINE void _(_inc, SM) { next(SM()); }
	INLINE void _(_dec, SL) { prev(SL()); }

//-----------------------------------------------------------------------------

	template <size_t K, typename F, typename O>
	INLINE bool _(_comp, size <K>, F, O&& o) const
		{ return F()(der().template v<K>(), o.template v<K>()); }

	template <typename F, typename O>
	INLINE bool _(_comp, SM, F, O&&) const { return false; }

	template <typename F, typename O>
	INLINE bool _(_comp, SL, F, O&&) const { return false; }

//-----------------------------------------------------------------------------

	INLINE void inc() { op_M <_inc>()(k, der()); }
	INLINE void dec() { op_L <_dec>()(k, der()); }

	template <typename F, typename O>
	INLINE constexpr bool comp(F f, O&& o) const
	{
		return afun::lex2_fun()
			(f, k == o.k, f(k, o.k), op_ML <_comp>()(k, der(), f, o));
	}

	// TODO: define when random-access is available
	template <typename O>
	INLINE constexpr d comp(afun::op::sub, O&& o) const;

//-----------------------------------------------------------------------------

public:
	INLINE constexpr join_iter_base(size_t k) : k(k) { }

	INLINE constexpr R operator*() const { return op <deref>()(k, der()); }
};

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
	public join_iter_base <D, TR, sizes <N...> >,
	public iter_base <D, TR, V...>
{
	using S = join_iter_base <D, TR, sizes <N...> >;
	using B = iter_base <D, TR, V...>;

	friend base_type_of <B>;

	template <typename, typename, typename>
	friend class join_iter_base;

//-----------------------------------------------------------------------------

	template <size_t K>
	using trav = iter_elem_at <K, V...>;

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return trav <K>::get(); }

//-----------------------------------------------------------------------------

	using S::inc;
	using S::dec;
	using S::comp;

//-----------------------------------------------------------------------------

public:
	using S::operator*;

	template <typename... A>
	INLINE constexpr join_iter_impl(size_t k, A&&... a) :
		S(k), B(fwd <A>(a)...) { }
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
	public join_iter_base <D, TR, sizes <N...> >,
	public trav_base <D, TR, Q, V...>
{
protected:
	using S = join_iter_base <D, TR, sizes <N...> >;
	using B = trav_base <D, TR, Q, V...>;

	friend base_type_of <B>;
	friend base_trav_of <B>;

	template <typename, typename, typename>
	friend class join_iter_base;

	using B::der_f;
	using B::der;

//-----------------------------------------------------------------------------

	using S::_;
	using S::k;

	size_t e;

	static constexpr size_t M = size_t(-1);
	static constexpr size_t L = sizeof...(V);

	using SM = size <M>;
	using SL = size <L>;

	template <typename OP> using op_ML = typename S::template op_ML <OP>;
	template <typename OP> friend class afun::lookup_op_fun;

//-----------------------------------------------------------------------------

	template <size_t K>
	using trav = iter_elem_at <K, V...>;

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return trav <K>::get(); }

//-----------------------------------------------------------------------------

	struct elem_l { };
	struct elem_r { };

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE void _(elem_l, size <K>) { v<K>() <<= edge; }

	template <size_t K>
	INLINE void _(elem_r, size <K>) { v<K>() >>= edge; }

	INLINE void _(elem_l, SM) { }
	INLINE void _(elem_l, SL) { }

	INLINE void _(elem_r, SM) { }
	INLINE void _(elem_r, SL) { }

//-----------------------------------------------------------------------------

	INLINE void shift_l(key::edge) { op_ML <elem_l>()(k, der()); }
	INLINE void shift_r(key::edge) { op_ML <elem_r>()(k, der()); }

	INLINE void _swap() { ivl::swap(k, e), elem_flip(); }

	INLINE void elem_flip() { thru{v<N>().flip()...}; }

//-----------------------------------------------------------------------------

	using S::inc;
	using S::dec;
	using S::comp;

//-----------------------------------------------------------------------------

public:
	using S::operator*;

	template <typename... A>
	INLINE constexpr join_trav_impl(size_t k, size_t, size_t e, A&&... a) :
		S(k), e(e), B(fwd <A>(a)...) { }

	static constexpr bool finite = _and <trav_finite <V>...>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return k != e; }
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

	friend base_type_of <B>;
	friend base_trav_of <B>;

	template <typename, typename, typename>
	friend class join_iter_base;

	using B::elem_flip;
	using B::der_f;
	using B::der;

//-----------------------------------------------------------------------------

	using B::_;
	using B::k;

	size_t f;

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

	using P = key::iter;
	using E = key::edge;

	INLINE void shift_l(P) {               k = f,   elem_l(); }
	INLINE void shift_r(P) { if (!empty()) k = l(), elem_r(); }
	INLINE void shift_l(E) { B::shift_l(E()); if (!empty()) l() = k; }
	INLINE void shift_r(E) { B::shift_r(E());               f   = k; }

	INLINE void elem_l() { thru{v<N>() <<= P()...}; }
	INLINE void elem_r() { thru{v<N>() >>= P()...}; }

	INLINE void _swap() { if (!empty()) k = k == f ? l() : f, elem_flip(); }

	INLINE constexpr bool empty() const { return f == l() + 1; }

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
