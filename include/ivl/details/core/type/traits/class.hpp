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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_CLASS_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_CLASS_HPP

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

#if IVL_HAS_FEATURE(is_class)

template <typename T> struct is_class : public expr <__is_class(T)> { };

#else

struct is_class_test : public input <c_null>
{
	template <typename T> static pass test(int T::*);
};

template <typename T>
using is_class = expr <sfinae <is_class_test, T>() && !is_union <T>()>;

#endif  // IVL_HAS_FEATURE(is_class)

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(is_empty)

template <typename T> struct is_empty : public expr <__is_empty(T)> { };

#else

struct is_empty_test : public input <>
{
	struct plain { int x; };
	template <typename T> struct derived : public T { int x; };

	template <typename T> static
	pass_if <sizeof(derived <T>) == sizeof(plain)> test(int);
};

template <typename T, bool = is_class <T>{}>
struct is_empty_ : public _false { };

template <typename T>
struct is_empty_ <T, true> : public sfinae <is_empty_test, T> { };

template <typename T> using is_empty = is_empty_ <T>;

#endif  // IVL_HAS_FEATURE(is_empty)

//-----------------------------------------------------------------------------

template <typename T>
using is_base_opt = expr <is_empty <T>() && !is_final <T>()>;

//-----------------------------------------------------------------------------

struct is_abstract_test : public input <c_null>
{
	template <typename T> static pass test(T (*)[1]);
};

template <typename T>
using is_abstract = expr <!sfinae <is_abstract_test, T>() && is_class <T>()>;

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(is_polymorphic)

template <typename T>
struct is_polymorphic : public expr <__is_polymorphic(T)> { };

#else

struct is_polymorphic_test : public input <>
{
	using V = const volatile void;

	template <typename T> static
	pass_if <sizeof((T*) dynamic_cast <V*>(generate <T*>())) != 0> test(int);
};

template <typename T>
using is_polymorphic = sfinae <is_polymorphic_test, T>;

#endif  // IVL_HAS_FEATURE(is_polymorphic)

//-----------------------------------------------------------------------------

}  // namespace details

using details::is_class;
using details::is_empty;
using details::is_base_opt;
using details::is_abstract;
using details::is_polymorphic;

//-----------------------------------------------------------------------------

#define IVL_HAS_TYPE(TYPE)                                                  \
                                                                            \
namespace details {                                                         \
                                                                            \
	struct has_##TYPE##_test : public input <>                               \
	{                                                                        \
		template <typename T> static                                          \
		target <sizeof(typename T::TYPE)> test(int);                          \
	};                                                                       \
                                                                            \
}                                                                           \
                                                                            \
template <typename T>                                                       \
using has_##TYPE = sfinae <details::has_##TYPE##_test, remove_cv <T> >;     \

//-----------------------------------------------------------------------------

IVL_HAS_TYPE(type)
IVL_HAS_TYPE(base_type)
IVL_HAS_TYPE(value_type)

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_HPP
