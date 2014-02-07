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

#ifndef IVL_CORE_TYPE_FUN_OP_HPP
#define IVL_CORE_TYPE_FUN_OP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl_op {

//-----------------------------------------------------------------------------

namespace details {

using ::ivl::types::bare_type;
using ::ivl::fwd;

}  // namespace details

//-----------------------------------------------------------------------------

#define IVL_OP1(NAME, OP)                \
                                         \
namespace details {                      \
                                         \
struct NAME                              \
{                                        \
	template <typename A>                 \
	INLINE constexpr auto                 \
	operator()(A&& a) const               \
	-> decltype(OP fwd <A>(a))            \
		{ return OP fwd <A>(a); }          \
};                                       \
                                         \
}                                        \
                                         \
using details::NAME;                     \

//-----------------------------------------------------------------------------

#define IVL_OP1_PRE(NAME, OP)            \
                                         \
namespace details {                      \
                                         \
struct NAME                              \
{                                        \
	template <typename A>                 \
	INLINE auto                           \
	operator()(A&& a) const               \
	-> decltype(OP fwd <A>(a))            \
		{ return OP fwd <A>(a); }          \
};                                       \
                                         \
}                                        \
                                         \
using details::NAME;                     \

//-----------------------------------------------------------------------------

#define IVL_OP1_POST(NAME, OP)           \
                                         \
namespace details {                      \
                                         \
struct NAME                              \
{                                        \
	template <typename A>                 \
	INLINE auto                           \
	operator()(A&& a) const               \
	-> decltype(fwd <A>(a) OP)            \
		{ return fwd <A>(a) OP; }          \
};                                       \
                                         \
}                                        \
                                         \
using details::NAME;                     \

//-----------------------------------------------------------------------------

#define IVL_OP2(NAME, OP)                            \
                                                     \
namespace details {                                  \
                                                     \
struct NAME                                          \
{                                                    \
	template <typename A, typename B>                 \
	INLINE constexpr auto                             \
	operator()(A&& a, B&& b) const                    \
	-> decltype(fwd <A>(a) OP fwd <B>(b))             \
		{ return fwd <A>(a) OP fwd <B>(b); }           \
};                                                   \
                                                     \
}                                                    \
                                                     \
using details::NAME;                                 \

//-----------------------------------------------------------------------------

#define IVL_OP2_MUT(NAME, OP)                        \
                                                     \
namespace details {                                  \
                                                     \
struct NAME                                          \
{                                                    \
	template <typename A, typename B>                 \
	INLINE auto                                       \
	operator()(A&& a, B&& b) const                    \
	-> decltype(fwd <A>(a) OP fwd <B>(b))             \
		{ return fwd <A>(a) OP fwd <B>(b); }           \
};                                                   \
                                                     \
}                                                    \
                                                     \
using details::NAME;                                 \

//-----------------------------------------------------------------------------

#define IVL_OP_CAST(NAME)                                     \
                                                              \
