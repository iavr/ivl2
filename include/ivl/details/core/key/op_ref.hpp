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

#ifndef IVL_DETAILS_CORE_KEY__OP_REF__HPP
#define IVL_DETAILS_CORE_KEY__OP_REF__HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename O, typename... A>
class op_ref : private raw_tuple <O, A...>
{
	using B = raw_tuple <O, A...>;

	template <typename T>
	using tail = tail_tup <base_opt <T> >;

	using derived <B>::der;
	using derived <B>::der_f;

//-----------------------------------------------------------------------------

public:
	using B::B;

//-----------------------------------------------------------------------------

	INLINE           rtref <O>  op() &&     { return at._<0>(der_f()); }
	INLINE           ltref <O>  op() &      { return at._<0>(der()); }
	INLINE constexpr cltref <O> op() const& { return at._<0>(der()); }

//-----------------------------------------------------------------------------

	INLINE tail <B>
	ref() && { return tail <B>(der_f()); }

	INLINE tail <B&>
	ref() & { return tail <B&>(der()); }

	INLINE constexpr tail <const B&>
	ref() const& { return tail <const B&>(der()); }

};

//-----------------------------------------------------------------------------

}  // namespace details

using details::op_ref;

//-----------------------------------------------------------------------------

}  // namespace keys

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_KEY__OP_REF__HPP
