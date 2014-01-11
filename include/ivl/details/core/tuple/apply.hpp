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

template <typename F>
class tup_applier
{
	template <typename... A>
	struct map_t { using type = F(pack <A...>); };

	template <typename... A>
	struct map_t <pack <A...> > : map_t <A...> { };

public:
	template <typename... A>
	using map = type_of <map_t <A...> >;
};

template <typename F, typename... A>
using tup_apply_types =
	map <tup_applier <F>::template map, tup_tran <tup_types <A>...> >;

//-----------------------------------------------------------------------------

template <size_t... I, typename F, typename... A>
class store <data::apply <>, sizes <I...>, F, A...> :
	public base_tup <apply_tup <F, A...>, tup_apply_types <F, A...> >
{
	using P = tup_apply_types <F, A...>;
	using B = base_tup <apply_tup <F, A...>, P>;

	using fun = elem_at <0, F, A...>;
	template <size_t J> using arg = elem_at <J + 1, F, A...>;

	friend base_type_of <B>;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE rtel <J, P>
	_at() && { return fun::fwd()(at._<J>(arg <I>::fwd())...); }

	template <size_t J>
	INLINE ltel <J, P>
	_at() & { return fun::get()(at._<J>(arg <I>::get())...); }

	template <size_t J>
	INLINE constexpr cltel <J, P>
	_at() const& { return fun::get()(at._<J>(arg <I>::get())...); }

//-----------------------------------------------------------------------------

public:
	using B::B;
};

//-----------------------------------------------------------------------------

template <typename F>
class collection <data::apply <>, F>;

template <typename F, typename... A>
class collection <data::apply <>, F, A...> :
	public store <data::apply <>, sz_rng_of <A...>, F, A...>
{
	using B = store <data::apply <>, sz_rng_of <A...>, F, A...>;

public:
	using B::B;
	using B::base_type::operator=;
};

//-----------------------------------------------------------------------------

}  // namespace tuple_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_APPLY_HPP
