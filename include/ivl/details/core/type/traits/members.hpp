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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_MEMBERS_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_MEMBERS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <template <typename...> class F, typename C>
using type_sfinae = sfinae <F, remove_cv <C> >;

template <template <typename...> class F, typename C, typename... T>
using member_sfinae = sfinae <F, raw_type <C>, T...>;

//-----------------------------------------------------------------------------

template <template <typename...> class F, typename T>
using has_type = type_sfinae <F, T>;

template <typename...> struct has_member;

template <typename M, typename C>
struct has_member <M, C> :
	_not <member_sfinae <M::template fallback, C>{}> { };

template <typename M, typename C, typename T>
struct has_member <M, C, T> :
	member_sfinae <M::template conv, C, member_ptr <C, T> > { };

template <typename M, typename C, typename T>
struct has_member_ptr : expr <
	is_member_ptr_of <C, T>() && member_sfinae <M::template conv, C, T>()
> { };

template <typename M, typename C>
using has_unique = member_sfinae <M::template type, C>;

template <typename M, typename C>
using member_type = typename M::template type <C>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

#define IVL_HAS_TYPE(TYPE)                                                   \
                                                                             \
template <typename T>                                                        \
using type__##TYPE = typename T::TYPE;                                       \
                                                                             \
template <typename T>                                                        \
using has__##TYPE = details::has_type <type__##TYPE, T>;                     \

//-----------------------------------------------------------------------------

#define IVL_HAS_MEMBER(MEMBER)                                               \
                                                                             \
namespace details {                                                          \
                                                                             \
struct member__##MEMBER                                                      \
{                                                                            \
	struct base { nat MEMBER; };                                              \
	template <typename C> using type = decltype(&C::MEMBER);                  \
   template <typename C> using fallback = type <derive <C, base> >;          \
	template <typename C, typename T>                                         \
	using conv = decltype(convert <T>(&C::MEMBER));                           \
};                                                                           \
                                                                             \
template <typename C, typename... T>                                         \
using has_member__##MEMBER = has_member <member__##MEMBER, C, T...>;         \
                                                                             \
template <typename C, typename T>                                            \
using has_member_ptr__##MEMBER = has_member_ptr <member__##MEMBER, C, T>;    \
                                                                             \
template <typename C>                                                        \
using has_unique__##MEMBER = has_unique <member__##MEMBER, C>;               \
                                                                             \
template <typename C>                                                        \
using member_type__##MEMBER = member_type <member__##MEMBER, C>;             \
                                                                             \
}                                                                            \
                                                                             \
using details::has_member__##MEMBER;                                         \
using details::has_member_ptr__##MEMBER;                                     \
using details::has_unique__##MEMBER;                                         \
using details::member_type__##MEMBER;                                        \

//-----------------------------------------------------------------------------

IVL_HAS_TYPE(type)
IVL_HAS_TYPE(base_type)
IVL_HAS_TYPE(value_type)

// ----------------------------------------------------------------------------

IVL_HAS_MEMBER(begin)
IVL_HAS_MEMBER(end)
IVL_HAS_MEMBER(size)

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_MEMBERS_HPP
