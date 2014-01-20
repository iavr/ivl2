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

#ifndef IVL_DETAILS_CORE_ATOM_TRAITS_HPP
#define IVL_DETAILS_CORE_ATOM_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

template <typename T>
struct is_atom_ : _false { };

template <typename T, typename S>
struct is_atom_<atom <T, S> > : _true { };

}  // namespace details

template <typename T> using is_atom = details::is_atom_<raw_type <T> >;

template <typename T>
struct as_tuple : expr <is_tuple <T>() || is_atom <T>()> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename T>
using is_atom_fun_ = expr <is_class <T>() || is_fun <T>()>;

}  // namespace details

template <typename T, typename S> struct is_atom_fun    : _false { };
template <typename T, typename S> struct is_atom_method : _false { };

template <typename T>
struct is_atom_fun <T, data::fun <> > :
	details::is_atom_fun_<raw_type <T> > { };

template <typename T>
struct is_atom_method <T, data::fun <> > :
	is_method_ptr <raw_type <T> > { };

//-----------------------------------------------------------------------------

template <typename T>
struct atom_of_t : _if_t <as_tuple <T>{}, T, atoms::atom <T> > { };
// atom_of <> defined @tuple/begin

//-----------------------------------------------------------------------------

namespace details {

// extending definition @tuple/traits
template <template <typename...> class C, typename... E>
struct tup_tmp_type <C <E...>, true> :
	id_t <atom <tmp <remove_type <E>...> > > { };

template <template <typename...> class C, typename... E>
struct tup_tmp_type <C <E...>, false> : id_t <tmp <E...> > { };

}  // namespace details

//-----------------------------------------------------------------------------

namespace details {

// extending definition @type/traits/transform
template <typename T, typename S>
struct create_rec <atom <T, S> > : create_rec <type_of <atom <T, S> > > { };

template <typename T>
struct create_rec <_type <T> > { using type = atom <create <T> >; };

}  // namespace details

//-----------------------------------------------------------------------------

// extending definition @tuple/type/traits
template <typename T, typename S>
struct under_t <atoms::atom <T, S> > : pack <T> { };

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ATOM_TRAITS_HPP
