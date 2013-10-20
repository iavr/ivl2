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
struct is_atom_ : public _false { };

template <typename T>
struct is_atom_<atom <T> > : public _true { };

template <typename T>
struct as_tuple_<atom <T> > : public _true { };

}  // namespace details

template <typename T> using is_atom = details::is_atom_<raw_type <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = as_tuple <T>{}>
struct atom_of_t_ : public id_t <T> { };

template <typename T>
struct atom_of_t_<T, false> { using type = atom <T>; };

}  // namespace details

template <typename T> using atom_of_t = details::atom_of_t_<T>;
template <typename T> using atom_of   = type_of <atom_of_t <T> >;

//-----------------------------------------------------------------------------

template <typename T>
struct under_t <atom <T> > : public pack <T> { };

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ATOM_TRAITS_HPP
