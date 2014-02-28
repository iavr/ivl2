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

#ifndef IVL_CORE_ARRAY_FUN_META_HPP
#define IVL_CORE_ARRAY_FUN_META_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <size_t B, typename F, typename... A>
class lookup_fun_impl
{
	using R = decltype(F().template _<0>(gen <A>()...));
	using P = R(*)(A&&...);

	template <size_t I>
	struct stub
	{
		INLINE constexpr static R f(A&&... a)
			{ return F().template _<I>(fwd <A>(a)...); }
	};

public:
	template <size_t... I>
	INLINE R operator()(sizes <I...>, size_t i, A&&... a) const
	{
		static const P table[] = {stub <I + B>::f...};
		static const P *index = table - B;
		return index[i](fwd <A>(a)...);
	};
};

template <size_t B, size_t E, typename F>
struct lookup_fun
{
	template <typename... A>
	INLINE constexpr decltype(F().template _<0>(gen <A>()...))
	operator()(size_t i, A&&... a) const
	{
		return lookup_fun_impl <B, F, A...>()
			(sz_rng <0, E - B>(), i, fwd <A>(a)...);
	};
};

//-----------------------------------------------------------------------------

template <typename OP>
struct lookup_op_fun
{
	template <size_t K, typename C, typename... A>
	INLINE constexpr auto _(C&& c, A&&... a) const
	-> decltype(fwd <C>(c)._(OP(), size <K>(), fwd <A>(a)...))
		{ return fwd <C>(c)._(OP(), size <K>(), fwd <A>(a)...); }
};

template <size_t B, size_t E, typename OP>
struct lookup_op : lookup_fun <B, E, lookup_op_fun <OP> > { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::lookup_fun;
using details::lookup_op_fun;
using details::lookup_op;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_META_HPP
