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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_MEMBER_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_MEMBER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template <typename R> struct sig_ret_t { using type = R; };
template <typename R> struct sig_arg_t;

template <typename R, typename... A>
struct sig_ret_t <R (A...)> { using type = R; };

template <typename R, typename... A>
struct sig_arg_t <R (A...)> : public pack <A...> { };

template <typename S> using sig_ret = type_of <sig_ret_t <S> >;
template <typename S> using sig_arg = type_of <sig_arg_t <S> >;

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename C, typename T>
struct member_parts
{
	using class_type = C;
	using sig_type = T;
	using ret_type = T;
};

template <typename C, typename R, typename... A>
struct member_parts <C, R (A...)>
{
	using class_type = C;
	using sig_type = R (A...);
	using ret_type = R;
	using arg_type = pack <A...>;
};

//-----------------------------------------------------------------------------

template <typename M>
struct member_ { };

template <typename T, typename C>
struct member_ <T C::*> : public member_parts <C, T> { };

//-----------------------------------------------------------------------------

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...)> :
	public member_parts <C, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const> :
	public member_parts <C const, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) volatile> :
	public member_parts <C volatile, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const volatile> :
	public member_parts <C const volatile, R (A...)> { };

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) &> :
	public member_parts <C&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const&> :
	public member_parts <C const&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) volatile&> :
	public member_parts <C volatile&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const volatile&> :
	public member_parts <C const volatile&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) &&> :
	public member_parts <C&&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const&&> :
	public member_parts <C const&&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) volatile&&> :
	public member_parts <C volatile&&, R (A...)> { };

template <typename R, typename C, typename ...A>
struct member_ <R (C::*)(A...) const volatile&&> :
	public member_parts <C const volatile&&, R (A...)> { };

#endif  // IVL_HAS_FEATURE(cxx_reference_qualified_functions)

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename M>
using member = details::member_<raw_type <M> >;

template <typename M>
using member_class = typename member <M>::class_type;

template <typename M>
using member_sig = typename member <M>::sig_type;

template <typename M>
using member_ret = typename member <M>::ret_type;

template <typename M>
using member_arg = typename member <M>::arg_type;

//-----------------------------------------------------------------------------

template <typename C, typename M>
using is_member_ptr_of = expr <
	is_member_ptr <M>() &&
	eq <raw_type <member_class <M> >, raw_type <C> >()
>;

//-----------------------------------------------------------------------------

template <typename C, typename R, typename... A>
struct member_ptr_t : public member_ptr_t <C, R (A...)> { };

template <typename C, typename T>
struct member_ptr_t <C, T> : public id_t <T raw_type <C>::*> { };

template <typename C, typename R, typename... A>
using member_ptr = type_of <member_ptr_t <C, R, A...> >;

//-----------------------------------------------------------------------------

template <typename C, typename R, typename ...A>
struct member_ptr_t <C, R (A...)>
	{ using type = R (C::*)(A...); };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const, R (A...)>
	{ using type = R (C::*)(A...) const; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C volatile, R (A...)>
	{ using type = R (C::*)(A...) volatile; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const volatile, R (A...)>
	{ using type = R (C::*)(A...) const volatile; };

//-----------------------------------------------------------------------------

template <typename C, typename R, typename ...A>
struct member_ptr_t <C&, R (A...)>
	{ using type = R (C::*)(A...) &; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const&, R (A...)>
	{ using type = R (C::*)(A...) const&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C volatile&, R (A...)>
	{ using type = R (C::*)(A...) volatile&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const volatile&, R (A...)>
	{ using type = R (C::*)(A...) const volatile&; };

//-----------------------------------------------------------------------------

template <typename C, typename R, typename ...A>
struct member_ptr_t <C&&, R (A...)>
	{ using type = R (C::*)(A...) &&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const&&, R (A...)>
	{ using type = R (C::*)(A...) const&&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C volatile&&, R (A...)>
	{ using type = R (C::*)(A...) volatile&&; };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const volatile&&, R (A...)>
	{ using type = R (C::*)(A...) const volatile&&; };

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// TODO: variadic version not working in either ggc or clang
template <template <typename...> class F>
struct map_test : public input <>
{
	template <typename T> static
	target <sizeof(F <T>)> test(int);
};

template <template <typename...> class F>
struct map_test2 : public input <>
{
	template <typename T, typename A> static
	target <sizeof(F <T, A>)> test(int);
};

template <template <typename...> class F, typename T>
using type_sfinae = sfinae <map_test <F>, remove_cv <T> >;

template <template <typename...> class F, typename T>
using member_sfinae = sfinae <map_test <F>, raw_type <T> >;

template <template <typename...> class F, typename T, typename A>
using member_sfinae2 = sfinae <map_test2 <F>, raw_type <T>, A>;

//-----------------------------------------------------------------------------

template <template <typename...> class F, typename T>
using has_type = type_sfinae <F, T>;

template <typename M, typename C, bool = is_class <C>() && !is_final <C>()>
struct has_member_ :
	public _not <member_sfinae <M::template fallback, C>{}> { };

template <typename M, typename C>
struct has_member_<M, C, false> : public _false { };

template <typename...> struct has_member;

template <typename M, typename C>
struct has_member <M, C> : public has_member_<M, C> { };

template <typename M, typename C, typename T>
struct has_member <M, C, T> :
	public member_sfinae2 <M::template conv, C, member_ptr <C, T> > { };

template <typename M, typename C, typename T>
struct has_member_ptr : public expr <
	is_member_ptr_of <C, T>() && member_sfinae2 <M::template conv, C, T>()
> { };

template <typename M, typename C>
using has_unique_member = member_sfinae <M::template type, C>;

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
   template <typename C> using fallback = type <derive <base, C> >;          \
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
using has_unique__##MEMBER = has_unique_member <member__##MEMBER, C>;        \
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

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_MEMBER_HPP
