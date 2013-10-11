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
struct seq_apply { void operator()(); };
struct seq_join  { void operator()(); };
struct seq_zip   { void operator()(); };

//-----------------------------------------------------------------------------

template <typename D>
struct arr_loop : public derived <D, arr_loop <D> >
{
	template <typename F, typename A1, enable_if <is_array <A1>{}> = 0>
	inline void operator()(F&& f, A1&& a1) const
	{
		this->der().iter(fwd <F>(f), fwd <A1>(a1).begin(), fwd <A1>(a1).end());
	}

	template <
		typename F, typename A1, typename A2,
		enable_if <is_array <A1>{} && is_array <A2>{}> = 0
	>
	inline void operator()(F&& f, A1&& a1, A2&& a2) const
	{
		this->der().iter(fwd <F>(f),
			fwd <A1>(a1).begin(), fwd <A1>(a1).end(), fwd <A2>(a2).begin());
	}
};

//-----------------------------------------------------------------------------

template <typename S, typename D>
struct seq_sep_loop : public arr_loop <D>
{
	template <typename F, typename B, typename E>
	inline void iter(F&& f, const B& b, const E& e) const
	{
		if (b != e) f(*b);
		for (B i = b + 1; i != e; ++i)
			fwd <F>(f)(fwd <S>(this->der().sep())), fwd <F>(f)(*i);
	}
};

//-----------------------------------------------------------------------------

struct seq_loop : public arr_loop <seq_loop>
{
	using arr_loop <seq_loop>::operator();

	template <typename F, typename B, typename E>
	inline void iter(F&& f, const B& b, const E& e) const
	{
		for (B i = b; i != e; ++i)
			fwd <F>(f)(*i);
	}

	template <typename F, typename B, typename E, typename D>
	inline void iter(F&& f, const B& b, const E& e, const D& d) const
	{
		D j = d;
		for (B i = b; i != e; ++i, ++j)
			fwd <F>(f)(*i, *j);
	}
};

//-----------------------------------------------------------------------------

}  // namespace afun_details

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_ARRAY_HPP
