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

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

using apply = seq_apply;

//-----------------------------------------------------------------------------

template <typename S>
class sep_loop : public seq_sep_loop <S, sep_loop <S> >
{
	S&& s;

public:
	explicit INLINE constexpr sep_loop(S&& s) : s{fwd <S>(s)} { }
	INLINE S&& sep() const { return fwd <S>(s); }
};

//-----------------------------------------------------------------------------

struct loop : seq_loop
{
	// TODO: keys
	template <typename S>
	INLINE sep_loop <S>
	operator[](S&& s) const { return sep_loop <S>(fwd <S>(s)); }
};

//-----------------------------------------------------------------------------

// no alias: fwd-declared
template <typename F, typename B = none>
struct vec_apply : seq_vec_apply <F, B> { };

template <typename F, typename B = none>
using vec_loop = seq_vec_loop <F, B>;

template <typename F, typename B = none>
using vec_auto = seq_vec_auto <F, B>;

template <typename F, typename B = atom <F> >
using vec = seq_vec <F, B>;

template <typename F, size_t I = 0> using vec_mut  = seq_vec_mut <F, I>;
template <typename F, size_t I = 0> using vec_copy = seq_vec_copy <F, I>;

template <typename F, typename B = none>
using bra_vec_apply = seq_bra_vec_apply <F, B>;

template <typename F, typename B = atom <F> >
using bra_vec = seq_bra_vec <F, B>;

//-----------------------------------------------------------------------------

template <typename F> using accum     = seq_accum <F>;
template <typename F> using accum_off = seq_accum_off <F>;

template <
	typename F, typename I = F, typename E = get_fun <0>,
	template <typename> class R = common_of,
	typename XI = id_fun, typename XE = id_fun, typename U = accum <F>
>
using fold = seq_fold <F, I, E, R, XI, XE, U>;

template <
	typename F, typename I = F, typename E = get_fun <0>,
	template <typename> class R = common_of
>
using fold_off = seq_fold_off <F, I, E, R>;

template <typename F, typename I = F, typename E = get_fun <0> >
using collect = fold <F, I, E, copy>;

template <typename F, typename I = F, typename E = get_fun <0> >
using collect_off = fold_off <F, I, E, copy>;

//-----------------------------------------------------------------------------

template <typename F>
struct vec_fold : F, vec_apply <arg_fun_of <F> >
{
	using vec_apply <arg_fun_of <F> >::operator();

	template <typename T, only_if <is_tuple <T>{}> = 0>
	INLINE constexpr ret <F(T)>
	operator()(T&& t) const { return F::operator()(fwd <T>(t)); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::apply;
using details::loop;

using details::vec_apply;
using details::vec_loop;
using details::vec_auto;
using details::vec;
using details::vec_mut;
using details::vec_copy;
using details::bra_vec_apply;
using details::bra_vec;

using details::accum;
using details::accum_off;
using details::fold;
using details::fold_off;
using details::collect;
using details::collect_off;

using details::vec_fold;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::apply  apply;
static __attribute__ ((unused)) afun::loop   loop;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_VEC_HPP
