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

#ifndef IVL_DETAILS_CORE_KEY_KEYS_HPP
#define IVL_DETAILS_CORE_KEY_KEYS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace key {

//-----------------------------------------------------------------------------

struct begin        : public ::ivl::keys::key <begin>         { using P::operator=; };
struct end          : public ::ivl::keys::key <end>           { using P::operator=; };
struct length       : public ::ivl::keys::key <length>        { using P::operator=; };
struct size         : public ::ivl::keys::key <size>          { using P::operator=; };

//-----------------------------------------------------------------------------

}  // namespace key

//-----------------------------------------------------------------------------

static  __attribute__ ((unused))  key::begin        begin;
static  __attribute__ ((unused))  key::end          end;
static  __attribute__ ((unused))  key::length       length;
static  __attribute__ ((unused))  key::size         size;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_DETAILS_CORE_KEY_KEYS_HPP
