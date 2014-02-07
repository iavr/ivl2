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

#ifndef IVL_CORE_TYPE_TRAITS_VALUE_HPP
#define IVL_CORE_TYPE_TRAITS_VALUE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template <typename T> add_rref <T> gen();

template <typename T> bool convert(T);

template <size_t N> struct sized { char arr[N]; };

struct thru { template <typename... T> thru(T&&...) { } };

//-----------------------------------------------------------------------------

template <typename A>
INLINE remove_ref <A>&&
mv(A&& a) { return static_cast <remove_ref <A>&&>(a); }

template <typename T, only_if <!is_lref <T>()> = 0>
INLINE constexpr T&&
fwd(remove_ref <T>&& a) { return static_cast <T&&>(a); }

template <typename T>
INLINE constexpr T&&
fwd(remove_ref <T>& a) { return static_cast <T&&>(a); }

//-----------------------------------------------------------------------------

template <typename T, typename A, only_if <!is_lref <A>()> = 0>
INLINE constexpr raw_type <T>&&
as(A&& a) { return static_cast <raw_type <T>&&>(a); }

template <
	typename T, typename A,
	only_if <is_lref <A>() && !is_const <remove_ref <A> >()> = 0
>
INLINE constexpr raw_type <T>&
as(A&& a) { return static_cast <raw_type <T>&>(a); }

template <
	typename T, typename A,
	only_if <is_lref <A>() && is_const <remove_ref <A> >()> = 0
>
INLINE constexpr const raw_type <T>&
as(A&& a) { return static_cast <const raw_type <T>&>(a); }

//-----------------------------------------------------------------------------

template <size_t I, typename A, typename... An, only_if <!I> = 0>
INLINE constexpr A&&
get(A&& a, An&&... an) { return fwd <A>(a); }

template <size_t I, typename A, typename... An, only_if <I> = 0>
INLINE constexpr pick <I - 1, An...>&&
get(A&& a, An&&... an) { return get <I - 1>(fwd <An>(an)...); }

//-----------------------------------------------------------------------------

template <size_t I, typename... A>
INLINE constexpr copy <pick <I, A...> >
get_cp(A&&... a) { return get <I>(fwd <A>(a)...); }

template <typename A>
INLINE constexpr copy <A>
cp(A&& a) { return fwd <A>(a); }

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

using types::traits::mv;
using types::traits::fwd;
using types::traits::as;
using types::traits::get;
using types::traits::get_cp;
using types::traits::cp;

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

struct pre_tmp_call
{
	template <typename F, typename... P, typename... A>
	INLINE constexpr auto operator()(F&& f, types::tmp <P...>, A&&... a) const
	-> decltype(fwd <F>(f).template _<P...>(fwd <A>(a)...))
		{ return fwd <F>(f).template _<P...>(fwd <A>(a)...); }
};

struct tmp_call
{
	template <typename F, typename... A>
	INLINE constexpr auto operator()(F&& f, A&&... a) const
	-> decltype(fwd <F>(f)(fwd <A>(a)...))
		{ return fwd <F>(f)(fwd <A>(a)...); }

	template <typename F, typename... P, typename... A>
	INLINE constexpr auto operator()(F&& f, types::tmp <P...>, A&&... a) const
	-> decltype(fwd <F>(f).template _<P...>(fwd <A>(a)...))
		{ return fwd <F>(f).template _<P...>(fwd <A>(a)...); }
};

struct tmp_call_ret
{
	template <typename F, typename... A>
	auto operator()(F&& f, A&&... a) const
	-> decltype(fwd <F>(f)(fwd <A>(a)...));

	template <typename F, typename... P, typename... A>
	auto operator()(F&& f, types::tmp <P...>, A&&... a) const
	-> decltype(fwd <F>(f).template _<P...>(fwd <A>(a)...));
};

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_TRAITS_VALUE_HPP
