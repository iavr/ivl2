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

#ifndef IVL_CORE_TUPLE_BASE_BASE_HPP
#define IVL_CORE_TUPLE_BASE_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename P, typename I = sz_rng_of_p <P> >
struct tup_base;

//-----------------------------------------------------------------------------

template <
	typename D,
	template <typename...> class C, typename... E, size_t... I
>
class tup_base <D, C <E...>, sizes <I...> > : public access <D, E...>
{
	using P = C <E...>;
	using Q = pack <E...>;
	using B = access <D, E...>;

	template <typename T, typename R = raw_type <T> >
	using opt = base_opt <T, R, _if <eq <R, D>{}, B, R> >;

	template <typename T> using uopt = opt <add_uref <T> >;

//-----------------------------------------------------------------------------

protected:
	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

public:
	using base_type = tup_base;
	using type = P;
	static constexpr size_t length = P::length;

	using indices = sizes <I...>;
	INLINE constexpr indices idx() const { return indices(); }

//-----------------------------------------------------------------------------

	using B::B;

	template <typename A, only_if <tup_atom_assign <Q, A>{}> = 0>
	INLINE D& operator=(A&& a)
		{ return thru{at <I>() = fwd <A>(a)...}, der(); }

	template <typename T, only_if <tup_assign <Q, T>{}> = 0>
	INLINE D& operator=(T&& t)
		{ return thru{at <I>() = _at._<I>(fwd <T>(t))...}, der(); }

	template <typename O, only_if <tup_op_ref_assign <O, length>{}> = 0>
	INLINE D& operator=(O&& o)
		{ return fwd <O>(o).template io <I...>(der()), der(); }

//-----------------------------------------------------------------------------

private:
	template <size_t... J>
	using sz_if = only_if <sizeof...(J) != 1, sizes <J...> >;

	template <typename K, typename T>
	using indir = indirect_tup <K, opt <T> >;

	template <size_t J>
	INLINE r_pick_p <J, P>
	at_f() { return der_f().template call_at <J>(); }

//-----------------------------------------------------------------------------

public:
	template <size_t J>
	INLINE r_pick_p <J, P>
	at() && { return der_f().template call_at <J>(); }

	template <size_t J>
	INLINE l_pick_p <J, P>
	at() & { return der().template call_at <J>(); }

	template <size_t J>
	INLINE constexpr c_pick_p <J, P>
	at() const& { return der().template call_at <J>(); }

//-----------------------------------------------------------------------------

	template <size_t... J, typename K = sz_if <J...> >
	INLINE indir <K, D>
	at() && { return der_f().template at <K>(); }

	template <size_t... J, typename K = sz_if <J...> >
	INLINE indir <K, D&>
	at() & { return der().template at <K>(); }

	template <size_t... J, typename K = sz_if <J...> >
	INLINE constexpr indir <K, const D&>
	at() const& { return der().template at <K>(); }

//-----------------------------------------------------------------------------

	template <typename K>
	INLINE indir <K, D>
	at() && { return indir <K, D>(der_f()); }

	template <typename K>
	INLINE indir <K, D&>
	at() & { return indir <K, D&>(der()); }

	template <typename K>
	INLINE constexpr indir <K, const D&>
	at() const& { return indir <K, const D&>(der()); }

//-----------------------------------------------------------------------------

	template <typename F, typename... A>
	INLINE ret <F(r_ref <E>..., A...)>
	call(F&& f, A&&... a) && { return fwd <F>(f)(at_f <I>()..., fwd <A>(a)...); }

	template <typename F, typename... A>
	INLINE ret <F(l_ref <E>..., A...)>
	call(F&& f, A&&... a) & { return fwd <F>(f)(at <I>()..., fwd <A>(a)...); }

	template <typename F, typename... A>
	INLINE constexpr res <F(c_ref <E>..., A...)>
	call(F&& f, A&&... a) const& { return fwd <F>(f)(at <I>()..., fwd <A>(a)...); }

//-----------------------------------------------------------------------------

	template <typename F, typename... A>
	INLINE ret <F(A..., r_ref <E>...)>
	rcall(F&& f, A&&... a) && { return fwd <F>(f)(fwd <A>(a)..., at_f <I>()...); }

	template <typename F, typename... A>
	INLINE ret <F(A..., l_ref <E>...)>
	rcall(F&& f, A&&... a) & { return fwd <F>(f)(fwd <A>(a)..., at <I>()...); }

	template <typename F, typename... A>
	INLINE constexpr res <F(A..., c_ref <E>...)>
	rcall(F&& f, A&&... a) const& { return fwd <F>(f)(fwd <A>(a)..., at <I>()...); }

//-----------------------------------------------------------------------------

	// TODO: flip element order when in gcc, as a workaround to bug
	// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=51253
	template <typename F> INLINE void
	loop(F&& f) && { thru{(fwd <F>(f)(at_f <I>()), 0)...}; }

	template <typename F> INLINE void
	loop(F&& f) & { thru{(fwd <F>(f)(at <I>()), 0)...}; }

	template <typename F> INLINE void
	loop(F&& f) const& { thru{(fwd <F>(f)(at <I>()), 0)...}; }

//-----------------------------------------------------------------------------

protected:
	INLINE void loop_f()      { thru{at_f <I>()...}; }

public:
	INLINE void loop() &&     { thru{at_f <I>()...}; }
	INLINE void loop() &      { thru{at <I>()...}; }
	INLINE void loop() const& { thru{at <I>()...}; }

//-----------------------------------------------------------------------------

private:
	template <typename... P>
	using tmp_if = only_if <sizeof...(P), tup_tmp <P...> >;

	template <typename... T> using app = subs <apply_tuple, uopt <T>...>;
	template <typename... T> using op  = subs <keys::op_ref, uopt <T>...>;

	template <typename F, typename... A>
	using auto_ret = _if <tup_void <F(A...)>{}, F&&, app <F, A...> >;

	template <typename F, typename... A>
	using auto_sw = _if <tup_void <F(A...)>{}, afun::tup_loop, make <app> >;

	using _auto = afun::switch_fun <auto_sw>;
	using bra   = afun::op::bracket;
	using par   = afun::op::call;
	using tmp   = afun::pre_tmp_call;

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

//-----------------------------------------------------------------------------

	template <typename... P, typename... A, typename T = tmp_if <P...> >
	INLINE auto_ret <tmp, D, T, A...>
	_(A&&... a) && { return _auto()(tmp(), der_f(), T(), fwd <A>(a)...); }

	template <typename... P, typename... A, typename T = tmp_if <P...> >
	INLINE auto_ret <tmp, D&, T, A...>
	_(A&&... a) & { return _auto()(tmp(), der(), T(), fwd <A>(a)...); }

	template <typename... P, typename... A, typename T = tmp_if <P...> >
	INLINE constexpr auto_ret <tmp, const D&, T, A...>
	_(A&&... a) const& { return _auto()(tmp(), der(), T(), fwd <A>(a)...); }

//-----------------------------------------------------------------------------

	template <typename... A>
	INLINE op <D, A...>
	_(A&&... a) && { return make <op>()(der_f(), fwd <A>(a)...); }

	template <typename... A>
	INLINE op <D&, A...>
	_(A&&... a) & { return make <op>()(der(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr op <const D&, A...>
	_(A&&... a) const& { return make <op>()(der(), fwd <A>(a)...); }

};

//-----------------------------------------------------------------------------

}  // namespace details

using details::tup_base;

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_BASE_BASE_HPP
