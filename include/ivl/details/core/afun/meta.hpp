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

#ifndef IVL_DETAILS_CORE_AFUN_META_HPP
#define IVL_DETAILS_CORE_AFUN_META_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun_meta_details {

//-----------------------------------------------------------------------------

template <typename F, typename... E>
class bind_ : private tuple <F>, private tuple <E...>
{
	using TF = tuple <F>;
	using TE = tuple <E...>;

public:
	inline constexpr
	bind_(F&& f, E&&... e) : TF(fwd <F>(f)), TE(fwd <E>(e)...) { }

	template <typename... A>
	inline constexpr auto
	operator()(A&&... a) const
		-> decltype(this->TE::call(generate <F>(), fwd <A>(a)...))
		{ return TE::call(fwd <F>(TF::_()), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, typename... E>
class pre_ : private tuple <F>, private tuple <E...>
{
	using TF = tuple <F>;
	using TE = tuple <E...>;

public:
	inline constexpr
	pre_(F&& f, E&&... e) : TF(fwd <F>(f)), TE(fwd <E>(e)...) { }

	template <typename... A>
	inline constexpr types::ret <F(A&&...)>
	operator()(A&&... a) const
	{
		return TE::call(fwd <F>(TF::_())), fwd <F>(TF::_())(fwd <A>(a)...);
	}
};

//-----------------------------------------------------------------------------

}  // namespace afun_meta_details

//-----------------------------------------------------------------------------

namespace afun {
namespace meta {

// TODO: gcc ICE: template <typename F, typename... E>
template <typename... T> using bind = afun_meta_details::bind_<T...>;
template <typename... T> using pre  = afun_meta_details::pre_<T...>;

}  // namespace meta
}  // namespace afun

//-----------------------------------------------------------------------------

namespace meta {

static __attribute__ ((unused)) afun::rref_of <afun::meta::bind>  bind;
static __attribute__ ((unused)) afun::rref_of <afun::meta::pre>   pre;

}  // namespace meta

using meta::bind;
namespace afun_meta_details { using ivl::bind; }

//-----------------------------------------------------------------------------

namespace afun_meta_details {

struct tup_
{
	template <typename F>
	inline constexpr auto operator()(F&& f) const
		-> decltype(bind(_call, fwd <F>(f)))
		{ return bind(_call, fwd <F>(f)); }
};

}  // namespace afun_meta_details

//-----------------------------------------------------------------------------

namespace afun {
namespace meta {

using tup = afun_meta_details::tup_;

}  // namespace meta
}  // namespace afun

//-----------------------------------------------------------------------------

namespace meta {

static __attribute__ ((unused)) afun::meta::tup tup;

}  // namespace meta

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_AFUN_META_HPP
