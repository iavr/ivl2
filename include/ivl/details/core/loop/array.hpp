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

#ifndef IVL_DETAILS_CORE_LOOP_ARRAY_HPP
#define IVL_DETAILS_CORE_LOOP_ARRAY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// template <typename D>
// struct arr_loop : derived <D, arr_loop <D> >
// {
// 	template <typename F, typename A, only_if <is_array <A>{}> = 0>
// 	INLINE void operator()(F&& f, A&& a) const
// 	{
// 		this->der().iter(fwd <F>(f), fwd <A>(a).begin(), fwd <A>(a).end());
// 	}
//
// 	template <
// 		typename F, typename A, typename B,
// 		only_if <is_array <A>{} && is_array <B>{}> = 0
// 	>
// 	INLINE void operator()(F&& f, A&& a, B&& b) const
// 	{
// 		this->der().iter(fwd <F>(f),
// 			fwd <A>(a).begin(), fwd <A>(a).end(), fwd <B>(b).begin());
// 	}
// };
//
// //-----------------------------------------------------------------------------
//
// template <typename S, typename D>
// class seq_sep_loop : public tup_sep_loop <S, D>, public arr_loop <D>
// {
// protected:
// 	using arr_loop <D>::der;
//
// public:
// 	using tup_sep_loop <S, D>::operator();
// 	using arr_loop <D>::operator();
//
// 	template <typename F, typename B, typename E>
// 	INLINE void iter(F&& f, const B& b, const E& e) const
// 	{
// 		if (b != e) f(*b);
// 		for (B i = b + 1; i != e; ++i)
// 			fwd <F>(f)(fwd <S>(der().sep())), fwd <F>(f)(*i);
// 	}
// };
//
// //-----------------------------------------------------------------------------
//
// struct seq_loop : tup_loop, arr_loop <seq_loop>
// {
// 	using tup_loop::operator();
// 	using arr_loop <seq_loop>::operator();
//
// 	template <typename F, typename B, typename E>
// 	INLINE void iter(F&& f, const B& b, const E& e) const
// 	{
// 		for (B i = b; i != e; ++i)
// 			fwd <F>(f)(*i);
// 	}
//
// 	template <typename F, typename B, typename E, typename D>
// 	INLINE void iter(F&& f, const B& b, const E& e, const D& d) const
// 	{
// 		D j = d;
// 		for (B i = b; i != e; ++i, ++j)
// 			fwd <F>(f)(*i, *j);
// 	}
// };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_LOOP_ARRAY_HPP
