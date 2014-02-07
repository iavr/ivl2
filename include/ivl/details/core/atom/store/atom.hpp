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

#ifndef IVL_CORE_ATOM_STORE_ATOM_HPP
#define IVL_CORE_ATOM_STORE_ATOM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace atoms {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename S, typename A = atom_attr <T, S> >
struct store : base_atom <atom <T, S>, _type <T> >
{
	using base_atom <atom <T, S>, _type <T> >::base_atom;
};

//-----------------------------------------------------------------------------

// member_ptr atom
template <typename T, typename S>
class store <T, S, numbers <1, 0> > :
	public base_atom <atom <T, S>, _type <T> >
{
	using B = base_atom <atom <T, S>, _type <T> >;
	using B::val_f;
	using B::val;

	template <typename O, typename... A>
	using op = keys::op_ref <O, uref_opt <A>...>;

public:
	using B::B;

//-----------------------------------------------------------------------------

	template <typename... A>
	INLINE op <T, A...>
	_(A&&... a) && { return op <T, A...>(val_f(), fwd <A>(a)...); }

	template <typename... A>
	INLINE op <T&, A...>
	_(A&&... a) & { return op <T&, A...>(val(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr op <const T&, A...>
	_(A&&... a) const& { return op <const T&, A...>(val(), fwd <A>(a)...); }

};

//-----------------------------------------------------------------------------

template <typename T, typename S>
struct atom : store <T, S>
{
	using store <T, S>::store;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ATOM_STORE_ATOM_HPP
