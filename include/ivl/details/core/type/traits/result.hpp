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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_RESULT_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_RESULT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

template <typename... P> struct tmp { };

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <bool MEM = false>
struct invoker
{
	template <typename... A>
	auto operator()(flexi, A&&... a) -> nat;

	template <typename F, typename... A>
	auto operator()(F&& f, A&&... a)
		-> decltype(fwd <F>(f)(fwd <A>(a)...));

	template <typename F, typename... P, typename... A>
	auto operator()(F&& f, tmp <P...>, A&&... a)
		-> decltype(fwd <F>(f).template _<P...>(fwd <A>(a)...));
};

//-----------------------------------------------------------------------------

template <>
struct invoker <true>
{
	template <typename F, typename A, typename C, bool M, bool I, bool = false>
	struct ok : public ok <remove_ref <F>, remove_ref <A>, C, M, I, true> { };

	template <typename F, typename A, typename C, bool M, bool I>
	struct ok <F, A, C, M, I, true> : public expr <
		(M ? is_method_ptr <F>{} : is_prop_ptr <F>{}) &&
		(I ^ is_base_eq <C, A>{})
	> { };

//-----------------------------------------------------------------------------

	template <typename... An>
	auto operator()(flexi, An&&... an) -> nat;

	template <
		typename F, typename A, typename... An,
		enable_if <ok <F, A, member_class <F>, true, false>{}> = 0
	>
	auto operator()(F&& f, A&& a, An&&... an)
		-> decltype((fwd <A>(a).*f)(fwd <An>(an)...));

	template <
		typename F, typename A, typename... An,
		enable_if <ok <F, A, member_class <F>, true, true>{}> = 0
	>
	auto operator()(F&& f, A&& a, An&&... an)
		-> decltype(((*fwd <A>(a)).*f)(fwd <An>(an)...));

	template <
		typename F, typename A,
		enable_if <ok <F, A, member_class <F>, false, false>{}> = 0
	>
	auto operator()(F&& f, A&& a) -> decltype(fwd<A>(a).*f);

	template <
		typename F, typename A,
		enable_if <ok <F, A, member_class <F>, false, true>{}> = 0
	>
	auto operator()(F&& f, A&& a) -> decltype((*fwd<A>(a)).*f);
};

//-----------------------------------------------------------------------------

template <typename S, bool M, bool C> struct invoke_fun;

template <typename F, typename... A, bool M>
struct invoke_fun <F(A...), M, true> : public check_t <
	decltype(invoker <M>()(generate <F>(), generate <A>()...))
> { };

template <typename F, typename... P, typename... A, bool M>
struct invoke_fun <F(tmp <P...>, A...), M, true> : public check_t <
	decltype(invoker <M>()(generate <F>(), tmp <P...>(), generate <A>()...))
> { };

template <typename F, typename... A, bool M>
struct invoke_fun <F(A...), M, false> : public nat { };

template <typename F, typename... P, typename... A, bool M>
struct invoke_fun <F(tmp <P...>, A...), M, false> : public nat { };

//-----------------------------------------------------------------------------

template <typename S, bool M = false> struct invoke_t;

template <typename F, typename... A, bool M>
struct invoke_t <F(A...), M> :
	public invoke_fun <F(A...), M, is_complete <F>{}> { };

template <typename S> using fun_result_t_ = invoke_t <S>;
template <typename S> using mem_result_t_ = invoke_t <S, true>;

template <typename S>
using result_t_ = if_nat <fun_result_t_<S>, mem_result_t_<S> >;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct fun_result_t : public fun_result_t <F(A...)> { };

template <typename F, typename... A>
struct fun_result_t <F(A...)> : public details::fun_result_t_<F(A...)> { };

template <typename F, typename... A>
struct mem_result_t : public mem_result_t <F(A...)> { };

template <typename F, typename... A>
struct mem_result_t <F(A...)> : public details::mem_result_t_<F(A...)> { };

template <typename F, typename... A>
struct result_t : public result_t <F(A...)> { };

template <typename F, typename... A>
struct result_t <F(A...)> : public details::result_t_<F(A...)> { };

template <typename... S> using fun_result = type_of <fun_result_t <S...> >;
template <typename... S> using mem_result = type_of <mem_result_t <S...> >;
template <typename... S> using result     = type_of <result_t <S...> >;

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct ret_t : public ret_t <F(A...)> { };

template <typename F, typename... A>
struct ret_t <F(A...)> : public id_t <
	decltype(generate <F>()(generate <A>()...))
> { };

template <typename F, typename... P, typename... A>
struct ret_t <F(tmp <P...>, A...)> : public id_t <
	decltype(generate <F>().template _<P...>(generate <A>()...))
> { };

template <typename F, typename... A> using ret = type_of <ret_t <F, A...> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_RESULT_HPP
