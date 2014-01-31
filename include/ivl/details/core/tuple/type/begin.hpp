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

#ifndef IVL_DETAILS_CORE_TUPLE_TYPE_BEGIN_HPP
#define IVL_DETAILS_CORE_TUPLE_TYPE_BEGIN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {
namespace details {

template <typename O, typename... A> struct op_ref;

}  // namespace details

using details::op_ref;

}  // namespace keys

//-----------------------------------------------------------------------------

namespace tuples {
namespace details {

using namespace types;

}  // namespace details
}  // namespace tuples

//-----------------------------------------------------------------------------

namespace afun {
namespace details {

using namespace tuples;

}  // namespace details
}  // namespace afun

//-----------------------------------------------------------------------------

namespace types {
namespace traits {

template <typename T> struct as_tuple;
template <typename T> struct atom_of_t;
template <typename T> using  atom_of = type_of <atom_of_t <T> >;
template <typename T> struct is_op_ref;

namespace details {

using namespace tuples;

}  // namespace details
}  // namespace traits
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_TYPE_BEGIN_HPP
