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

#ifndef IVL_CORE_TYPE_FUN_CALL_HPP
#define IVL_CORE_TYPE_FUN_CALL_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

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

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_FUN_CALL_HPP