namespace details {                                           \
                                                              \
struct _##NAME##_cast                                         \
{                                                             \
	template <typename T, typename A>                          \
	INLINE constexpr T                                         \
	_(A&& a) const { return NAME##_cast <T>(fwd <A>(a)); }     \
};                                                            \
                                                              \
}                                                             \
                                                              \
using details::_##NAME##_cast;                                \

//-----------------------------------------------------------------------------

IVL_OP1(plus,  +)
IVL_OP1(minus, -)

IVL_OP1_PRE(inc_, ++)
IVL_OP1_PRE(dec_, --)
IVL_OP1_POST(_inc, ++)
IVL_OP1_POST(_dec, --)

IVL_OP2(add, +)
IVL_OP2(sub, -)
IVL_OP2(mul, *)
IVL_OP2(div, /)
IVL_OP2(mod, %)

//-----------------------------------------------------------------------------

IVL_OP2(eq,  ==)
IVL_OP2(neq, !=)
IVL_OP2(gt,  >)
IVL_OP2(lt,  <)
IVL_OP2(ge,  >=)
IVL_OP2(le,  <=)

IVL_OP1(_not, !)
IVL_OP2(_and, &&)
IVL_OP2(_or,  ||)

IVL_OP1(bit_not, ~)
IVL_OP2(bit_and, &)
IVL_OP2(bit_or,  |)
IVL_OP2(bit_xor, ^)

//-----------------------------------------------------------------------------

IVL_OP2_MUT(left,  <<)
IVL_OP2_MUT(right, >>)
IVL_OP2_MUT(assign, =)

IVL_OP2_MUT(add_as, +=)
IVL_OP2_MUT(sub_as, -=)
IVL_OP2_MUT(mul_as, *=)
IVL_OP2_MUT(div_as, /=)
IVL_OP2_MUT(mod_as, %=)

IVL_OP2_MUT(and_as,   &=)
IVL_OP2_MUT(or_as,    |=)
IVL_OP2_MUT(xor_as,   ^=)
IVL_OP2_MUT(left_as,  <<=)
IVL_OP2_MUT(right_as, >>=)

//-----------------------------------------------------------------------------

IVL_OP1(deref, *)
IVL_OP1(addr,  &)

IVL_OP2(ref_member, .*)
IVL_OP2(ptr_member, ->*)

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct ref_call
{
	template <typename C, typename M, typename... A>
	INLINE constexpr auto operator()(C&& c, M&& m, A&&... a) const
	-> decltype(( fwd <C>(c) .* fwd <M>(m) ) ( fwd <A>(a)... ))
		{ return ( fwd <C>(c) .* fwd <M>(m) ) ( fwd <A>(a)... ); }
};

//-----------------------------------------------------------------------------

struct ptr_call
{
	template <typename C, typename M, typename... A>
	INLINE constexpr auto operator()(C&& c, M&& m, A&&... a) const
	-> decltype(( fwd <C>(c) ->* fwd <M>(m) ) ( fwd <A>(a)... ))
		{ return ( fwd <C>(c) ->* fwd <M>(m) ) ( fwd <A>(a)... ); }
};

//-----------------------------------------------------------------------------

struct call
{
	template <typename F, typename... A>
	INLINE constexpr auto operator()(F&& f, A&&... a) const
	-> decltype(fwd <F>(f) ( fwd <A>(a)... ))
		{ return fwd <F>(f) ( fwd <A>(a)... ); }
};

//-----------------------------------------------------------------------------

struct bracket
{
	template <typename A, typename B>
	INLINE constexpr auto operator()(A&& a, B&& b) const
	-> decltype(fwd <A>(a) [ fwd <B>(b) ])
		{ return fwd <A>(a) [ fwd <B>(b) ]; }
};

//-----------------------------------------------------------------------------

struct comma
{
	template <typename A, typename B>
	INLINE constexpr auto operator()(A&& a, B&& b) const
	-> decltype(fwd <A>(a) , fwd <B>(b))
		{ return fwd <A>(a) , fwd <B>(b); }
};

//-----------------------------------------------------------------------------

struct cond
{
	template <typename A, typename B, typename C>
	INLINE constexpr auto operator()(A&& a, B&& b, C&& c) const
	-> decltype(fwd <A>(a) ? fwd <B>(b) : fwd <C>(c))
		{ return fwd <A>(a) ? fwd <B>(b) : fwd <C>(c); }
};

//-----------------------------------------------------------------------------

struct _sizeof
{
	template <typename T>
	INLINE constexpr size_t _() const { return sizeof(T); }

