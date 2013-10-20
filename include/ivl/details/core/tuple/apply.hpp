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

#ifndef IVL_DETAILS_CORE_TUPLE_APPLY_HPP
#define IVL_DETAILS_CORE_TUPLE_APPLY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuple_details {

//-----------------------------------------------------------------------------

template <typename F, typename A>
class collection <data::apply <>, F, A> : public base_tup <
	apply_tup <F, A>, map <tup_app <F>::template map, tup_types <A> >
>
{
	using P = map <tup_app <F>::template map, tup_types <A> >;
	using B = base_tup <apply_tup <F, A>, P>;

	using EF = under_elem <0, B>;
	using EA = under_elem <1, B>;

	friend base_type_of <B>;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE rtel <J, P>
	_at() && { return EF::get_r()(at._<J>(EA::get_r())); }

	template <size_t J>
	INLINE ltel <J, P>
	_at() & { return EF::get()(at._<J>(EA::get())); }

	template <size_t J>
	INLINE constexpr cltel <J, P>
	_at() const& { return EF::get()(at._<J>(EA::get())); }

//-----------------------------------------------------------------------------

public:
	using B::base_type::operator=;

	template <typename G, typename B>
	explicit INLINE constexpr collection(G&& g, B&& b) :
		B(fwd <G>(g), fwd <B>(b)) { }
};

//-----------------------------------------------------------------------------

}  // namespace tuple_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_APPLY_HPP
