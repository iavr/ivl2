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

#ifndef IVL_DETAILS_CORE_VEC_TUPLE_HPP
#define IVL_DETAILS_CORE_VEC_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

struct C;
namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// no alias: often used
struct tup_apply : uref_of <apply_tuple, any_tuple> { };
struct tup_loop_ : rref_of <loop_tuple,  any_tuple> { };
struct tup_scan_ : rref_of <scan_tuple,  any_tuple> { };

template <typename L>
struct tup_loop_of
{
	template <typename F, typename... A, only_if <any_tuple <A...>{}> = 0>
	INLINE void operator()(F&& f, A&&... a) const
		{ L()(fwd <F>(f), fwd <A>(a)...).loop(); }
};

struct tup_loop : tup_loop_of <tup_loop_>, seq_loop <>
{
	using seq_loop <>::operator();
	using tup_loop_of <tup_loop_>::operator();
};

using tup_scan = tup_loop_of <tup_scan_>;

template <typename F, typename... A>
using tup_auto_for = _if <vec_void <F(A...)>{}, tup_loop, tup_apply>;

using tup_auto = afun::choose_fun <tup_auto_for>;

//-----------------------------------------------------------------------------

template <typename S>
class tup_sep_loop : public seq_sep_loop <S>
{
	using B = seq_sep_loop <S>;

protected:
	using B::val;

public:
	using B::B;

	template <typename F, typename T, only_if <tup_empty <T>{}> = 0>
	INLINE void operator()(F&& f, T&& t) const { };

	template <typename F, typename T, only_if <tup_non_empty<T>{}> = 0>
	INLINE void operator()(F&& f, T&& t) const
	{
		fwd <F>(f)(tup_head()(fwd <T>(t)));
		S&& s = fwd <S>(val());
		tup_loop()(pre_fun()(fwd <F>(f), fwd <S>(s)), tup_tail()(fwd <T>(t)));
	}
};

//-----------------------------------------------------------------------------

template <typename F, typename B = none>
struct val_gen : B { F val() const { return F(); } };

template <typename F> struct atom_gen : F { using F::F; };

//-----------------------------------------------------------------------------

template <typename R, typename T = op::call>
struct tup_vec_for
{
	template <typename... A>
	using map = _if <any_tuple <A...>{}, R, atom_call <T> >;
};

template <typename F, typename R, typename B = none>
using tup_vec_f = vec_fun <
	val_gen <F, B>,
	tup_vec_for <R>::template map
>;

template <typename F, typename B = none>
using tup_vec_apply = tup_vec_f <F, tup_apply, B>;

template <typename F, typename B = none>
using tup_vec_loop = tup_vec_f <F, tup_loop, B>;

template <typename F, typename B = none>
using tup_vec_auto = tup_vec_f <F, tup_auto, B>;

template <typename F, typename B = atom <F> >
using tup_vec = vec_atom <
	atom_gen <B>,
	tup_vec_for <tup_auto>::template map
>;

template <typename F, size_t I = 0>
using tup_vec_mut = tup_vec_f <F, mut_call <tup_loop, I> >;

template <typename F, size_t I = 0>
using tup_vec_copy = tup_vec_f <F, copy_call <tup_apply, I> >;

//-----------------------------------------------------------------------------

template <typename F, typename B = none, typename T = op::bracket>
using tup_bra_vec_apply = bra_vec_fun <
	val_gen <F, B>,
	tup_vec_for <tup_vec_apply <T>, T>::template map
>;

template <typename F, typename B = atom <F>, typename T = op::bracket>
using tup_bra_vec = bra_vec_atom <
	atom_gen <B>,
	tup_vec_for <tup_vec_apply <T>, T>::template map
>;

//-----------------------------------------------------------------------------

template <typename F, size_t I = 0>
struct mut_fun
{
	template <
		typename... A,
		only_if <!is_const <remove_ref <pick <I, A...> > >()>
	= 0>
	INLINE constexpr ret <F(A...)>
	operator()(A&&... a) const { return F()(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, typename L = tup_loop_>
class tup_accum
{
	template <typename T> using acc = bind_args <mut_fun <F>, T>;

public:
	template <
		typename I, typename... A, typename T = copy <I>,
		only_if <any_tuple <A...>{}>
	= 0>
	INLINE constexpr T
	operator()(I&& i, A&&... a) const
		{ return L()(acc <T>(fwd <I>(i)), fwd <A>(a)...).loop().val(); }
};

template <typename F>
using tup_accum_off = tup_accum <F, tup_scan_>;

//-----------------------------------------------------------------------------

template <
	typename F, typename I = F, typename E = get_fun <0>,
	template <typename> class R = common_of,
	typename XI = id_fun, typename XE = id_fun, typename U = tup_accum <F>
>
class tup_fold
{
	template <typename T, typename... A>
	INLINE constexpr copy <ret <XI(T)> >
	op(_true, A&&... a) const { return XI()(I().template _<T>()); }

	template <typename T, typename... A>
	INLINE constexpr copy <ret <XI(T)> >
	op(_false, A&&... a) const
	{
		return U()(XE()(E()(static_cast <R <A> >(tup_head()(fwd <A>(a)))...)),
			tup_tail_of <rref_opt>()(fwd <A>(a))...);  // TODO: tail shifts real offset by -1 !!
	}

public:
	template <
		typename... A, typename T = copy <ret <E(R <A>...)> >,
		only_if <any_tuple <A...>{}>
	= 0>
	INLINE constexpr copy <ret <XI(T)> >
	operator()(A&&... a) const
		{ return op <T>(any_empty <A...>{}, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <size_t O>
struct add_offset
{
	template <typename A>
	INLINE constexpr pre_tuple <rref_opt <A>, size_t>
	operator()(A&& a) const
		{ return pre_tuple <rref_opt <A>, size_t>(fwd <A>(a), O); }
};

template <
	typename F, typename I = F, typename E = get_fun <0>,
	template <typename> class R = common_of
>
using tup_fold_off = tup_fold <
	F, I, E, R, add_offset <size_t(-1)>, add_offset <0>, tup_accum_off <F>
>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_TUPLE_HPP
