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
	typename DER, typename R, typename T, typename F, typename I,
	typename N = sz_rng_of_p <I>,
	typename B = base_iter <I, R, T>
>
struct apply_iter_impl;

template <
	typename DER, typename R, typename T, typename F, typename... I,
	size_t... N, typename B
>
class apply_iter_impl <DER, R, T, F, pack <I...>, sizes <N...>, B> :
	public derived <DER>, public B,
	private raw_tuple <rref_opt <F>, I...>
{
	using IP = pack <I...>;
	using D = seq_diff <B>;
	using P = seq_ptr <B>;

	using derived <DER>::der;
	using B::ref;

	using RF = rref_opt <F>;
	using E  = raw_tuple <RF, I...>;
	using fun = elem <0, RF>;

	template <size_t K>
	using iter = elem_at <K + 1, RF, I...>;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE ltel <K, IP>
	i() { return iter <K>::get(); }

	template <size_t K>
	INLINE constexpr cltel <K, IP>
	i() const { return iter <K>::get(); }

	INLINE constexpr RF
	f() const { return static_cast <RF>(fun::get()); }

//-----------------------------------------------------------------------------

public:
	using E::E;

	INLINE constexpr R operator*()  const { return ref(f()(*i<N>()...)); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE DER& operator++() { return thru{++i<N>()...}, der(); }
	INLINE DER& operator--() { return thru{--i<N>()...}, der(); }

	INLINE DER operator++(int) { return DER(f(), i<N>()++...); }
	INLINE DER operator--(int) { return DER(f(), i<N>()--...); }

	INLINE constexpr R operator[](D n) const { return ref(f()(i<N>()[n]...)); }

	INLINE DER& operator+=(D n) { return thru{i<N>() += n...}, der(); }
	INLINE DER& operator-=(D n) { return thru{i<N>() -= n...}, der(); }

	INLINE DER operator+(D n) { return DER(f(), i<N>() + n...); }
	INLINE DER operator-(D n) { return DER(f(), i<N>() - n...); }
};

//-----------------------------------------------------------------------------

template <
	typename DER, typename R, typename T, typename F, typename V,
	typename N = sz_rng_of_p <V>,
	typename B = base_trav <trav_fin <V>{}, V, R, T>
>
struct apply_trav_impl;

template <
	typename DER, typename R, typename T, typename F, typename... V,
	size_t... N, typename B
>
class apply_trav_impl <DER, R, T, F, pack <V...>, sizes <N...>, B> :
	public derived <DER>, public B,
	private raw_tuple <rref_opt <F>, V...>
{
	using VP = pack <V...>;
	using D = seq_diff <B>;
	using P = seq_ptr <B>;

	using derived <DER>::der;
	using B::ref;

	using RF = rref_opt <F>;
	using E  = raw_tuple <RF, V...>;
	using fun = elem <0, RF>;

	template <size_t K>
	using trav = elem_at <K + 1, RF, V...>;

//-----------------------------------------------------------------------------

	template <size_t K>
	INLINE ltel <K, VP>
	v() { return trav <K>::get(); }

	template <size_t K>
	INLINE constexpr cltel <K, VP>
	v() const { return trav <K>::get(); }

	INLINE constexpr RF
	f() const { return static_cast <RF>(fun::get()); }

//-----------------------------------------------------------------------------

public:
	using E::E;

	INLINE constexpr operator bool() const { return ivl::_and(v<N>()...); }

	INLINE constexpr R operator*()  const { return ref(f()(*v<N>()...)); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE DER& operator++() { return thru{++v<N>()...}, der(); }
	INLINE DER& operator--() { return thru{--v<N>()...}, der(); }

	INLINE DER operator++(int) { return DER(f(), v<N>()++...); }
	INLINE DER operator--(int) { return DER(f(), v<N>()--...); }

	INLINE constexpr R operator[](D n) const { return ref(f()(v<N>()[n]...)); }

	INLINE DER& operator+=(D n) { return thru{v<N>() += n...}, der(); }
	INLINE DER& operator-=(D n) { return thru{v<N>() -= n...}, der(); }

	INLINE DER operator+(D n) { return DER(f(), v<N>() + n...); }
	INLINE DER operator-(D n) { return DER(f(), v<N>() - n...); }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T, typename F>
struct iterator <data::apply <>, I, R, T, F> :
	apply_iter_impl <apply_iter <I, R, T, F>, R, T, F, I>
{
	using apply_iter_impl <apply_iter <I, R, T, F>, R, T, F, I>
		::apply_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename V, typename R, typename T, typename F>
struct traversor <data::apply <>, V, R, T, F> :
	apply_trav_impl <apply_trav <V, R, T, F>, R, T, F, V>
{
	using apply_trav_impl <apply_trav <V, R, T, F>, R, T, F, V>
		::apply_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_APPLY_HPP
