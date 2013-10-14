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

#ifndef IVL_DETAILS_CORE_TYPE_CONST_CALL_HPP
#define IVL_DETAILS_CORE_TYPE_CONST_CALL_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename R, typename S, typename D, bool V = is_void <R>()>
struct c_call_base;

template <typename R, typename F, typename... A, typename D>
struct c_call_base <R, F(A...), D, false> : public constant <R, D>
{
	inline constexpr operator R() const { return F()()(A()()...); }
};

template <typename R, typename F, typename... A, typename D>
struct c_call_base <R, F(A...), D, true> : public constant <void, D>
{
	inline void operator()() const { F()()(A()()...); }
};

template <typename R, typename F, typename... P, typename... A, typename D>
struct c_call_base <R, F(tmp <P...>, A...), D, false> : public constant <R, D>
{
	inline constexpr
	operator R() const { return F()().template _<P...>(A()()...); }
};

template <typename R, typename F, typename... P, typename... A, typename D>
struct c_call_base <R, F(tmp <P...>, A...), D, true> : public constant <void, D>
{
	inline void operator()() const { F()().template _<P...>(A()()...); }
};

//-----------------------------------------------------------------------------

template <typename T>
// struct val_ct { using type = value_type_of <T>; };
struct val_ct { using type = typename T::value_type; };

template <typename... P>
struct val_ct <tmp <P...> > { using type = tmp <P...>; };

template <typename T> using val_c = type_of <val_ct <T> >;

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct ret_ct : public ret_ct <F(A...)> { };

template <typename F, typename... A>
struct ret_ct <F(A...)> : public ret_t <val_c <F> (val_c <A>...)> { };

template <typename F, typename... A> using ret_c = type_of <ret_ct <F, A...> >;

//-----------------------------------------------------------------------------

template <typename F, typename... A>
struct c_call : public c_call <F(A...)> { };

template <typename F, typename... A>
struct c_call <F(A...)> :
	public c_call_base <ret_c <F(A...)>, F(A...), c_call <F(A...)> > { };

//-----------------------------------------------------------------------------

}  // namespace details

using details::c_call;

//-----------------------------------------------------------------------------

template <typename C, typename... A>
struct c_fun_call : public c_fun_call <C(A...)> { };

template <typename C, typename... A>
struct c_fun_call <C(A...)> : public c_call <c_cons <C>(A...)> { };

template <typename C, C &O, typename... A>
struct c_ref_call : public c_ref_call <C(A...), O> { };

template <typename C, C &O, typename... A>
struct c_ref_call <C(A...), O> : public c_call <c_ref <C, O>(A...)> { };

template <typename C, C const &O, typename... A>
struct c_cref_call : public c_cref_call <C(A...), O> { };

template <typename C, C const &O, typename... A>
struct c_cref_call <C(A...), O> : public c_call <c_cref <C, O>(A...)> { };

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_CONST_CALL_HPP