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

#ifndef IVL_CORE_ARRAY_VIEW_RANGE_HPP
#define IVL_CORE_ARRAY_VIEW_RANGE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename A, typename... B>
struct int_common_t : common_t <A, B...> { };

template <typename T, T N, typename... B>
struct int_common_t <integral <T, N>, B...> : common_t <B...> { };

template <typename A, typename... B>
using int_common = type_of <int_common_t <A, B...> >;

//-----------------------------------------------------------------------------

template <typename B, typename U, typename... E>
struct range_type_t;

template <typename B, typename U, typename... E>
using range_type = type_of <range_type_t <B, U, E...> >;

template <typename B, typename U>
struct range_type_t <B, U> : copy_t <int_type <B> > { };

template <typename B, typename U, typename E>
struct range_type_t <B, U, E> : copy_t <int_common <B, E> > { };

//-----------------------------------------------------------------------------

template <typename T, typename O, typename U, bool F>
using range_traits_base = id_t <seq_traits <
	id_t <T>, O, _type <T>,
	range_trav, id, size_t, U, expr <F>
> >;

template <typename B, typename U, typename... E>
struct range_traits_t;

template <typename B, typename U, typename... E>
using range_traits = type_of <range_traits_t <B, U, E...> >;

template <typename B, typename U>
struct range_traits_t <B, U> :
	range_traits_base <range_type <B, U>, none, U, false> { };

// TODO: find order_type when B, U, E are compile-time constants
template <typename B, typename U, typename E>
struct range_traits_t <B, U, E> :
	range_traits_base <range_type <B, U, E>, none, U, true> { };

//-----------------------------------------------------------------------------

template <typename B, typename U, typename... E>
class range_store;

template <typename B, typename U>
struct range_store <B, U> : raw_tuple <B, U>
{
	using T = raw_tuple <B, U>;

//-----------------------------------------------------------------------------

	using begin = elem <0, B>;
	using delta = elem <1, U>;

protected:
	INLINE           r_ref <B> b_f()      { return begin::fwd(); }
	INLINE           r_ref <B> b() &&     { return begin::fwd(); }
	INLINE           l_ref <B> b() &      { return begin::get(); }
	INLINE constexpr c_ref <B> b() const& { return begin::get(); }

	INLINE           r_ref <U> u_f()      { return delta::fwd(); }
	INLINE           r_ref <U> u() &&     { return delta::fwd(); }
	INLINE           l_ref <U> u() &      { return delta::get(); }
	INLINE constexpr c_ref <U> u() const& { return delta::get(); }

	template <typename V, typename R>
	INLINE constexpr V t(R&& r) const&
		{ return V(fwd <R>(r).u(), fwd <R>(r).b()); }

//-----------------------------------------------------------------------------

public:
	using T::T;

	template <typename E, typename R = range_seq <B, U, E> >
	INLINE R bound(E&& e) && { return R(b_f(), u_f(), fwd <E>(e)); }

	template <typename E, typename R = range_seq <B, U, E> >
	INLINE R bound(E&& e) & { return R(b(), u(), fwd <E>(e)); }

	template <typename E, typename R = range_seq <B, U, E> >
	INLINE constexpr R bound(E&& e) const& { return R(b(), u(), fwd <E>(e)); }
};

//-----------------------------------------------------------------------------

template <typename B, typename U, typename E>
struct range_store <B, U, E> : raw_tuple <B, U, E>
{
	using TR = range_traits <B, U, E>;
	using I = range_type <B, U, E>;
	using T = raw_tuple <B, U, E>;
	using S = seq_size <TR>;
	using d = seq_diff <TR>;

//-----------------------------------------------------------------------------

	using begin = elem <0, B>;
	using delta = elem <1, U>;
	using end   = elem <2, E>;

protected:
	INLINE           r_ref <B> b_f()      { return begin::fwd(); }
	INLINE           r_ref <B> b() &&     { return begin::fwd(); }
	INLINE           l_ref <B> b() &      { return begin::get(); }
	INLINE constexpr c_ref <B> b() const& { return begin::get(); }

	INLINE           r_ref <U> u_f()      { return delta::fwd(); }
	INLINE           r_ref <U> u() &&     { return delta::fwd(); }
	INLINE           l_ref <U> u() &      { return delta::get(); }
	INLINE constexpr c_ref <U> u() const& { return delta::get(); }

	INLINE           r_ref <E> e_f()      { return end::fwd(); }
	INLINE           r_ref <E> e() &&     { return end::fwd(); }
	INLINE           l_ref <E> e() &      { return end::get(); }
	INLINE constexpr c_ref <E> e() const& { return end::get(); }

	template <typename V, typename R>
	INLINE constexpr V
	t(R&& r) const&
		{ return V(fwd <R>(r).u(), fwd <R>(r).b(), fwd <R>(r).trunc()); }

//-----------------------------------------------------------------------------

private:
	INLINE I trunc() const { return u().template trunc <d>(I(b()), e()); }

//-----------------------------------------------------------------------------

public:
	template <typename _B, typename _U, typename _E>
	INLINE constexpr range_store(_B&& _b, _U&& _u, _E&& _e) :
		T(fwd <_B>(_b), fwd <_U>(_u), fwd <_E>(_e)) { }

	INLINE constexpr S size() const { return u().template size <S>(b(), e()); }
};

//-----------------------------------------------------------------------------

// extending definition @array/type/sequence
template <typename B, typename U, typename... E>
struct seq_data_t <range_seq <B, U, E...> > :
	pack <range_store <B, U, E...> > { };

//-----------------------------------------------------------------------------

template <
	typename P,
	typename R = embed <range_store, P>,
	typename D = embed <range_seq, P>,
	typename TR = embed <range_traits, P>
>
class range_seq_impl :
	public based <R>,
	public seq_base <D, TR>
{
	using C = based <R>;
	using B = seq_base <D, TR>;
	friend B;

	using IR = r_seq_iter <TR>;
	using IL = l_seq_iter <TR>;
	using IC = c_seq_iter <TR>;

	template <typename Q> using VR = r_seq_trav <TR, Q>;
	template <typename Q> using VL = l_seq_trav <TR, Q>;
	template <typename Q> using VC = c_seq_trav <TR, Q>;

	using C::base_f;
	using C::base;

//-----------------------------------------------------------------------------

	template <typename Q>
	INLINE VR <Q> _trav() && { return R::template t <VR <Q> >(base_f()); }

	template <typename Q>
	INLINE VL <Q> _trav() & { return R::template t <VL <Q> >(base()); }

	template <typename Q>
	INLINE constexpr VC <Q>
	_trav() const& { return R::template t <VC <Q> >(base()); }

//-----------------------------------------------------------------------------

protected:
	using base_type = base_type_of <B>;

//-----------------------------------------------------------------------------

public:
	using C::C;

	INLINE           IR begin() &&     { return IR(R::u_f(), R::b_f()); }
	INLINE           IL begin() &      { return IL(R::u(),   R::b()); }
	INLINE constexpr IC begin() const& { return IC(R::u(),   R::b()); }

	INLINE           IR end() &&     { return IR(R::u_f(), R::e_f()); }
	INLINE           IL end() &      { return IL(R::u(),   R::e()); }
	INLINE constexpr IC end() const& { return IC(R::u(),   R::e()); }
};

//-----------------------------------------------------------------------------

template <typename _B, typename U, typename... E>
class sequence <tag::range, _B, U, E...> :
	public range_seq_impl <pack <_B, U, E...> >
{
	using B = range_seq_impl <pack <_B, U, E...> >;

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

#endif  // IVL_CORE_ARRAY_VIEW_RANGE_HPP
