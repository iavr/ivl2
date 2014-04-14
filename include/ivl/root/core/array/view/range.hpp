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

class B;
namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename O, typename U, bool finite>
using range_traits = seq_traits <
	id_t <T>, O, _type <T>,
	range_iter, range_trav, id, size_t, U, expr <finite>
>;

//-----------------------------------------------------------------------------

template <typename A, typename... B>
struct int_common_t : common_t <A, B...> { };

template <typename T, T N, typename... B>
struct int_common_t <integral <T, N>, B...> : common_t <B...> { };

template <typename A, typename... B>
using int_common = type_of <int_common_t <A, B...> >;

//-----------------------------------------------------------------------------

template <typename B, typename U, typename... E> class range;

template <typename R> struct range_attr;

template <typename B, typename U>
struct range_attr <range <B, U> >
{
	using type = copy <int_type <B> >;
	using derived_type = range_seq <B, U>;
	using traits = range_traits <type, none, U, false>;
};

template <typename B, typename U, typename E>
struct range_attr <range <B, U, E> >
{
	using type = copy <int_common <B, E> >;
	using derived_type = range_seq <B, U, E>;
	using traits = range_traits <type, none, U, true>;  // TODO: find order_type
};

//-----------------------------------------------------------------------------

template <typename B, typename U>
class unbounded_range : raw_tuple <B, U>
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

template <
	typename B, typename U, typename E,
	typename A = range_attr <range <B, U, E> >,
	typename I = type_of <A>,
	typename TR = traits_of <A>
>
class bounded_range : raw_tuple <B, U, I>
{
	using T = raw_tuple <B, U, I>;
	using S = seq_size <TR>;
	using d = seq_diff <TR>;

//-----------------------------------------------------------------------------

	using begin = elem <0, B>;
	using delta = elem <1, U>;
	using end   = elem <2, I>;

protected:
	INLINE           r_ref <B> b_f()      { return begin::fwd(); }
	INLINE           r_ref <B> b() &&     { return begin::fwd(); }
	INLINE           l_ref <B> b() &      { return begin::get(); }
	INLINE constexpr c_ref <B> b() const& { return begin::get(); }

	INLINE           r_ref <U> u_f()      { return delta::fwd(); }
	INLINE           r_ref <U> u() &&     { return delta::fwd(); }
	INLINE           l_ref <U> u() &      { return delta::get(); }
	INLINE constexpr c_ref <U> u() const& { return delta::get(); }

	INLINE           r_ref <I> e_f()      { return end::fwd(); }
	INLINE           r_ref <I> e() &&     { return end::fwd(); }
	INLINE           l_ref <I> e() &      { return end::get(); }
	INLINE constexpr c_ref <I> e() const& { return end::get(); }

	template <typename V, typename R>
	INLINE constexpr V
	t(R&& r) const&
		{ return V(fwd <R>(r).u(), fwd <R>(r).b(), fwd <R>(r).e()); }

//-----------------------------------------------------------------------------

public:
	template <typename _B, typename _U, typename _E>
	INLINE bounded_range(_B&& _b, _U&& _u, _E&& _e) :
		T(fwd <_B>(_b), fwd <_U>(_u), fwd <_E>(_e))
			{ u().template trunc <d>(b(), e()); }

	INLINE constexpr S size() const { return u().template diff <S>(e(), b()); }
};

//-----------------------------------------------------------------------------

template <typename B, typename U>
struct range <B, U> : unbounded_range <B, U>
{
	using unbounded_range <B, U>::unbounded_range;
};

template <typename B, typename U, typename E>
struct range <B, U, E> : bounded_range <B, U, E>
{
	using bounded_range <B, U, E>::bounded_range;
};

//-----------------------------------------------------------------------------

// extending definition @array/type/sequence
template <typename B, typename U, typename... E>
struct seq_data_t <range_seq <B, U, E...> > : pack <range <B, U, E...> > { };

//-----------------------------------------------------------------------------

template <
	typename R,
	typename A = range_attr <R>,
	typename D = derived_type_of <A>,
	typename TR = traits_of <A>
>
class range_seq_impl :
	public based <R>,
	public seq_base <D, TR>
{
	using S = based <R>;
	using B = seq_base <D, TR>;
	friend B;

	using IR = r_seq_iter <TR>;
	using IL = l_seq_iter <TR>;
	using IC = c_seq_iter <TR>;

	template <typename Q> using VR = r_seq_trav <TR, Q>;
	template <typename Q> using VL = l_seq_trav <TR, Q>;
	template <typename Q> using VC = c_seq_trav <TR, Q>;

	using S::base_f;
	using S::base;

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
	using S::S;

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
	public range_seq_impl <range <_B, U, E...> >
{
	using B = range_seq_impl <range <_B, U, E...> >;

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
