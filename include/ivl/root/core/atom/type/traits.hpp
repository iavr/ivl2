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

#ifndef IVL_CORE_ATOM_TYPE_TRAITS_HPP
#define IVL_CORE_ATOM_TYPE_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct is_atom_      : _false { };
template <typename T> struct is_ext_atom_  : _false { };
template <typename T> struct is_atom_atom_ : is_ext_atom_<T> { };
template <typename T> struct is_tup_atom_  : is_atom_atom_<T> { };
template <typename T> struct is_seq_atom_  : is_atom_atom_<T> { };

template <typename T, typename C> struct is_atom_<atom <T, C> > : _true { };
template <typename T> struct is_ext_atom_<ext_atom <T> > : _true { };
template <typename T> struct is_atom_atom_<atom <T> >    : _true { };
template <typename T> struct is_tup_atom_<tup_atom <T> > : _true { };
template <typename T> struct is_seq_atom_<seq_atom <T> > : _true { };

}  // namespace details

template <typename T> using is_atom     = details::is_atom_<raw_type <T> >;
template <typename T> using is_tup_atom = details::is_tup_atom_<raw_type <T> >;
template <typename T> using is_seq_atom = details::is_seq_atom_<raw_type <T> >;

template <typename T>
struct as_tuple : expr <is_tuple <T>() || is_tup_atom <T>()> { };

template <typename T>
struct as_seq : expr <is_seq <T>() || is_seq_atom <T>()> { };

//-----------------------------------------------------------------------------

template <typename T>
struct tup_atom_of_t : _if_t <as_tuple <T>{}, T, atoms::tup_atom <T> > { };

template <typename T>
struct seq_atom_of_t : _if_t <as_seq <T>{}, T, atoms::seq_atom <T> > { };

// tup_atom_of <> defined @tuple/begin
// seq_atom_of <> defined @array/begin

//-----------------------------------------------------------------------------

namespace details {

template <typename T>
using atom_attr_ = numbers <
	is_method_ptr <T>{}, (is_arr <T>() || is_fun <T>() || is_class <T>())
>;

}  // namespace details

template <typename T, typename C>
struct atom_attr_t : numbers <0, 0, 0, 0> { };

template <typename T>
struct atom_attr_t <T, tag::ext> : details::atom_attr_<raw_type <T> > { };

template <typename T, typename C>
using atom_attr = type_of <atom_attr_t <T, C> >;

//-----------------------------------------------------------------------------

namespace details {

// extending definition @tuple/type/traits
template <template <typename...> class C, typename... E>
struct tup_tmp_type <C <E...>, true> :
	id_t <tup_atom <tmp <remove_type <E>...> > > { };

template <template <typename...> class C, typename... E>
struct tup_tmp_type <C <E...>, false> : id_t <tmp <E...> > { };

}  // namespace details

//-----------------------------------------------------------------------------

namespace details {

// extending definition @type/traits/transform
template <typename T, typename C>
struct copy_rec <atom <T, C> > : copy_rec <type_of <atom <T, C> > > { };

template <typename T>
struct copy_rec <_type <T> > : id_t <atom <copy <T> > > { };

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ATOM_TYPE_TRAITS_HPP
