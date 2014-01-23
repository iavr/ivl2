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

#ifndef IVL_DETAILS_CORE_TUPLE_BASE_BASE_HPP
#define IVL_DETAILS_CORE_TUPLE_BASE_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <template <typename...> class R, typename... A>
INLINE constexpr R <A...>
make(A&&... a) { return R <A...>(fwd <A>(a)...); }

//-----------------------------------------------------------------------------

template <template <typename...> class T>
struct apply_
{
	template <typename... A>
	INLINE constexpr subs <T, A...>
	operator()(A&&... a) const { return subs <T, A...>(fwd <A>(a)...); }
};

template <template <typename...> class T>
struct loop_
{
	template <typename... A>
	INLINE void
	operator()(A&&... a) const { subs <T, A...>(fwd <A>(a)...).loop(); }
};

//-----------------------------------------------------------------------------

template <typename D, typename P, typename I = sz_rng_of_p <P> >
struct base_tup;

//-----------------------------------------------------------------------------

template <
	typename D,
	template <typename...> class C, typename... E, size_t... I
>
class base_tup <D, C <E...>, sizes <I...> > : public access <D, E...>
{
	using P = C <E...>;
	using Q = pack <E...>;
	using B = access <D, E...>;

	template <typename T, typename R = raw_type <T> >
	using opt = base_opt <T, R, _if <eq <R, D>{}, B, R> >;

//-----------------------------------------------------------------------------

protected:
	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

public:
	using base_type = base_tup;
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

//-----------------------------------------------------------------------------

private:
	template <size_t J>
	INLINE rtel <J, P>
	at_f() { return der_f().template ref_at <J>(); }

	template <size_t... J>
	using sz_if = only_if <sizeof...(J) != 1, sizes <J...> >;

//-----------------------------------------------------------------------------

public:
	template <size_t J>
	INLINE rtel <J, P>
	at() && { return der_f().template ref_at <J>(); }

	template <size_t J>
	INLINE ltel <J, P>
	at() & { return der().template ref_at <J>(); }

	template <size_t J>
	INLINE constexpr cltel <J, P>
	at() const& { return der().template ref_at <J>(); }

//-----------------------------------------------------------------------------

	template <size_t... J, typename K = sz_if <J...> >
	INLINE indirect_tup <K, opt <D&&> >
	at() && { return der_f().template at <K>(); }

	template <size_t... J, typename K = sz_if <J...> >
	INLINE indirect_tup <K, opt <D&> >
	at() & { return der().template at <K>(); }

	template <size_t... J, typename K = sz_if <J...> >
	INLINE constexpr indirect_tup <K, opt <const D&> >
	at() const& { return der().template at <K>(); }

//-----------------------------------------------------------------------------

	template <typename K>
	INLINE indirect_tup <K, opt <D&&> >
	at() && { return indirect_tup <K, D&&>(der_f()); }

	template <typename K>
	INLINE indirect_tup <K, opt <D&> >
	at() & { return indirect_tup <K, D&>(der()); }

	template <typename K>
	INLINE constexpr indirect_tup <K, opt <const D&> >
	at() const& { return indirect_tup <K, const D&>(der()); }

//-----------------------------------------------------------------------------

	template <typename F, typename... A>
	INLINE ret <F(rtref <E>..., A...)>
	call(F&& f, A&&... a) && { return fwd <F>(f)(at_f <I>()..., fwd <A>(a)...); }

	template <typename F, typename... A>
	INLINE ret <F(ltref <E>..., A...)>
	call(F&& f, A&&... a) & { return fwd <F>(f)(at <I>()..., fwd <A>(a)...); }

	template <typename F, typename... A>
	INLINE constexpr ret <F(cltref <E>..., A...)>
	call(F&& f, A&&... a) const& { return fwd <F>(f)(at <I>()..., fwd <A>(a)...); }

//-----------------------------------------------------------------------------