	template <typename T>
	INLINE constexpr size_t operator()(T&& v) const
		{ return sizeof(fwd <T>(v)); }
};

struct _alignof
{
	template <typename T>
	INLINE constexpr size_t _() const { return alignof(T); }
};

//-----------------------------------------------------------------------------

struct conv
{
	template <typename T, typename A>
	INLINE constexpr T _(A&& a) const { return (T) fwd <A>(a); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::ref_call;
using details::ptr_call;
using details::call;
using details::bracket;
using details::comma;
using details::cond;
using details::_sizeof;
using details::_alignof;
using details::conv;

//-----------------------------------------------------------------------------

IVL_OP_CAST(static)
IVL_OP_CAST(dynamic)
IVL_OP_CAST(const)
IVL_OP_CAST(reinterpret)

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct _new
{
	template <typename C>
	INLINE auto _() const
	-> decltype(new C)
		{ return new C; }

	template <typename C>
	INLINE auto _(size_t n0) const
	-> decltype(new C[n0])
		{ return new C[n0]; }

	template <typename C, size_t n1>
	INLINE auto _(size_t n0) const
	-> decltype(new C[n0][n1])
		{ return new C[n0][n1]; }

	template <typename C, size_t n1, size_t n2>
	INLINE auto _(size_t n0) const
	-> decltype(new C[n0][n1][n2])
		{ return new C[n0][n1][n2]; }
};

//-----------------------------------------------------------------------------

struct new_nothrow
{
	template <typename C>
	INLINE auto _() const
	-> decltype(new (std::nothrow) C)
		{ return new (std::nothrow) C; }

	template <typename C>
	INLINE auto _(size_t n0) const
	-> decltype(new (std::nothrow) C[n0])
		{ return new (std::nothrow) C[n0]; }

	template <typename C, size_t n1>
	INLINE auto _(size_t n0) const
	-> decltype(new (std::nothrow) C[n0][n1])
		{ return new (std::nothrow) C[n0][n1]; }

	template <typename C, size_t n1, size_t n2>
	INLINE auto _(size_t n0) const
	-> decltype(new (std::nothrow) C[n0][n1][n2])
		{ return new (std::nothrow) C[n0][n1][n2]; }
};

//-----------------------------------------------------------------------------

struct place
{
	template <typename C>
	INLINE void operator()(C&& c) const
		{ new (fwd <C>(c)) bare_type <C>; }

	template <typename C>
	INLINE void operator()(C&& c, size_t n0) const
		{ new (fwd <C>(c)) bare_type <C>[n0]; }

	template <size_t n1, typename C>
	INLINE void _(C&& c, size_t n0) const
		{ new (fwd <C>(c)) bare_type <C>[n0][n1]; }

	template <size_t n1, size_t n2, typename C>
	INLINE void _(C&& c, size_t n0) const
		{ new (fwd <C>(c)) bare_type <C>[n0][n1][n2]; }
};

//-----------------------------------------------------------------------------

struct new_val
{
	template <typename C>
	INLINE auto _() const
	-> decltype(new C())
		{ return new C(); }

	template <typename C>
	INLINE auto _(size_t n0) const
	-> decltype(new C[n0]())
		{ return new C[n0](); }

	template <typename C, size_t n1>
	INLINE auto _(size_t n0) const
	-> decltype(new C[n0][n1]())
		{ return new C[n0][n1](); }

	template <typename C, size_t n1, size_t n2>
	INLINE auto _(size_t n0) const
	-> decltype(new C[n0][n1][n2]())
		{ return new C[n0][n1][n2](); }
};

//-----------------------------------------------------------------------------

struct new_nothrow_val
{
	template <typename C>
	INLINE auto _() const
	-> decltype(new (std::nothrow) C())
		{ return new (std::nothrow) C(); }

	template <typename C>
	INLINE auto _(size_t n0) const
	-> decltype(new (std::nothrow) C[n0]())
		{ return new (std::nothrow) C[n0](); }

	template <typename C, size_t n1>
	INLINE auto _(size_t n0) const
	-> decltype(new (std::nothrow) C[n0][n1]())
		{ return new (std::nothrow) C[n0][n1](); }

	template <typename C, size_t n1, size_t n2>
	INLINE auto _(size_t n0) const
	-> decltype(new (std::nothrow) C[n0][n1][n2]())
		{ return new (std::nothrow) C[n0][n1][n2](); }
};

//-----------------------------------------------------------------------------

struct place_val
{
	template <typename C>
	INLINE void operator()(C&& c) const
		{ new (fwd <C>(c)) bare_type <C>(); }

	template <typename C>
	INLINE void operator()(C&& c, size_t n0) const
		{ new (fwd <C>(c)) bare_type <C>[n0](); }

	template <size_t n1, typename C>
	INLINE void _(C&& c, size_t n0) const
		{ new (fwd <C>(c)) bare_type <C>[n0][n1](); }

	template <size_t n1, size_t n2, typename C>
	INLINE void _(C&& c, size_t n0) const
		{ new (fwd <C>(c)) bare_type <C>[n0][n1][n2](); }
};

//-----------------------------------------------------------------------------

struct new_direct
{
	template <typename C, typename... A>
	INLINE auto _(A&&... a) const
	-> decltype(new C ( fwd <A>(a)... ) )
		{ return new C ( fwd <A>(a)... ) ; }
};

//-----------------------------------------------------------------------------

struct new_nothrow_direct
{
	template <typename C, typename... A>
	INLINE auto _(A&&... a) const
	-> decltype(new (std::nothrow) C ( fwd <A>(a)... ) )
		{ return new (std::nothrow) C ( fwd <A>(a)... ) ; }
};

//-----------------------------------------------------------------------------

struct place_direct
{
	template <typename C, typename... A>
	INLINE void operator()(C&& c, A&&... a) const
		{ new (fwd <C>(c)) bare_type <C> ( fwd <A>(a)... ) ; }
};

//-----------------------------------------------------------------------------

struct new_list
{
	template <typename C, typename... A>
	INLINE auto _(A&&... a) const
	-> decltype(new C { fwd <A>(a)... } )
		{ return new C { fwd <A>(a)... } ; }
};

//-----------------------------------------------------------------------------

struct new_nothrow_list
{
	template <typename C, typename... A>
	INLINE auto _(A&&... a) const
	-> decltype(new (std::nothrow) C { fwd <A>(a)... } )
		{ return new (std::nothrow) C { fwd <A>(a)... } ; }
};

//-----------------------------------------------------------------------------

struct place_list
{
	template <typename C, typename... A>
	INLINE void operator()(C&& c, A&&... a) const
		{ new (fwd <C>(c)) bare_type <C> { fwd <A>(a)... } ; }
};

//-----------------------------------------------------------------------------

struct _delete
{
	template <typename C>
	INLINE void operator()(C&& c) const { delete fwd <C>(c); }
};

//-----------------------------------------------------------------------------

struct delete_array
{
	template <typename C>
	INLINE void operator()(C&& c) const { delete [] fwd <C>(c); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::_new;
using details::new_nothrow;
using details::place;
using details::new_val;
using details::new_nothrow_val;
using details::place_val;
using details::new_direct;
using details::new_nothrow_direct;
using details::place_direct;
using details::new_list;
using details::new_nothrow_list;
using details::place_list;
using details::_delete;
using details::delete_array;

//-----------------------------------------------------------------------------

}  // namespace ivl_op

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {
namespace op {

using namespace ivl_op;

}  // namespace op
}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_FUN_OP_HPP
