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

#ifndef IVL_CORE_TUPLE_VIEW_SCAN_HPP
#define IVL_CORE_TUPLE_VIEW_SCAN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F, typename A, typename I = sz_rng_of_p <A> >
class scan_impl;

template <typename F, typename... A, size_t... I>
class scan_impl <F, pack <A...>, sizes <I...> > : public tup_base <
	scan_tup <F, A...>, rep <tran_len <tup_types <A>...>{}, nat>
>
{
	using P = rep <tran_len <tup_types <A>...>{}, nat>;
	using B = tup_base <scan_tup <F, A...>, P>;

	using fun = elem <0, F>;
	template <size_t J> using arg = elem_at <J + 1, F, A...>;

	friend base_type_of <B>;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE nat
	call_at() && { return fun::fwd()(J, _at._<J>(arg <I>::fwd())...), nat(); }

	template <size_t J>
	INLINE nat
	call_at() & { return fun::get()(J, _at._<J>(arg <I>::get())...), nat(); }

	template <size_t J>
	INLINE constexpr nat
	call_at() const& { return fun::get()(J, _at._<J>(arg <I>::get())...), nat(); }

//-----------------------------------------------------------------------------

public:
	using B::B;

//-----------------------------------------------------------------------------

	INLINE r_ref <F> loop() && { return B::loop_f(), fun::fwd(); }
	INLINE l_ref <F> loop() &  { return B::loop(), fun::get()(); }

	INLINE constexpr c_ref <F> loop() const& { return B::loop(), fun::get(); }

};

//-----------------------------------------------------------------------------

template <typename F>
class collection <data::scan <>, F>;

template <typename F, typename... A>
class collection <data::scan <>, F, A...> :
	public scan_impl <F, pack <A...> >
{
	using B = scan_impl <F, pack <A...> >;

public:
	using B::B;
	using B::base_type::operator=;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_VIEW_SCAN_HPP
