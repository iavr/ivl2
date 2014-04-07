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

#ifndef IVL_CORE_TYPE_FUN_FUN_HPP
#define IVL_CORE_TYPE_FUN_FUN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

// capture function NS::FUN, calling unqualified FUN
// to allow for custom ADL-based overloads on NS::FUN

#define IVL_FUN_NS(FUN, NS)                                \
                                                           \
namespace ivl_fun {                                        \
namespace details {                                        \
namespace IVL_##FUN {                                      \
                                                           \
using NS::FUN;                                             \
                                                           \
struct IVL_##FUN                                           \
{                                                          \
	template <typename... A>                                \
	INLINE constexpr auto                                   \
	operator()(A&&... a) const                              \
	-> decltype(FUN(::ivl::fwd <A>(a)...))                  \
		{ return FUN(::ivl::fwd <A>(a)...); }                \
};                                                         \
                                                           \
}                                                          \
}                                                          \
}                                                          \
                                                           \
namespace ivl {                                            \
namespace afun {                                           \
                                                           \
using FUN = ::ivl_fun::details::IVL_##FUN::IVL_##FUN;      \
                                                           \
}                                                          \
}                                                          \

//-----------------------------------------------------------------------------

#define IVL_FUN_STD(FUN) IVL_FUN_NS(FUN, ::std)

//-----------------------------------------------------------------------------

IVL_FUN_STD(pow)
IVL_FUN_STD(swap)

//-----------------------------------------------------------------------------

namespace ivl {

static __attribute__ ((unused)) afun::swap  swap;

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_FUN_FUN_HPP
