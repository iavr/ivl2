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

#ifndef IVL_CORE_ARRAY_ITER_ZIP_HPP
#define IVL_CORE_ARRAY_ITER_ZIP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename N, typename G>
class zip_iter_base;

template <typename D, typename TR, size_t... N, typename G>
class zip_iter_base <D, TR, sizes <N...>, G> :
	public derived <D, _false>
{
	using derived <D, _false>::der;

	using R = seq_iref <TR>;
	using d = seq_diff <TR>;

//-----------------------------------------------------------------------------

protected:
	INLINE void inc() { thru{++der().template v<N>()...}; }
	INLINE void dec() { thru{--der().template v<N>()...}; }

	INLINE void add(d n) { thru{der().template v<N>() += n...}; }
	INLINE void sub(d n) { thru{der().template v<N>() -= n...}; }

	template <typename F, typename O>
	INLINE constexpr bool comp(F f, O&& o) const
		{ return f(G()(der().template v<N>()...), G()(o.template v<N>()...)); }

	template <typename O>
	INLINE constexpr d comp(afun::op::sub, O&& o) const
		{ return G()(der().template v<N>()...) - G()(o.template v<N>()...); }

//-----------------------------------------------------------------------------

public:
	INLINE constexpr R operator*() const
		{ return afun::rref()(*der().template v<N>()...); }

	INLINE constexpr R operator[](d n) const
		{ return afun::rref()( der().template v<N>()[n]...); }
};

//-----------------------------------------------------------------------------

template <
	typename I, typename R, typename T, typename G,
	typename D = zip_iter <I, R, T, G>,
	typename TR = iter_traits <I, R, T>,
	typename N = sz_rng_of_p <I>
>
struct zip_iter_impl;

//-----------------------------------------------------------------------------

template <
	typename... I, typename R, typename T, typename G,
	typename D, typename TR, size_t... N
>
class zip_iter_impl <pack <I...>, R, T, G, D, TR, sizes <N...> > :
	public zip_iter_base <D, TR, sizes <N...>, G>,
	public iter_base <D, TR, I...>
{
	using S = zip_iter_base <D, TR, sizes <N...>, G>;
	using B = iter_base <D, TR, I...>;

	friend base_type_of <B>;

	template <typename, typename, typename, typename>
	friend class zip_iter_base;

//-----------------------------------------------------------------------------

	template <size_t K>
	using iter = iter_elem_at <K, I...>;

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
	typename Q, typename V, typename R, typename T, typename G,
	typename D = zip_trav <Q, V, R, T, G>,
	typename TR = iter_traits <V, R, T>,
	typename N = sz_rng_of_p <V>
>
struct zip_trav_impl;

template <
	typename Q, typename... V, typename R, typename T, typename G,
	typename D, typename TR, size_t... N
>
class zip_trav_impl <Q, pack <V...>, R, T, G, D, TR, sizes <N...> > :
	public zip_iter_base <D, TR, sizes <N...>, G>,
	public trav_base <D, TR, Q, V...>
{
	using B = trav_base <D, TR, Q, V...>;

	friend B;
	friend base_type_of <B>;

	template <typename, typename, typename, typename>
	friend class zip_iter_base;

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

	template <typename P> INLINE void shift_l(P) { thru{v<N>() <<= P()...}; }
	template <typename P> INLINE void shift_r(P) { thru{v<N>() >>= P()...}; }

	INLINE void _swap() { thru{v<N>().swap()...}; }

//-----------------------------------------------------------------------------

public:
	using B::B;

	static constexpr bool finite = _or <fin_trav <V>...>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return G()(v<N>()...); }

	INLINE bool operator+() const { return +G()(v<N>()...); }
	INLINE bool operator-() const { return -G()(v<N>()...); }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T, typename G>
struct iterator <tag::zip, I, R, T, G> :
	zip_iter_impl <I, R, T, G>
{
	using zip_iter_impl <I, R, T, G>::zip_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T, typename G>
struct traversor <tag::zip, Q, V, R, T, G> :
	zip_trav_impl <Q, V, R, T, G>
{
	using zip_trav_impl <Q, V, R, T, G>::zip_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_ZIP_HPP
