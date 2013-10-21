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

#ifndef IVL_DETAILS_CORE_TUPLE_TUPLE_HPP
#define IVL_DETAILS_CORE_TUPLE_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuple_details {

//-----------------------------------------------------------------------------

template <size_t... I, typename... E>
class store <data::tuple <>, sizes <I...>, E...> :
	public base_tup <tuple <E...>, pack <E...> >
{
	using P = pack <E...>;
	using B = base_tup <tuple <E...>, P>;

	template <size_t J> using under = under_elem <J, B>;

	friend base_type_of <B>;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE rtel <J, P> _at() && { return under <J>::fwd(); }

	template <size_t J>
	INLINE ltel <J, P> _at() & { return under <J>::get(); }

	template <size_t J>
	INLINE constexpr cltel <J, P> _at() const& { return under <J>::get(); }

//-----------------------------------------------------------------------------

public:
	template <typename... A>
	explicit INLINE constexpr store(_true, A&&... a) : B(fwd <A>(a)...) { }

	template <typename T>
	INLINE constexpr store(T&& t) : B(at._<I>(fwd <T>(t))...) { }
};

//-----------------------------------------------------------------------------

template <typename... E>
class collection <data::tuple <>, E...> :
	public store <data::tuple <>, sz_rng_of <E...>, E...>
{
	using P = pack <E...>;
	using B = store <data::tuple <>, sz_rng_of <E...>, E...>;

public:
	using B::base_type::operator=;
	explicit INLINE constexpr collection(const E&... e) : B(yes, e...) { }

	template <typename... A, enable_if <tup_conv <pack <A...>, P>{}> = 0>
	INLINE constexpr collection(A&&... a) : B(yes, fwd <A>(a)...) { }

	template <typename... A, enable_if <tup_explicit <P, pack <A...> >{}> = 0>
	explicit INLINE constexpr collection(A&&... a) : B(yes, fwd <A>(a)...) { }

	template <typename T, enable_if <tup_conv <T, P>{}> = 0>
	INLINE constexpr collection(T&& t) : B(fwd <T>(t)) { }

	template <typename T, enable_if <tup_explicit <P, T>{}> = 0>
	explicit INLINE constexpr collection(T&& t) : B(fwd <T>(t)) { }
};

//-----------------------------------------------------------------------------

}  // namespace tuple_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_TUPLE_HPP
