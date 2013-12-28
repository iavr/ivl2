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

#ifndef IVL_DETAILS_CORE_TUPLE_BASE_HPP
#define IVL_DETAILS_CORE_TUPLE_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

struct A;
struct J;
namespace ivl {

//-----------------------------------------------------------------------------

namespace tuple_details {

//-----------------------------------------------------------------------------

template <typename... E>
struct derive : public E...
{
	explicit INLINE constexpr derive(_true) : E()... { }

	template <typename... A>
	explicit INLINE constexpr derive(A&&... a) : E(fwd <A>(a))... { }
};

//-----------------------------------------------------------------------------

template <
	typename D,
	size_t... I, template <typename...> class Q, typename... E,
	size_t... N, typename... U
>
class store <
	data::base <>, D,
	sizes <I...>, Q <E...>,
	sizes <N...>, pack <U...>
> :
	public Q <E...>,
	public access <D, E...>,
	public derive <elem <N, U>...>
{
	using P = Q <E...>;
	using V = pack <U...>;
	using B = derive <elem <N, U>...>;
	static constexpr size_t L = P::length;

	template <size_t J> using under = elem_at <J, U...>;

//-----------------------------------------------------------------------------

protected:
	using derived <D>::der;
	using derived <D>::der_f;

//-----------------------------------------------------------------------------

public:
	using base_type = store;
	using type = P;
	static constexpr size_t length = L;

	using indices = sizes <I...>;
	INLINE constexpr indices idx() const { return indices(); }

//-----------------------------------------------------------------------------

	using B::B;

	template <typename A, enable_if <tup_assign <P, rep <L, A> >{}> = 0>
	INLINE D& operator=(A&& a)
		{ return thru{_<I>() = fwd <A>(a)...}, der(); }

	template <typename T, enable_if <tup_assign <P, T>{}> = 0>
	INLINE D& operator=(T&& t)
		{ return thru{_<I>() = at._<I>(fwd <T>(t))...}, der(); }

//-----------------------------------------------------------------------------

private:
	template <size_t J>
	INLINE rtel <J, P>
	_f() { return der_f().template _at <J>(); }

//-----------------------------------------------------------------------------

public:
	template <size_t J>
	INLINE rtel <J, P>
	_() && { return der_f().template _at <J>(); }

	template <size_t J>
	INLINE ltel <J, P>
	_() & { return der().template _at <J>(); }

	template <size_t J>
	INLINE constexpr cltel <J, P>
	_() const& { return der().template _at <J>(); }

//-----------------------------------------------------------------------------

	template <typename K>
	INLINE indirect_tup <K, D&&>
	_() && { return indirect_tup <K, D&&>(der_f()); }

	template <typename K>
	INLINE indirect_tup <K, D&>
	_() & { return indirect_tup <K, D&>(der()); }

	template <typename K>
	INLINE constexpr indirect_tup <K, const D&>
	_() const& { return indirect_tup <K, const D&>(der()); }

//-----------------------------------------------------------------------------

	template <typename F, typename... A>
	INLINE ret <F(rtref <E>..., A...)>
	call(F&& f, A&&... a) && { return fwd <F>(f)(_f <I>()..., fwd <A>(a)...); }

	template <typename F, typename... A>
	INLINE ret <F(ltref <E>..., A...)>
	call(F&& f, A&&... a) & { return fwd <F>(f)(_<I>()..., fwd <A>(a)...); }

	template <typename F, typename... A>
	INLINE constexpr ret <F(cltref <E>..., A...)>
	call(F&& f, A&&... a) const& { return fwd <F>(f)(_<I>()..., fwd <A>(a)...); }

//-----------------------------------------------------------------------------

	template <typename F, typename... A>
	INLINE ret <F(A..., rtref <E>...)>
	rcall(F&& f, A&&... a) && { return fwd <F>(f)(fwd <A>(a)..., _f <I>()...); }

	template <typename F, typename... A>
	INLINE ret <F(A..., ltref <E>...)>
	rcall(F&& f, A&&... a) & { return fwd <F>(f)(fwd <A>(a)..., _<I>()...); }

	template <typename F, typename... A>
	INLINE constexpr ret <F(A..., cltref <E>...)>
	rcall(F&& f, A&&... a) const& { return fwd <F>(f)(fwd <A>(a)..., _<I>()...); }

//-----------------------------------------------------------------------------

	// TODO: flip element order when in gcc, as a workaround to bug
	// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=51253
	template <typename F> INLINE void
	loop(F&& f) && { thru{(fwd <F>(f)(_f <I>()), 0)...}; }

	template <typename F> INLINE void
	loop(F&& f) & { thru{(fwd <F>(f)(_<I>()), 0)...}; }

	template <typename F> INLINE void
	loop(F&& f) const& { thru{(fwd <F>(f)(_<I>()), 0)...}; }

//-----------------------------------------------------------------------------

	INLINE void loop() &&     { thru{_f <I>()...}; }
	INLINE void loop() &      { thru{_<I>()...}; }
	INLINE void loop() const& { thru{_<I>()...}; }

//-----------------------------------------------------------------------------

private:
	using bracket = afun::op::bracket;
	using _call   = afun::op::call;

	template <typename T, typename R = raw_type <T> >
	struct opt_t : public raw_opt_t <T, R> { };

	template <typename T>
	struct opt_t <T, D> : public _if_t <is_base_opt <B>{}, D, T> { };

	template <typename T> using opt = type_of <opt_t <T> >;

	template <template <typename...> class F, typename... T>
	using optimize = F <opt <T&&>...>;

//-----------------------------------------------------------------------------

	template <typename... T> using app_r = optimize <apply_tuple,  T...>;
	template <typename... T> using op_r  = optimize <keys::op_ref, T...>;

	template <typename... A>
	INLINE static constexpr app_r <A...>
	app_h(A&&... a) { return app_r <A...>(fwd <A>(a)...); }

	template <typename... A>
	INLINE static constexpr op_r <A...>
	op_h(A&&... a) { return op_r <A...>(fwd <A>(a)...); }

//-----------------------------------------------------------------------------

public:
	template <typename A>
	INLINE app_r <bracket, D&&, A>
	operator[](A&& a) && { return app_h(bracket(), der_f(), fwd <A>(a)); }

	template <typename A>
	INLINE app_r <bracket, D&, A>
	operator[](A&& a) & { return app_h(bracket(), der(), fwd <A>(a)); }

	template <typename A>
	INLINE constexpr app_r <bracket, const D&, A>
	operator[](A&& a) const& { return app_h(bracket(), der(), fwd <A>(a)); }

//-----------------------------------------------------------------------------

	template <typename... A>
	INLINE app_r <_call, D&&, A...>
	operator()(A&&... a) && { return app_h(_call(), der_f(), fwd <A>(a)...); }

	template <typename... A>
	INLINE app_r <_call, D&, A...>
	operator()(A&&... a) & { return app_h(_call(), der(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr app_r <_call, const D&, A...>
	operator()(A&&... a) const& { return app_h(_call(), der(), fwd <A>(a)...); }

//-----------------------------------------------------------------------------

	template <typename... A>
	INLINE op_r <D&&, A...>
	_(A&&... a) && { return op_h(der_f(), fwd <A>(a)...); }

	template <typename... A>
	INLINE op_r <D&, A...>
	_(A&&... a) & { return op_h(der(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr op_r <const D&, A...>
	_(A&&... a) const& { return op_h(der(), fwd <A>(a)...); }

};

//-----------------------------------------------------------------------------

template <typename D, typename P>
struct collection <data::base <>, D, P> : public store <
	data::base <>, D, sz_rng_of_p <P>, P,
	sz_rng_of_p <under <D> >, under <D>
>
{
	using U = under <D>;
	using I = sz_rng_of_p <P>;
	using N = sz_rng_of_p <U>;
	using B = store <data::base <>, D, I, P, N, U>;

public:
	using B::B;
};

//-----------------------------------------------------------------------------

}  // namespace tuple_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_BASE_HPP
