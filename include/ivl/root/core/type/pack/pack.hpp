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

#ifndef IVL_CORE_TYPE_PACK_PACK_HPP
#define IVL_CORE_TYPE_PACK_PACK_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace packs {

//-----------------------------------------------------------------------------

template <typename P>    struct is_pack                : _false { };
template <typename... E> struct is_pack <pack <E...> > : _true { };

template <typename T> struct is_type              : _false { };
template <typename T> struct is_type <_type <T> > : _true { };

template <typename T>
struct as_pack : expr <is_pack <T>() || is_type <T>()> { };

template <typename T>    struct is_tmp               : _false { };
template <typename... P> struct is_tmp <tmp <P...> > : _true { };

//-----------------------------------------------------------------------------

template <typename T>
struct _type_of_t : _if_t <as_pack <T>{}, T, _type <T> > { };

template <typename T>
using _type_of = type_of <_type_of_t <T> >;

//-----------------------------------------------------------------------------

template <typename P> struct is_null : _false { };

template <template <typename...> class C>
struct is_null <C <> > : _true { };

template <typename T>
struct is_null <repeat <0, T> > : _true { };

//-----------------------------------------------------------------------------

template <typename P> struct null_of_t;
template <typename P> using  null_of = type_of <null_of_t <P> >;

template <template <typename...> class C, typename... E>
struct null_of_t <C <E...> > : id_t <C <> > { };

template <typename T>
struct null_of_t <_type <T> > : pack <> { };

//-----------------------------------------------------------------------------

template <template <typename...> class F, typename P> struct embed_t;

template <
	template <typename...> class F,
	template <typename...> class C, typename... E
>
struct embed_t <F, C <E...> > : id_t <F <E...> > { };

template <template <typename...> class F, typename P>
using embed = type_of <embed_t <F, P> >;

//-----------------------------------------------------------------------------

template <typename P> using pack_of_t = embed_t <pack, P>;
template <typename P> using pack_of = type_of <pack_of_t <P> >;

//-----------------------------------------------------------------------------

template <template <typename...> class F, typename P> struct type_map_t;
template <template <typename...> class F, typename P> struct map_t;

template <
	template <typename...> class F,
	template <typename...> class C, typename... E
> struct type_map_t <F, C <E...> > : id_t <C <type_of <F <E> >...> > { };

template <
	template <typename...> class F,
	template <typename...> class C, typename... E
> struct map_t <F, C <E...> > : id_t <C <F <E>...> > { };

template <template <typename...> class F, typename P>
using type_map = type_of <type_map_t <F, P> >;

template <template <typename...> class F, typename P>
using map = type_of <map_t <F, P> >;

//-----------------------------------------------------------------------------

}  // namespace packs

using namespace packs;

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_PACK_PACK_HPP
