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

namespace afun {

//-----------------------------------------------------------------------------

namespace meta {

//-----------------------------------------------------------------------------

template <typename F, typename... E>
struct bind : public tuple <F>, public tuple <E...>
{
	using TF = tuple <F>;
	using TE = tuple <E...>;

public:
	bind(F&& f, E&&... e) : TF(fwd <F>(f)), TE(fwd <E>(e)...) { }

	template <typename... A>
	inline constexpr auto
	operator()(A&&... a) const
		// TF::_() or this->TF::_() not working: using generate <F>() instead
		-> decltype(this->TE::call(types::generate <F>(), fwd <A>(a)...))
		{ return TE::call(fwd <F>(TF::_()), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, typename... E>
class pre : private tuple <F>, private tuple <E...>
{
	using TF = tuple <F>;
	using TE = tuple <E...> ;

public:
	pre(F&& f, E&&... e) : TF(fwd <F>(f)), TE(fwd <E>(e)...) { }

	template <typename... A>
	inline constexpr types::ret <F(A&&...)>
	operator()(A&&... a) const
	{
		return TE::call(fwd <F>(TF::_())), fwd <F>(TF::_())(fwd <A>(a)...);
	}
};

//-----------------------------------------------------------------------------

}  // namespace meta

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

namespace meta {

static __attribute__ ((unused)) afun::rref_of <afun::meta::bind>  bind;
static __attribute__ ((unused)) afun::rref_of <afun::meta::pre>   pre;

}  // namespace meta

using meta::bind;

//-----------------------------------------------------------------------------

namespace afun_meta_details {

using ivl::bind;

struct tup
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

using tup = afun_meta_details::tup;

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