	template <typename F, typename... A>
	INLINE ret <F(A..., rtref <E>...)>
	rcall(F&& f, A&&... a) && { return fwd <F>(f)(fwd <A>(a)..., at_f <I>()...); }

	template <typename F, typename... A>
	INLINE ret <F(A..., ltref <E>...)>
	rcall(F&& f, A&&... a) & { return fwd <F>(f)(fwd <A>(a)..., at <I>()...); }

	template <typename F, typename... A>
	INLINE constexpr ret <F(A..., cltref <E>...)>
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

	INLINE void loop() &&     { thru{at_f <I>()...}; }
	INLINE void loop() &      { thru{at <I>()...}; }
	INLINE void loop() const& { thru{at <I>()...}; }

//-----------------------------------------------------------------------------

private:
	template <typename... T> using app = subs <apply_tuple, opt <T&&>...>;
	template <typename... T> using loo = subs <loop_tuple, opt <T&&>...>;
	template <typename... T> using op  = subs <keys::op_ref, opt <T&&>...>;

	template <typename... P>
	using tmp_if = only_if <sizeof...(P), tup_tmp <P...> >;

	template <typename F, typename... A>
	using auto_ret = _if <tup_void <F(A...)>{}, void, app <F, A...> >;

	template <typename F, typename... A>
	using auto_for = _if <tup_void <F(A...)>{}, loop_<loo>, apply_<app> >;

	using _auto = afun::choose_fun <auto_for>;
	using bra   = afun::op::bracket;
	using par   = afun::op::call;
	using tmp   = afun::pre_tmp_call;

//-----------------------------------------------------------------------------

public:
	template <typename A>
	INLINE app <bra, D&&, A>
	operator[](A&& a) && { return make <app>(bra(), der_f(), fwd <A>(a)); }

	template <typename A>
	INLINE app <bra, D&, A>
	operator[](A&& a) & { return make <app>(bra(), der(), fwd <A>(a)); }

	template <typename A>
	INLINE constexpr app <bra, const D&, A>
	operator[](A&& a) const& { return make <app>(bra(), der(), fwd <A>(a)); }

//-----------------------------------------------------------------------------

	template <typename... A>
	INLINE auto_ret <par, D&&, A...>
	operator()(A&&... a) && { return _auto()(par(), der_f(), fwd <A>(a)...); }

	template <typename... A>
	INLINE auto_ret <par, D&, A...>
	operator()(A&&... a) & { return _auto()(par(), der(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr auto_ret <par, const D&, A...>
	operator()(A&&... a) const& { return _auto()(par(), der(), fwd <A>(a)...); }

//-----------------------------------------------------------------------------

	template <typename... P, typename... A, typename T = tmp_if <P...> >
	INLINE auto_ret <tmp, D&&, T, A...>
	_(A&&... a) && { return _auto()(tmp(), der_f(), T(), fwd <A>(a)...); }

	template <typename... P, typename... A, typename T = tmp_if <P...> >
	INLINE auto_ret <tmp, D&, T, A...>
	_(A&&... a) & { return _auto()(tmp(), der(), T(), fwd <A>(a)...); }

	template <typename... P, typename... A, typename T = tmp_if <P...> >
	INLINE constexpr auto_ret <tmp, const D&, T, A...>
	_(A&&... a) const& { return _auto()(tmp(), der(), T(), fwd <A>(a)...); }

//-----------------------------------------------------------------------------

	template <typename... A>
	INLINE op <D&&, A...>
	_(A&&... a) && { return make <op>(der_f(), fwd <A>(a)...); }

	template <typename... A>
	INLINE op <D&, A...>
	_(A&&... a) & { return make <op>(der(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr op <const D&, A...>
	_(A&&... a) const& { return make <op>(der(), fwd <A>(a)...); }

};

//-----------------------------------------------------------------------------

}  // namespace details

using details::base_tup;

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_BASE_BASE_HPP