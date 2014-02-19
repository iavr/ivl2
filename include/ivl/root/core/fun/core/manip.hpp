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

#ifndef IVL_CORE_FUN_CORE_MANIP_HPP
#define IVL_CORE_FUN_CORE_MANIP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// using join  = seq_join;
// using zip   = seq_zip;
// using inner = seq_inner;
//
// using head  = seq_head;
// using tail  = seq_tail;
// using flip  = seq_flip;
// using call  = tup_call;
//
// template <template <typename...> class O = base_opt>
// using tail_of = seq_tail_of <O>;

//-----------------------------------------------------------------------------

template <typename S, typename T>
using manip_sw = map_switch <t_case <is_seq, S>, t_case <is_tuple, T> >;

using join  = seq_join;
using zip   = seq_zip;
using inner = seq_inner;

using head  = seq_head;

template <template <typename...> class O = base_opt>
using tail_of = seq_tail_of <O>;

template <template <typename...> class O = base_opt>
using flip_of = switch_fun_of <manip_sw <seq_flip_of <O>, tup_flip> >;

using tail = tail_of <>;
using flip = flip_of <>;
using call = tup_call;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::join;
using details::zip;
using details::inner;

using details::head;
using details::tail;
using details::flip;
using details::call;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::join  join;
static __attribute__ ((unused)) afun::zip   zip;
static __attribute__ ((unused)) afun::inner inner;

static __attribute__ ((unused)) afun::head  head;
static __attribute__ ((unused)) afun::tail  tail;
static __attribute__ ((unused)) afun::flip  flip;
static __attribute__ ((unused)) afun::call  call;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_CORE_MANIP_HPP
