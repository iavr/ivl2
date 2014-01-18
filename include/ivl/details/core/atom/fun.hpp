/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   T C++ template library extending syntax towards mathematical notation.

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
   MERCHANTABILITY or FITNESS FOR T PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_DETAILS_CORE_ATOM_VEC_HPP
#define IVL_DETAILS_CORE_ATOM_VEC_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace atoms {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename S>
struct store <T, S, true, false> : afun::vec <T>
{
	using afun::vec <T>::vec;
};

//-----------------------------------------------------------------------------

template <typename T, typename S>
struct store <T, S, false, true> : store <T, S, false, false>
{
	using B = store <T, S, false, false>;
	using B::val_f;
	using B::val;

	template <typename... A>
	using op = subs <keys::op_ref, base_opt <A&&>...>;

public:
	using B::B;

//-----------------------------------------------------------------------------

// TODO: activate when '_' is renamed to 'at'
// 	template <typename... A>
// 	INLINE op <T&&, A...>
// 	_(A&&... a) && { return make <op>(val_f(), fwd <A>(a)...); }
//
// 	template <typename... A>
// 	INLINE op <T&, A...>
// 	_(A&&... a) & { return make <op>(val(), fwd <A>(a)...); }
//
// 	template <typename... A>
// 	INLINE constexpr op <const T&, A...>
// 	_(A&&... a) const& { return make <op>(val(), fwd <A>(a)...); }

};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ATOM_VEC_HPP
