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

struct J;
namespace ivl {

//-----------------------------------------------------------------------------

namespace tuple_details {

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
	public Q <E...>, public access <D, E...>,
	public elem <N, U>...
{
	using P = Q <E...>;
	using V = pack <U...>;
	static constexpr size_t L = P::length;

	template <size_t J> using under = under_elem <J, D>;

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

	explicit INLINE constexpr store() : elem <N, U>()... { }

	template <typename... A>
	explicit INLINE constexpr store(A&&... a) : elem <N, U>(fwd <A>(a))... { }

	template <typename A, enable_if <tup_assign <P, rep <L, A> >{}> = 0>
	INLINE D& operator=(A&& a)
	{
		return thru{_<I>() = fwd <A>(a)...}, der();
	}

	template <typename T, enable_if <tup_assign <P, T>{}> = 0>
	INLINE D& operator=(T&& t)
	{
		return thru{_<I>() = at._<I>(fwd <T>(t))...}, der();
	}

//-----------------------------------------------------------------------------

private:
	template <size_t J>
	INLINE rtel <J, P>
	_f() { return der_f().template _at <J>(); }

public:
	using access <D, E...>::_;

//-----------------------------------------------------------------------------

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

	// TODO: flip element order when in gcc, as a workaround to bug
	// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=51253
	template <typename F> INLINE void
	loop(F&& f) && { thru{(fwd <F>(f)(_f <I>()), 0)...}; }

	template <typename F> INLINE void
	loop(F&& f) & { thru{(fwd <F>(f)(_<I>()), 0)...}; }

	template <typename F> INLINE void
	loop(F&& f) const& { thru{(fwd <F>(f)(_<I>()), 0)...}; }

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
