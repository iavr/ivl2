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

#ifndef IVL_CORE_ARRAY_ITER_APPLY_HPP
#define IVL_CORE_ARRAY_ITER_APPLY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename N, typename M>
class apply_iter_base;

template <typename D, typename TR, size_t... N, typename M>
class apply_iter_base <D, TR, sizes <N...>, M> :
	public derived <D, _false>
{
	using derived <D, _false>::der;

	using R = seq_iref <TR>;
	using d = seq_diff <TR>;

	using more = more_of <M>;

//-----------------------------------------------------------------------------

protected:
	INLINE void inc() { thru{++der().template v<N>()...}; }
	INLINE void dec() { thru{--der().template v<N>()...}; }

	INLINE void add(d n) { thru{der().template v<N>() += n...}; }
	INLINE void sub(d n) { thru{der().template v<N>() -= n...}; }

	template <typename F, typename V>
	INLINE constexpr bool   // TODO: for M = all_term, only works for
	comp(F f, V&& v) const  //  (!=)-based termination
		{ return more()(f(der().template v<N>(), v.template v<N>())...); }

//-----------------------------------------------------------------------------

public:
	INLINE constexpr R operator*() const
		{ return der().template f()(*der().template v<N>()...); }

	INLINE constexpr R operator[](d n) const
		{ return der().template f()( der().template v<N>()[n]...); }
};

//-----------------------------------------------------------------------------

template <
	typename I, typename R, typename T, typename M, typename F,
	typename D = apply_iter <I, R, T, M, F>,
	typename TR = iter_traits <I, R, T>,
	typename N = sz_rng_of_p <I>
>
struct apply_iter_impl;

//-----------------------------------------------------------------------------

template <
	typename... I, typename R, typename T, typename M, typename F,
	typename D, typename TR, size_t... N
>
class apply_iter_impl <pack <I...>, R, T, M, F, D, TR, sizes <N...> > :
	public apply_iter_base <D, TR, sizes <N...>, M>,
	public iter_base <D, TR, F, I...>
{
	using B = iter_base <D, TR, F, I...>;

	friend base_type_of <B>;

	template <typename, typename, typename, typename>
	friend class apply_iter_base;

//-----------------------------------------------------------------------------

	using fun = iter_elem <0, F>;

	template <size_t K>
	using iter = iter_elem_at <K + 1, F, I...>;

	INLINE           l_iter_ref <F> f()       { return fun::get(); }
	INLINE constexpr c_iter_ref <F> f() const { return fun::get(); }

	template <size_t K>
	INLINE l_iter_pick <K, I...>
	v() { return iter <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, I...>
	v() const { return iter <K>::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T, typename M, typename F,
	typename D = apply_trav <Q, V, R, T, M, F>,
	typename TR = iter_traits <V, R, T>,
	typename N = sz_rng_of_p <V>
>
struct apply_trav_impl;

template <
	typename Q, typename... V, typename R, typename T, typename M, typename F,
	typename D, typename TR, size_t... N
>
class apply_trav_impl <Q, pack <V...>, R, T, M, F, D, TR, sizes <N...> > :
	public apply_iter_base <D, TR, sizes <N...>, M>,
	public trav_base <D, TR, Q, F, V...>
{
	using B = trav_base <D, TR, Q, F, V...>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename, typename, typename>
	friend class apply_iter_base;

	using more = more_of <M>;

//-----------------------------------------------------------------------------

	using fun = iter_elem <0, F>;

	template <size_t K>
	using trav = iter_elem_at <K + 1, F, V...>;

	INLINE           l_iter_ref <F> f()       { return fun::get(); }
	INLINE constexpr c_iter_ref <F> f() const { return fun::get(); }

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return trav <K>::get(); }

//-----------------------------------------------------------------------------

	template <typename P> INLINE void shift_l(P) { thru{v<N>() <<= P()...}; }
	template <typename P> INLINE void shift_r(P) { thru{v<N>() >>= P()...}; }

	INLINE void _swap() { thru{v<N>().swap()...}; }

//-----------------------------------------------------------------------------

public:
	using B::B;

	static constexpr bool finite = _or <fin_trav <V>...>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return more()(v<N>()...); }

	INLINE bool operator+() const { return more()(+v<N>()...); }
	INLINE bool operator-() const { return more()(-v<N>()...); }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T, typename M, typename F>
struct iterator <tag::apply, I, R, T, M, F> :
	apply_iter_impl <I, R, T, M, F>
{
	using apply_iter_impl <I, R, T, M, F>::apply_iter_impl;
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T,
	typename M, typename F
>
struct traversor <tag::apply, Q, V, R, T, M, F> :
	apply_trav_impl <Q, V, R, T, M, F>
{
	using apply_trav_impl <Q, V, R, T, M, F>::apply_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_APPLY_HPP
