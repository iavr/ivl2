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

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// TODO
struct seq_apply : tup_apply { };

//-----------------------------------------------------------------------------

template <typename D>
struct arr_loop : derived <D, arr_loop <D> >
{
	template <typename F, typename A, only_if <is_array <A>{}> = 0>
	INLINE void operator()(F&& f, A&& a) const
	{
		this->der().iter(fwd <F>(f), fwd <A>(a).begin(), fwd <A>(a).end());
	}

	template <
		typename F, typename A, typename B,
		only_if <is_array <A>{} && is_array <B>{}> = 0
	>
	INLINE void operator()(F&& f, A&& a, B&& b) const
	{
		this->der().iter(fwd <F>(f),
			fwd <A>(a).begin(), fwd <A>(a).end(), fwd <B>(b).begin());
	}
};

//-----------------------------------------------------------------------------

template <typename S, typename D>
class seq_sep_loop : public tup_sep_loop <S, D>, public arr_loop <D>
{
protected:
	using arr_loop <D>::der;

public:
	using tup_sep_loop <S, D>::operator();
	using arr_loop <D>::operator();

	template <typename F, typename B, typename E>
	INLINE void iter(F&& f, const B& b, const E& e) const
	{
		if (b != e) f(*b);
		for (B i = b + 1; i != e; ++i)
			fwd <F>(f)(fwd <S>(der().sep())), fwd <F>(f)(*i);
	}
};

//-----------------------------------------------------------------------------

struct seq_loop : tup_loop, arr_loop <seq_loop>
{
	using tup_loop::operator();
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
template <typename F, typename B = none> struct seq_vec_apply :
	tup_vec_apply <F, B> { using tup_vec_apply <F, B>::tup_vec_apply; };

template <typename F, typename B = none> struct seq_vec_loop :
	tup_vec_loop <F, B> { using tup_vec_loop <F, B>::tup_vec_loop; };

template <typename F, typename B = none> struct seq_vec_auto :
	tup_vec_auto <F, B> { using tup_vec_auto <F, B>::tup_vec_auto; };

template <typename F, typename B = atom <F> > struct seq_vec :
	tup_vec <F, B> { using tup_vec <F, B>::tup_vec; };

template <typename F, size_t I = 0> struct seq_vec_mut :
	tup_vec_mut <F, I> { using tup_vec_mut <F, I>::tup_vec_mut; };

template <typename F, size_t I = 0> struct seq_vec_copy :
	tup_vec_copy <F, I> { using tup_vec_copy <F, I>::tup_vec_copy; };

template <typename F, typename B = none> struct seq_bra_vec_apply :
	tup_bra_vec_apply <F, B> { using tup_bra_vec_apply <F, B>::tup_bra_vec_apply; };

template <typename F, typename B = atom <F> > struct seq_bra_vec :
	tup_bra_vec <F, B> { using tup_bra_vec <F, B>::tup_bra_vec; };

//-----------------------------------------------------------------------------

// TODO
template <typename F> struct seq_accum     : tup_accum <F> { };
template <typename F> struct seq_accum_off : tup_accum_off <F> { };

template <
	typename F, typename I = F, typename E = get_fun <0>,
	template <typename> class R = common_of,
	typename XI = id_fun, typename XE = id_fun, typename U = seq_accum <F>
>
struct seq_fold : tup_fold <F, I, E, R, XI, XE, U> { };

template <
	typename F, typename I = F, typename E = get_fun <0>,
	template <typename> class R = common_of
>
struct seq_fold_off : tup_fold_off <F, I, E, R> { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_ARRAY_HPP
