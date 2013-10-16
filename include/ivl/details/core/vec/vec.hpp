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

#ifndef IVL_DETAILS_CORE_VEC_VEC_HPP
#define IVL_DETAILS_CORE_VEC_VEC_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun_details {

//-----------------------------------------------------------------------------

using apply_ = der_nfun <tup_apply, seq_apply>;

//-----------------------------------------------------------------------------

template <typename S>
class sep_loop : public der_nfun <
	tup_sep_loop <S, sep_loop <S> >,
	seq_sep_loop <S, sep_loop <S> >
>
{
	S&& s;

public:
	explicit inline constexpr sep_loop(S&& s) : s{fwd <S>(s)} { }
	S&& sep() const { return fwd <S>(s); }
};

//-----------------------------------------------------------------------------

struct loop_ : public der_nfun <tup_loop, seq_loop>
{
	// TODO: keys
	template <typename S>
	sep_loop <S> operator[](S&& s) const { return sep_loop <S>(fwd <S>(s)); }
};

//-----------------------------------------------------------------------------

template <typename F>
using vec_apply_ = der_nfun <tup_vec_apply <F>, seq_vec_apply <F> >;

template <typename F>
using vec_loop_ = der_nfun <tup_vec_loop <F>, seq_vec_loop <F> >;

template <typename F>
using vec_ = der_nfun <tup_vec <F>, seq_vec <F> >;

//-----------------------------------------------------------------------------

}  // namespace afun_details

//-----------------------------------------------------------------------------

namespace afun {

using apply  = afun_details::apply_;
using loop   = afun_details::loop_;

template <typename F> using vec_apply = afun_details::vec_apply_<F>;
template <typename F> using vec_loop  = afun_details::vec_loop_<F>;
template <typename F> using vec       = afun_details::vec_<F>;

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::apply  apply;
static __attribute__ ((unused)) afun::loop   loop;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_VEC_HPP
