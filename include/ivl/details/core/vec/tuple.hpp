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

#ifndef IVL_DETAILS_CORE_VEC_TUPLE_HPP
#define IVL_DETAILS_CORE_VEC_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun_details {

//-----------------------------------------------------------------------------

class tup_apply
{
	using val = val_of <apply_tup>;

public:
	template <typename F, typename T, enable_if <is_tuple <T>{}> = 0>
	inline constexpr apply_tup <F&&, T&&>
	operator()(F&& f, T&& t) const
	{
		return apply_tup <F&&, T&&>(fwd <F>(f), fwd <T>(t));
	}

	template <typename F, typename... T, enable_if <any_tuple <T...>{}> = 0>
	inline constexpr auto
	operator()(F&& f, T&&... t) const
	-> decltype(val()(meta::tup(fwd <F>(f)), _inner(fwd <T>(t)...)))
	{
		return val()(meta::tup(fwd <F>(f)), _inner(fwd <T>(t)...));
	}
};

//-----------------------------------------------------------------------------

struct tup_loop
{
	template <typename F, typename T, enable_if <is_tuple <T>{}> = 0>
	inline void
	operator()(F&& f, T&& t) const { fwd <T>(t).loop(fwd <F>(f)); }

	template <typename F, typename... T, enable_if <any_tuple <T...>{}> = 0>
	inline void
	operator()(F&& f, T&&... t) const
	{
		_inner(fwd <T>(t)...).loop(meta::tup(fwd <F>(f)));
	}
};

//-----------------------------------------------------------------------------

template <typename S, typename D>
struct tup_sep_loop : public derived <D, tup_sep_loop <S, D> >
{
	template <typename F, typename T, enable_if <tup_empty <T>{}> = 0>
	inline void operator()(F&& f, T&& t) const { };

	template <typename F, typename T, enable_if <tup_non_empty<T>{}> = 0>
	inline void operator()(F&& f, T&& t) const
	{
		fwd <F>(f)(_head(fwd <T>(t)));
		S&& s = fwd <S>(this->der().sep());
		tup_loop()(meta::pre(fwd <F>(f), fwd <S>(s)), _tail(fwd <T>(t)));
	}
};

//-----------------------------------------------------------------------------

template <typename F>
class tup_vec_apply
{
	using apply = tup_apply;

public:
	template <typename... A, enable_if <!any_tuple <A...>{}> = 0>
	inline constexpr auto
	operator()(A&&... a) const
		-> decltype(F()(fwd <A>(a)...))
		{ return F()(fwd <A>(a)...); }

	template <typename... A, enable_if <any_tuple <A...>{}> = 0>
	inline constexpr auto
	operator()(A&&... a) const
		-> decltype(apply()(*this, fwd <A>(a)...))
		{ return apply()(*this, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F>
class tup_vec_loop
{
	using loop = tup_loop;

public:
	template <typename... A, enable_if <!any_tuple <A...>{}> = 0>
	inline void operator()(A&&... a) const { F()(fwd <A>(a)...); }

	template <typename... A, enable_if <any_tuple <A...>{}> = 0>
	inline void operator()(A&&... a) const { loop()(*this, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F>
class tup_vec
{
	using apply = tup_apply;
	using loop  = tup_loop;

public:
	template <typename... A, enable_if <!any_tuple <A...>{}> = 0>
	inline constexpr auto
	operator()(A&&... a) const
		-> decltype(F()(fwd <A>(a)...))
		{ return F()(fwd <A>(a)...); }

	template <typename... A, enable_if <tup_non_void <F(A...)>{}> = 0>
	inline constexpr auto
	operator()(A&&... a) const
		-> decltype(apply()(*this, fwd <A>(a)...))
		{ return apply()(*this, fwd <A>(a)...); }

	template <typename... A, enable_if <tup_void <F(A...)>{}> = 0>
	inline void operator()(A&&... a) const { loop()(*this, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

}  // namespace afun_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_TUPLE_HPP
