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

#ifndef IVL_DETAILS_CORE_TYPE_ENTITY_HPP
#define IVL_DETAILS_CORE_TYPE_ENTITY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

template <typename...> struct id_t;
template <typename T>  struct id_t <T> { using type = T; };
template <>            struct id_t <>  { };

template <typename T> using type_of = typename T::type;

template <typename... T> using id = type_of <id_t <T...> >;

//-----------------------------------------------------------------------------

template <typename P> using length = type_of <length_t <P> >;

template <size_t L> struct sequence { static constexpr size_t length = L; };

template <typename T>
struct type_sequence : public id_t <T>, public sequence <length <T>{}> { };

//-----------------------------------------------------------------------------

template <typename T>
struct _type : public type_sequence <_type <T> > { };

template <typename... E>
struct pack : public type_sequence <pack <E...> > { };

template <typename... E>
struct tmp : public type_sequence <tmp <E...> > { };

template <size_t L, typename T>
struct repeat : public type_sequence <repeat <L, T> > { };

//-----------------------------------------------------------------------------

template <typename D>
struct der { using der_type = D; };

//-----------------------------------------------------------------------------

template <typename D>
struct template_class : public der <D> { };

template <template <typename...> class F, typename...> struct temp;

template <template <typename...> class F, typename D>
struct temp <F, D> : public id_t <D>, public template_class <D> { };

template <template <typename...> class F>
struct temp <F> : public temp <F, temp <F> > { };

//-----------------------------------------------------------------------------

namespace details {

struct subs_fun
{
	template <typename... A, template <typename...> class F>
	static F <A...> _(temp <F>);
};

template <typename T, template <typename...> class F, typename... A>
using apply_subs = decltype(T::template _<A...>(temp <F>()));

template <template <typename...> class F, typename... A>
using subs = apply_subs <subs_fun, F, A...>;

}  // namespace details

using details::subs;

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_ENTITY_HPP
