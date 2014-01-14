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

#ifndef IVL_DETAILS_CORE_ATOM_ATOM_HPP
#define IVL_DETAILS_CORE_ATOM_ATOM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace atoms {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename S, bool = is_atom_fun <T, S>()>
class store : public base_tup <atom <T, S>, _type <T> >
{
	using P = pack <T>;
	using B = base_tup <atom <T, S>, _type <T> >;
	using U = elem_at <0, T>;

	friend base_type_of <B>;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE rtref <T> _at() && { return U::fwd(); }

	template <size_t J>
	INLINE ltref <T> _at() & { return U::get(); }

	template <size_t J>
	INLINE constexpr cltref <T> _at() const& { return U::get(); }

//-----------------------------------------------------------------------------

public:
// 	template <typename A = int, enable_if <is_cons <T>{}, A> = 0>
// 	explicit INLINE constexpr store() : B(yes) { }
//
// 	template <typename A>
// 	explicit INLINE constexpr store(A&& a) : B(fwd <A>(a)) { }

	template <typename A = int, enable_if <is_cons <T>{}, A> = 0>
	explicit INLINE constexpr store() : B(yes) { }

	template <typename A, enable_if <is_conv <A, T>{}> = 0>
	INLINE constexpr store(A&& a) : B(fwd <A>(a)) { }

	template <typename A, enable_if <is_explicit <T, A>{}> = 0>
	explicit INLINE constexpr store(A&& a) : B(fwd <A>(a)) { }

	template <typename A, enable_if <tup_tup_conv <A, P>{}> = 0>
	INLINE constexpr store(A&& a) : B(fwd <A>(a).val()) { }

	template <typename A, enable_if <tup_tup_explicit <P, A>{}> = 0>
	explicit INLINE constexpr store(A&& a) : B(fwd <A>(a).val()) { }
};

//-----------------------------------------------------------------------------

template <typename T, typename S>
class atom : public store <T, S>
{
	using B = store <T, S>;

public:
	using B::B;
	using B::base_type::operator=;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ATOM_ATOM_HPP
