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

template <
	typename I, typename R, typename T, typename M,
	typename D = zip_iter <I, R, T, M>,
	typename TR = iter_traits <I, R, T>,
	typename N = sz_rng_of_p <I>
>
struct zip_iter_impl;

//-----------------------------------------------------------------------------

template <
	typename... I, typename R, typename T, typename M,
	typename D, typename TR, size_t... N
>
class zip_iter_impl <pack <I...>, R, T, M, D, TR, sizes <N...> > :
	public iter_base <D, TR, I...>
{
	using B = iter_base <D, TR, I...>;
	using d = seq_diff <B>;
	using P = seq_iptr <B>;

	using F = afun::rref;

	template <size_t K>
	using iter = iter_elem_at <K, I...>;

	using term = raw_type <M>;

	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE l_iter_pick <K, I...>
	i() { return iter <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, I...>
	i() const { return iter <K>::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr R operator*()  const { return F()(*i<N>()...); }
	INLINE           P operator->() const { return &(operator*()); }

//-----------------------------------------------------------------------------

	INLINE D&& operator++() && { return thru{++i<N>()...}, der_f(); }
	INLINE D&  operator++() &  { return thru{++i<N>()...}, der(); }
	INLINE D&& operator--() && { return thru{--i<N>()...}, der_f(); }
	INLINE D&  operator--() &  { return thru{--i<N>()...}, der(); }

	INLINE D operator++(int) { return D(i<N>()++...); }
	INLINE D operator--(int) { return D(i<N>()--...); }

//-----------------------------------------------------------------------------

	INLINE constexpr R operator[](d n) const { return F()(i<N>()[n]...); }

	INLINE D&& operator+=(d n) && { return thru{i<N>() += n...}, der_f(); }
	INLINE D&  operator+=(d n) &  { return thru{i<N>() += n...}, der(); }
	INLINE D&& operator-=(d n) && { return thru{i<N>() -= n...}, der_f(); }
	INLINE D&  operator-=(d n) &  { return thru{i<N>() -= n...}, der(); }

	INLINE D operator+(d n) const { return D(i<N>() + n...); }
	INLINE D operator-(d n) const { return D(i<N>() - n...); }

//-----------------------------------------------------------------------------

	// TODO
	INLINE bool operator!=(const D& o)
		{ return term().more(i<N>() != o.template i<N>()...); }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename V, typename R, typename T, typename M,
	typename D = zip_trav <Q, V, R, T, M>,
	typename TR = iter_traits <V, R, T>,
	typename N = sz_rng_of_p <V>
>
struct zip_trav_impl;

template <
	typename Q, typename... V, typename R, typename T, typename M,
	typename D, typename TR, size_t... N
>
class zip_trav_impl <Q, pack <V...>, R, T, M, D, TR, sizes <N...> > :
	public trav_base <D, TR, V...>
{
	using B = trav_base <D, TR, V...>;
	using d = seq_diff <B>;
	using P = seq_iptr <B>;

	using F = afun::rref;

	template <size_t K>
	using trav = iter_elem_at <K, V...>;

	using term = raw_type <M>;
	using E = edge;

	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE l_iter_pick <K, V...>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, V...>
	v() const { return trav <K>::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	static constexpr bool finite = _or <fin_trav <V>...>{}();  // TODO: () needed by GCC

	INLINE constexpr operator bool() const { return term().more(v<N>()...); }

	INLINE constexpr R operator*()  const { return F()(*v<N>()...); }
	INLINE           P operator->() const { return &(operator*()); }

//-----------------------------------------------------------------------------

	INLINE D&& operator++() && { return thru{++v<N>()...}, der_f(); }
	INLINE D&  operator++() &  { return thru{++v<N>()...}, der(); }
	INLINE D&& operator--() && { return thru{--v<N>()...}, der_f(); }
	INLINE D&  operator--() &  { return thru{--v<N>()...}, der(); }

	INLINE D operator++(int) { return D(v<N>()++...); }
	INLINE D operator--(int) { return D(v<N>()--...); }

//-----------------------------------------------------------------------------

	INLINE constexpr R operator[](d n) const { return F()(v<N>()[n]...); }

	INLINE D&& operator+=(d n) && { return thru{v<N>() += n...}, der_f(); }
	INLINE D&  operator+=(d n) &  { return thru{v<N>() += n...}, der(); }
	INLINE D&& operator-=(d n) && { return thru{v<N>() -= n...}, der_f(); }
	INLINE D&  operator-=(d n) &  { return thru{v<N>() -= n...}, der(); }

	INLINE D operator+(d n) const { return D(v<N>() + n...); }
	INLINE D operator-(d n) const { return D(v<N>() - n...); }

//-----------------------------------------------------------------------------

	INLINE bool operator+() const { return term().more(+v<N>()...); }
	INLINE bool operator-() const { return term().more(-v<N>()...); }

	INLINE D&& operator<<=(E) && { return thru{v<N>() <<= E()...}, der_f(); }
	INLINE D&  operator<<=(E) &  { return thru{v<N>() <<= E()...}, der(); }
	INLINE D&& operator>>=(E) && { return thru{v<N>() >>= E()...}, der_f(); }
	INLINE D&  operator>>=(E) &  { return thru{v<N>() >>= E()...}, der(); }

//-----------------------------------------------------------------------------

	// TODO
	INLINE bool operator!=(const D& o)
		{ return term().more(v<N>() != o.template v<N>()...); }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T, typename M>
struct iterator <tag::zip, I, R, T, M> :
	zip_iter_impl <I, R, T, M>
{
	using zip_iter_impl <I, R, T, M>::zip_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T, typename M>
struct traversor <tag::zip, Q, V, R, T, M> :
	zip_trav_impl <Q, V, R, T, M>
{
	using zip_trav_impl <Q, V, R, T, M>::zip_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_ZIP_HPP
