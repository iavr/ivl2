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

#ifndef IVL_CORE_AFUN__META_OP__HPP
#define IVL_CORE_AFUN__META_OP__HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

#define IVL_BIND_OP(NAME)                   \
                                            \
namespace afun {                            \
                                            \
using bind_##NAME = bind_of <op::NAME>;     \
                                            \
}                                           \
                                            \
static __attribute__ ((unused))             \
	afun::bind_##NAME bind_##NAME;           \

//-----------------------------------------------------------------------------

IVL_BIND_OP(add)
IVL_BIND_OP(sub)
IVL_BIND_OP(mul)
IVL_BIND_OP(div)
IVL_BIND_OP(mod)

IVL_BIND_OP(eq)
IVL_BIND_OP(neq)
IVL_BIND_OP(gt)
IVL_BIND_OP(lt)
IVL_BIND_OP(ge)
IVL_BIND_OP(le)

IVL_BIND_OP(_and)
IVL_BIND_OP(_or)
IVL_BIND_OP(bit_and)
IVL_BIND_OP(bit_or)
IVL_BIND_OP(bit_xor)

IVL_BIND_OP(left)
IVL_BIND_OP(right)
IVL_BIND_OP(assign)

IVL_BIND_OP(add_as)
IVL_BIND_OP(sub_as)
IVL_BIND_OP(mul_as)
IVL_BIND_OP(div_as)
IVL_BIND_OP(mod_as)

IVL_BIND_OP(and_as)
IVL_BIND_OP(or_as)
IVL_BIND_OP(xor_as)
IVL_BIND_OP(left_as)
IVL_BIND_OP(right_as)

IVL_BIND_OP(ref_member)
IVL_BIND_OP(ptr_member)
IVL_BIND_OP(ref_call)
IVL_BIND_OP(ptr_call)

IVL_BIND_OP(call)
IVL_BIND_OP(bracket)
IVL_BIND_OP(comma)
IVL_BIND_OP(cond)

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_AFUN__META_OP__HPP
