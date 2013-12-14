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

#ifndef IVL_DETAILS_CORE_AFUN_MEMBER_HPP
#define IVL_DETAILS_CORE_AFUN_MEMBER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace op {

using types::is_ptr;

//-----------------------------------------------------------------------------

template <typename M> struct key_member;
template <typename M> struct key_call;

//-----------------------------------------------------------------------------

#define IVL_MEMBER(MEMBER)                                    \
                                                              \
template <>                                                   \
struct key_member <key::MEMBER>                               \
{                                                             \
	template <typename C, enable_if <!is_ptr <C>{}> = 0>       \
	INLINE auto                                                \
	operator()(C&& c) const                                    \
	-> decltype(fwd <C>(c) . MEMBER)                           \
		{ return fwd <C>(c) . MEMBER; }                         \
                                                              \
	template <typename C, enable_if <is_ptr <C>{}> = 0>        \
	INLINE auto                                                \
	operator()(C&& c) const                                    \
	-> decltype(fwd <C>(c) -> MEMBER)                          \
		{ return fwd <C>(c) -> MEMBER; }                        \
};                                                            \
                                                              \
template <>                                                   \
struct key_call <key::MEMBER>                                 \
{                                                             \
	template <                                                 \
		typename C, typename... A,                              \
		enable_if <!is_ptr <C>{}> = 0                           \
	>                                                          \
	INLINE auto                                                \
	operator()(C&& c, A&&... a) const                          \
	-> decltype(fwd <C>(c) . MEMBER (fwd <A>(a)...))           \
		{ return fwd <C>(c) . MEMBER (fwd <A>(a)...); }         \
                                                              \
	template <                                                 \
		typename C, typename... A,                              \
		enable_if <is_ptr <C>{}> = 0                            \
	>                                                          \
	INLINE auto                                                \
	operator()(C&& c, A&&... a) const                          \
	-> decltype(fwd <C>(c) -> MEMBER (fwd <A>(a)...))          \
		{ return fwd <C>(c) -> MEMBER (fwd <A>(a)...); }        \
};                                                            \

//-----------------------------------------------------------------------------

IVL_MEMBER(begin)
IVL_MEMBER(end)
IVL_MEMBER(length)
IVL_MEMBER(size)

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace op

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_AFUN_MEMBER_HPP
