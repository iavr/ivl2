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

#ifndef IVL_DETAILS_CORE_VEC_ARRAY_HPP
#define IVL_DETAILS_CORE_VEC_ARRAY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun_details {

//-----------------------------------------------------------------------------

// TODO
struct seq_apply { void operator()(nat); };

//-----------------------------------------------------------------------------

template <typename D>
struct arr_loop : derived <D, arr_loop <D> >
{
	template <typename F, typename A1, enable_if <is_array <A1>{}> = 0>
	INLINE void operator()(F&& f, A1&& a1) const
	{
		this->der().iter(fwd <F>(f), fwd <A1>(a1).begin(), fwd <A1>(a1).end());
	}

	template <
		typename F, typename A1, typename A2,
		enable_if <is_array <A1>{} && is_array <A2>{}> = 0
	>
	INLINE void operator()(F&& f, A1&& a1, A2&& a2) const
	{
		this->der().iter(fwd <F>(f),
			fwd <A1>(a1).begin(), fwd <A1>(a1).end(), fwd <A2>(a2).begin());
	}
};

//-----------------------------------------------------------------------------

template <typename S, typename D>
struct seq_sep_loop : arr_loop <D>
{
	template <typename F, typename B, typename E>
	INLINE void iter(F&& f, const B& b, const E& e) const
	{
		if (b != e) f(*b);
		for (B i = b + 1; i != e; ++i)
			fwd <F>(f)(fwd <S>(this->der().sep())), fwd <F>(f)(*i);
	}
};

//-----------------------------------------------------------------------------

struct seq_loop : arr_loop <seq_loop>
{
	using arr_loop <seq_loop>::operator();

	template <typename F, typename B, typename E>
	INLINE void iter(F&& f, const B& b, const E& e) const
	{
		for (B i = b; i != e; ++i)
			fwd <F>(f)(*i);
	}

	template <typename F, typename B, typename E, typename D>
	INLINE void iter(F&& f, const B& b, const E& e, const D& d) const
	{
		D j = d;
		for (B i = b; i != e; ++i, ++j)
			fwd <F>(f)(*i, *j);
	}
};

//-----------------------------------------------------------------------------

// TODO
template <typename F> struct seq_vec_apply :
	tup_vec_apply <F> { using tup_vec_apply <F>::tup_vec_apply; };

template <typename F> struct seq_vec_loop :
	tup_vec_loop <F> { using tup_vec_loop <F>::tup_vec_loop; };

template <typename F> struct seq_vec_auto :
	tup_vec_auto <F> { using tup_vec_auto <F>::tup_vec_auto; };

template <typename F, size_t I = 0> struct seq_vec_mut :
	tup_vec_mut <F, I> { using tup_vec_mut <F, I>::tup_vec_mut; };

template <typename F, size_t I = 0> struct seq_vec_copy :
	tup_vec_copy <F, I> { using tup_vec_copy <F, I>::tup_vec_copy; };

template <typename F> struct seq_vec :
	tup_vec <F> { using tup_vec <F>::tup_vec; };

//-----------------------------------------------------------------------------

}  // namespace afun_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_ARRAY_HPP
