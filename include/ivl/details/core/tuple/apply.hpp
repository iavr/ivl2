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

template <typename F, typename U>
class collection <data::apply <>, F, U> : public base_tup <
	apply_tup <F, U>, map <tup_app <F>::template map, tup_types <U> >
>
{
	using B = base_type_of <collection>;
	using P = map <tup_app <F>::template map, tup_types <U> >;

	friend B;
	F f;
	U u;

//-----------------------------------------------------------------------------

	template <size_t J>
	inline rtel <J, P>
	_at() && { return fwd <F>(f)(at._<J>(fwd <U>(u))); }

	template <size_t J>
	inline ltel <J, P>
	_at() & { return fwd <F>(f)(at._<J>(u)); }

	template <size_t J>
	inline constexpr cltel <J, P>
	_at() const& { return fwd <F>(f)(at._<J>(u)); }

//-----------------------------------------------------------------------------

public:
	using B::operator=;

	template <typename G, typename V>
	explicit inline constexpr collection(G&& g, V&& v) :
		f(fwd <G>(g)), u(fwd <V>(v)) { }
};

//-----------------------------------------------------------------------------

}  // namespace tuple_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_APPLY_HPP
