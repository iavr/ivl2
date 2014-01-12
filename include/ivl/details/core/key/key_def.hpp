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

#ifndef IVL_DETAILS_CORE_KEY__KEY_DEF__HPP
#define IVL_DETAILS_CORE_KEY__KEY_DEF__HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

#define IVL_KEY_INST(KEY, INST)                    \
                                                   \
namespace key {                                    \
                                                   \
struct KEY : ::ivl::keys::key <KEY>                \
{                                                  \
	using ::ivl::keys::key <KEY>::operator=;        \
};                                                 \
                                                   \
}                                                  \
                                                   \
static __attribute__ ((unused)) key::KEY INST;     \

//-----------------------------------------------------------------------------

#define IVL_MEMBER(MEMBER)                                    \
                                                              \
namespace afun {                                              \
                                                              \
template <>                                                   \
struct key_member <key::MEMBER>                               \
{                                                             \
	template <typename C>                                      \
	INLINE auto                                                \
	operator()(C&& c) const                                    \
	-> decltype(fwd <C>(c) . MEMBER)                           \
		{ return fwd <C>(c) . MEMBER; }                         \
                                                              \
	template <typename C>                                      \
	INLINE auto                                                \
	operator()(C* p) const                                     \
	-> decltype(p -> MEMBER)                                   \
		{ return p -> MEMBER; }                                 \
};                                                            \
                                                              \
template <>                                                   \
struct key_call <key::MEMBER>                                 \
{                                                             \
	template <typename C, typename... A>                       \
	INLINE auto                                                \
	operator()(C&& c, A&&... a) const                          \
	-> decltype(fwd <C>(c) . MEMBER (fwd <A>(a)...))           \
		{ return fwd <C>(c) . MEMBER (fwd <A>(a)...); }         \
                                                              \
	template <typename C, typename... A>                       \
	INLINE auto                                                \
	operator()(C* p, A&&... a) const                           \
	-> decltype(p -> MEMBER (fwd <A>(a)...))                   \
		{ return p -> MEMBER (fwd <A>(a)...); }                 \
};                                                            \
                                                              \
}                                                             \

//-----------------------------------------------------------------------------

#define IVL_KEY_INST_MEMBER(KEY, INST)    \
                                          \
IVL_KEY_INST(KEY, INST)                   \
                                          \
IVL_MEMBER(KEY)                           \

//-----------------------------------------------------------------------------

#define IVL_KEY       (KEY)   IVL_KEY_INST       (KEY, KEY)
#define IVL_KEY_MEMBER(KEY)   IVL_KEY_INST_MEMBER(KEY, KEY)

//-----------------------------------------------------------------------------

IVL_KEY_MEMBER(begin)
IVL_KEY_MEMBER(empty)
IVL_KEY_MEMBER(end)
IVL_KEY_MEMBER(length)
IVL_KEY_MEMBER(size)

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_DETAILS_CORE_KEY__KEY_DEF__HPP
