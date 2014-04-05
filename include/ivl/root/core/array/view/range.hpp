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

template <typename T, typename L, typename S, typename U>
using range_traits = seq_traits <
	id_t <T>, L, _type <T>,
	range_iter, range_trav, id, S, U
>;

//-----------------------------------------------------------------------------

template <typename B, typename U, typename...> class range;

//-----------------------------------------------------------------------------

template <typename B, typename U>
class range <B, U> : raw_tuple <B, U>
{
	using T = raw_tuple <B, U>;

//-----------------------------------------------------------------------------

	using begin  = elem <0, B>;
	using update = elem <1, U>;

protected:
	INLINE constexpr B b() const { return begin::get(); }

	INLINE           r_ref <U> u_f()      { return update::fwd(); }
	INLINE           r_ref <U> u() &&     { return update::fwd(); }
	INLINE           l_ref <U> u() &      { return update::get(); }
	INLINE constexpr c_ref <U> u() const& { return update::get(); }

	template <typename V, typename R>
	INLINE constexpr V t(R&& r) const& { return V(fwd <R>(r).u(), b()); }

//-----------------------------------------------------------------------------

public:
	using derived = range_seq <B, U>;  // TODO: remove
	static constexpr bool finite = false;

	using traits = range_traits <B, no_size, _unsigned <B>, U>;

	using T::T;
};

//-----------------------------------------------------------------------------

template <typename B, typename U, typename E, typename I = common <B, E> >
class finite_range : raw_tuple <I, U, I>
{
	using T = raw_tuple <I, U, I>;
	using S = _unsigned <B>;

//-----------------------------------------------------------------------------

	using begin  = elem <0, I>;
	using update = elem <1, U>;
	using end    = elem <2, I>;

protected:
	INLINE constexpr I b() const { return begin::get(); }
	INLINE constexpr I e() const { return end::get(); }

	INLINE           r_ref <U> u_f()      { return update::get_f(); }
	INLINE           r_ref <U> u() &&     { return update::get(); }
	INLINE           l_ref <U> u() &      { return update::get(); }
	INLINE constexpr c_ref <U> u() const& { return update::get(); }

	template <typename V, typename R>
	INLINE constexpr V
	t(R&& r) const& { return V(fwd <R>(r).u(), b(), e()); }

//-----------------------------------------------------------------------------

public:
	using derived = range_seq <B, U, E>;  // TODO: remove
	static constexpr bool finite = true;
	static constexpr bool fixed  = false; // TODO: typename U::template fixed <B, E>{};
	// TODO: static constexpr size_t length = typename U::template length <B, E>{};
	// TODO: using length_type = if_size <fixed, size <length> >;;

	using traits = range_traits <I, no_size, S, U>;  // TODO: use fixed/length

//-----------------------------------------------------------------------------

	template <typename _B, typename _U, typename _E>
	INLINE constexpr finite_range(_B b, _U&& u, _E e) :
		T(b, fwd <_U>(u), u.end(b, e)) { }

	INLINE constexpr S size() const { return u().size(b(), e()); }
};

//-----------------------------------------------------------------------------

template <typename B, typename U, typename E>
struct range <B, U, E> : finite_range <B, U, E>
{
	using finite_range <B, U, E>::finite_range;
};

//-----------------------------------------------------------------------------

// extending definition @array/type/sequence
template <typename B, typename U, typename... E>
struct seq_data_t <range_seq <B, U, E...> > : pack <range <B, U, E...> > { };

//-----------------------------------------------------------------------------

template <
	typename R, typename D = typename R::derived,  // TODO: remove
	typename TR = traits_of <R>
>
class range_seq_impl :
	public R,
	public seq_base <D, TR>
{
	using B = seq_base <D, TR>;
	friend B;

	using IR = r_seq_iter <TR>;
	using IL = l_seq_iter <TR>;
	using IC = c_seq_iter <TR>;

	template <typename Q> using VR = r_seq_trav <TR, Q>;
	template <typename Q> using VL = l_seq_trav <TR, Q>;
	template <typename Q> using VC = c_seq_trav <TR, Q>;

//-----------------------------------------------------------------------------

	template <typename Q>
	INLINE VR <Q> _trav() && { return R::template t <VR <Q> >(mv(*this)); }

	template <typename Q>
	INLINE VL <Q> _trav() & { return R::template t <VL <Q> >(*this); }

	template <typename Q>
	INLINE constexpr VC <Q>
	_trav() const& { return R::template t <VC <Q> >(*this); }

//-----------------------------------------------------------------------------

public:
	using traits = TR;
	using R::finite;  // TODO: remove
	using R::R;

	INLINE           IR begin() &&     { return IR(R::u_f(), R::b()); }
	INLINE           IL begin() &      { return IL(R::u(),   R::b()); }
	INLINE constexpr IC begin() const& { return IC(R::u(),   R::b()); }

	INLINE           IR end() &&     { return IR(R::u_f(), R::e()); }
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
