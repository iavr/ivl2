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

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuple_details {

//-----------------------------------------------------------------------------

template <
	typename D, size_t... I,
	template <typename...> class Q, typename... E
>
class store <data::base <>, D, sizes <I...>, Q <E...> > :
	public Q <E...>, public access <D, E...>
{
	using P = Q <E...>;
	using derived <D>::der;

public:
	using base_type = store;

	using indices = sizes <I...>;
	inline constexpr indices idx() const { return indices(); }

	using access <D, E...>::_;

//-----------------------------------------------------------------------------

	template <size_t J>
	inline rtel <J, P>
	_() && { return fwd <D>(der()).template _at <J>(); }

	template <size_t J>
	inline ltel <J, P>
	_() & { return der().template _at <J>(); }

	template <size_t J>
	inline constexpr cltel <J, P>
	_() const& { return der().template _at <J>(); }

//-----------------------------------------------------------------------------

	template <typename K>
	inline indirect <K, D&&>
	_() && { return indirect <K, D&&>(fwd <D>(der())); }

	template <typename K>
	inline indirect <K, D&>
	_() & { return indirect <K, D&>(der()); }

	template <typename K>
	inline constexpr indirect <K, const D&>
	_() const& { return indirect <K, const D&>(der()); }

//-----------------------------------------------------------------------------

	template <typename F, typename... A>
	inline ret <F(rtref <E>..., A...)>
	call(F&& f, A&&... a) &&
	{
		return fwd <F>(f)(at._<I>(fwd <D>(der()))..., fwd <A>(a)...);
	}

	template <typename F, typename... A>
	inline ret <F(ltref <E>..., A...)>
	call(F&& f, A&&... a) &
	{
		return fwd <F>(f)(at._<I>(der())..., fwd <A>(a)...);
	}

	template <typename F, typename... A>
	inline constexpr ret <F(cltref <E>..., A...)>
	call(F&& f, A&&... a) const&
	{
		return fwd <F>(f)(at._<I>(der())..., fwd <A>(a)...);
	}

//-----------------------------------------------------------------------------

	// TODO: flip element order when in gcc, as a workaround to bug
	// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=51253
	template <typename F> inline void
	loop(F&& f) && { thru{(fwd <F>(f)(at._<I>(fwd <D>(der()))), 0)...}; }

	template <typename F> inline void
	loop(F&& f) & { thru{(fwd <F>(f)(at._<I>(der())), 0)...}; }

	template <typename F> inline void
	loop(F&& f) const& { thru{(fwd <F>(f)(at._<I>(der())), 0)...}; }

//-----------------------------------------------------------------------------

	template <typename T, enable_if <tup_assign <P, T>{}> = 0>
	inline D& operator=(T&& t)
	{
		return thru{at._<I>(der()) = at._<I>(fwd <T>(t))...}, der();
	}

};

//-----------------------------------------------------------------------------

template <typename D, typename P>
class collection <data::base <>, D, P> :
	public store <data::base <>, D, sz_rng_of_p <P>, P> { };

//-----------------------------------------------------------------------------

}  // namespace tuple_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_BASE_HPP
