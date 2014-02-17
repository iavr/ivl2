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

template <
	typename I, typename R, typename T, typename M, typename F,
	typename N = sz_rng_of_p <I>, typename D = apply_iter <I, R, T, M, F>,
	typename TR = iter_traits <I, R, T>
>
struct apply_iter_impl;

//-----------------------------------------------------------------------------

template <
	typename... I, typename R, typename T, typename M, typename F,
	size_t... N, typename D, typename TR
>
class apply_iter_impl <pack <I...>, R, T, M, F, sizes <N...>, D, TR> :
	public iter_base <D, TR, F, I...>
{
	using B = iter_base <D, TR, F, I...>;
	using d = seq_diff <TR>;
	using P = seq_ptr <TR>;

	using fun = iter_elem <0, F>;

	template <size_t K>
	using iter = iter_elem_at <K + 1, F, I...>;

	using derived <D>::der;
	using B::ref;

//-----------------------------------------------------------------------------

	INLINE           l_iter_ref <F> f()       { return fun::get(); }
	INLINE constexpr c_iter_ref <F> f() const { return fun::get(); }

	template <size_t K>
	INLINE l_iter_pick <K, I...>
	i() { return iter <K>::get(); }

	template <size_t K>
	INLINE constexpr c_iter_pick <K, I...>
	i() const { return iter <K>::get(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr R operator*()  const { return ref(f()(*i<N>()...)); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D& operator++() { return thru{++i<N>()...}, der(); }
	INLINE D& operator--() { return thru{--i<N>()...}, der(); }

	INLINE D operator++(int) { return D(f(), i<N>()++...); }
	INLINE D operator--(int) { return D(f(), i<N>()--...); }

	INLINE constexpr R operator[](d n) const { return ref(f()(i<N>()[n]...)); }

	INLINE D& operator+=(d n) { return thru{i<N>() += n...}, der(); }
	INLINE D& operator-=(d n) { return thru{i<N>() -= n...}, der(); }

	INLINE D operator+(d n) { return D(f(), i<N>() + n...); }
	INLINE D operator-(d n) { return D(f(), i<N>() - n...); }
};

//-----------------------------------------------------------------------------

template <
	typename V, typename R, typename T, typename M, typename F,
	typename N = sz_rng_of_p <V>, typename D = apply_trav <V, R, T, M, F>,
	typename TR = iter_traits <V, R, T>
>
struct apply_trav_impl;

template <
	typename... V, typename R, typename T, typename M, typename F,
	size_t... N, typename D, typename TR
>
class apply_trav_impl <pack <V...>, R, T, M, F, sizes <N...>, D, TR> :
	public trav_base <D, TR, F, V...>
{
	using B = trav_base <D, TR, F, V...>;
	using d = seq_diff <B>;
	using P = seq_ptr <B>;

	using fun = iter_elem <0, F>;

	template <size_t K>
	using trav = iter_elem_at <K + 1, F, V...>;

	using term = raw_type <M>;

	using derived <D>::der;
	using B::ref;

//-----------------------------------------------------------------------------

	INLINE           l_iter_ref <F> f()       { return fun::get(); }
	INLINE constexpr c_iter_ref <F> f() const { return fun::get(); }

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

	INLINE constexpr R operator*()  const { return ref(f()(*v<N>()...)); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE D& operator++() { return thru{++v<N>()...}, der(); }
	INLINE D& operator--() { return thru{--v<N>()...}, der(); }

	INLINE D operator++(int) { return D(f(), v<N>()++...); }
	INLINE D operator--(int) { return D(f(), v<N>()--...); }

	INLINE constexpr R operator[](d n) const { return ref(f()(v<N>()[n]...)); }

	INLINE D& operator+=(d n) { return thru{v<N>() += n...}, der(); }
	INLINE D& operator-=(d n) { return thru{v<N>() -= n...}, der(); }

	INLINE D operator+(d n) { return D(f(), v<N>() + n...); }
	INLINE D operator-(d n) { return D(f(), v<N>() - n...); }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T, typename M, typename F>
struct iterator <data::apply <>, I, R, T, M, F> :
	apply_iter_impl <I, R, T, M, F>
{
	using apply_iter_impl <I, R, T, M, F>::apply_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename V, typename R, typename T, typename M, typename F>
struct traversor <data::apply <>, V, R, T, M, F> :
	apply_trav_impl <V, R, T, M, F>
{
	using apply_trav_impl <V, R, T, M, F>::apply_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_APPLY_HPP
