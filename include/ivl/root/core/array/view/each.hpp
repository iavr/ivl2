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

#ifndef IVL_CORE_ARRAY_VIEW_EACH_HPP
#define IVL_CORE_ARRAY_VIEW_EACH_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename U>
using each_traits = seq_traits <
	seq_type <U>, seq_length <U>, U, iter_iter, trav_trav
>;

//-----------------------------------------------------------------------------

template <typename U, typename TR = each_traits <U> >
class each_seq_impl :
	public seq_base <each_seq <U>, TR, U>
{
	using B = seq_base <each_seq <U>, TR, U>;
	friend B;

	using S = seq_size <TR>;

	using IR = r_seq_iter <TR>;
	using IL = l_seq_iter <TR>;
	using IC = c_seq_iter <TR>;

	template <typename Q> using VR = r_seq_trav <TR, Q>;
	template <typename Q> using VL = l_seq_trav <TR, Q>;
	template <typename Q> using VC = c_seq_trav <TR, Q>;

	using under = elem <0, U>;

//-----------------------------------------------------------------------------

	INLINE           r_ref <U> u_f()      { return under::fwd(); }
	INLINE           r_ref <U> u() &&     { return under::fwd(); }
	INLINE           l_ref <U> u() &      { return under::get(); }
	INLINE constexpr c_ref <U> u() const& { return under::get(); }

//-----------------------------------------------------------------------------

	template <typename Q>
	INLINE VR <Q> _trav() && { return VR <Q>(u_f().trav(Q())); }

	template <typename Q>
	INLINE VL <Q> _trav() & { return VL <Q>(u().trav(Q())); }

	template <typename Q>
	INLINE VC <Q> _trav() const& { return VC <Q>(u().trav(Q())); }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr S size() const { return u().size(); }

	INLINE           IR begin() &&     { return IR(u_f().begin()); }
	INLINE           IL begin() &      { return IR(u().begin()); }
	INLINE constexpr IC begin() const& { return IR(u().begin()); }

	INLINE           IR end() &&     { return IR(u_f().end()); }
	INLINE           IL end() &      { return IR(u().end()); }
	INLINE constexpr IC end() const& { return IR(u().end()); }

//-----------------------------------------------------------------------------

protected:
	template <typename T>
	using opt = typename B::template opt <T>;

	using B::der_f;
	using B::der;

private:
	using D = each_seq <U>;

	template <typename T>
	using uopt = opt <add_uref <T> >;

	template <typename... T>
	using app = subs <apply_sequence, afun::prim_term, uopt <T>...>;

	template <typename F, typename... A>
	using auto_ret = _if <seq_void <F(A...)>{}, F&&, app <F, A...> >;

	template <typename F, typename... A>
	using auto_sw = _if <seq_void <F(A...)>{}, afun::seq_loop, make <app> >;

	using _auto = afun::switch_fun <auto_sw>;
	using bra   = afun::op::bracket;
	using par   = afun::op::call;

//-----------------------------------------------------------------------------

public:
	template <typename A>
	INLINE app <bra, D, A>
	operator[](A&& a) && { return make <app>()(bra(), der_f(), fwd <A>(a)); }

	template <typename A>
	INLINE app <bra, D&, A>
	operator[](A&& a) & { return make <app>()(bra(), der(), fwd <A>(a)); }

	template <typename A>
	INLINE constexpr app <bra, const D&, A>
	operator[](A&& a) const& { return make <app>()(bra(), der(), fwd <A>(a)); }

//-----------------------------------------------------------------------------

	template <typename... A>
	INLINE auto_ret <par, D, A...>
	operator()(A&&... a) && { return _auto()(par(), der_f(), fwd <A>(a)...); }

	template <typename... A>
	INLINE auto_ret <par, D&, A...>
	operator()(A&&... a) & { return _auto()(par(), der(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr auto_ret <par, const D&, A...>
	operator()(A&&... a) const& { return _auto()(par(), der(), fwd <A>(a)...); }

};

//-----------------------------------------------------------------------------

template <typename U>
struct sequence <tag::each, U> : each_seq_impl <U>
{
	using each_seq_impl <U>::each_seq_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_VIEW_EACH_HPP
