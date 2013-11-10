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

#ifndef IVL_DETAILS_CORE_TYPE_PACK_REDUCE_HPP
#define IVL_DETAILS_CORE_TYPE_PACK_REDUCE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace packs {

//-----------------------------------------------------------------------------

namespace details {

template <typename P, bool = is_null <P>{}>
struct _and_p_ : public _if <car <P>{}, _and_p_<cdr <P> >, _false> { };

template <typename P, bool = is_null <P>{}>
struct _or_p_ : public _if <car <P>{}, _true, _or_p_<cdr <P> > > { };

template <typename P> struct _and_p_<P, true> : public _true  { };
template <typename P> struct _or_p_ <P, true> : public _false { };

}  // namespace details

template <typename P> using _and_p = details::_and_p_<P>;
template <typename P> using _or_p  = details::_or_p_<P>;

template <typename... E> using _and = _and_p <pack <E...> >;
template <typename... E> using _or  = _or_p  <pack <E...> >;

//-----------------------------------------------------------------------------

namespace details {

template <template <typename...> class F, typename P, bool = is_null <P>{}>
struct all_p_ : public _if <F <car <P> >{}, all_p_<F, cdr <P> >, _false> { };

template <template <typename...> class F, typename P, bool = is_null <P>{}>
struct any_p_ : public _if <F <car <P> >{}, _true, any_p_<F, cdr <P> > > { };

template <template <typename...> class F, typename P>
struct all_p_ <F, P, true> : public _true  { };

template <template <typename...> class F, typename P>
struct any_p_ <F, P, true> : public _false { };

}  // namespace details

template <template <typename...> class F, typename P>
using all_p = details::all_p_<F, P>;

template <template <typename...> class F, typename P>
using any_p = details::any_p_<F, P>;

template <template <typename...> class F, typename... E>
using all = all_p <F, pack <E...> >;

template <template <typename...> class F, typename... E>
using any  = any_p  <F, pack <E...> >;

//-----------------------------------------------------------------------------

template <typename T, typename P>
using contains_p = any_p <eq_to <T>::template map, P>;

template <typename T, typename... E>
using contains = contains_p <T, pack <E...> >;

//-----------------------------------------------------------------------------

template <typename P> using all_null_p = all_p <is_null, P>;
template <typename P> using any_null_p = any_p <is_null, P>;

template <typename... E> using all_null = all_null_p <pack <E...> >;
template <typename... E> using any_null = any_null_p <pack <E...> >;

//-----------------------------------------------------------------------------

template <size_t L>
using eq_len_to = eq_sz_fun_to <length, L>;

template <typename P>
using eq_len_of = eq_len_to <length <P>{}>;

template <typename P>
struct eq_len_p :
	public all_p <eq_len_of <car <P> >::template map, cdr <P> > { };

template <template <typename...> class C>
struct eq_len_p <C <> > : public _true { };

template <typename... P>
using eq_len = eq_len_p <pack <P...> >;

//-----------------------------------------------------------------------------

namespace details {

template <template <typename...> class F, typename P, bool = any_null_p <P>{}>
struct alls_p_ :
	public _if <embed <F, cars_p <P> >{}, alls_p_<F, cdrs_p <P> >, _false> { };

template <template <typename...> class F, typename P, bool = any_null_p <P>{}>
struct anys_p_ :
	public _if <embed <F, cars_p <P> >{}, _true, anys_p_<F, cdrs_p <P> > > { };

template <template <typename...> class F, typename P>
struct alls_p_<F, P, true> : public _true { };

template <template <typename...> class F, typename P>
struct anys_p_<F, P, true> : public _false { };

}  // namespace details

//-----------------------------------------------------------------------------

template <template <typename...> class F, typename P>
using anys_p = _if <eq_len_p <P>{}, details::anys_p_<F, P>, _false>;

template <template <typename...> class F, typename P>
using alls_p = _if <eq_len_p <P>{}, details::alls_p_<F, P>, _false>;

template <template <typename...> class F, typename... P>
using anys = anys_p <F, pack <P...> >;

template <template <typename...> class F, typename... P>
using alls = alls_p <F, pack <P...> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename P, bool = any_null_p <P>{}>
struct tran_
{
	using type = cons <cars_p <P>, type_of <tran_<cdrs_p <P> > > >;
};

template <typename P>
struct tran_<P, true> { using type = null_of <P>; };

}  // namespace details

template <typename P> using tran_pt = details::tran_<P>;
template <typename P> using tran_p  = type_of <tran_pt <P> >;

template <typename... P> using tran_t = tran_pt <pack <P...> >;
template <typename... P> using tran   = type_of <tran_t <P...> >;

//-----------------------------------------------------------------------------

}  // namespace packs

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_PACK_REDUCE_HPP
