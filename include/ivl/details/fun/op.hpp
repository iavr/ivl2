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

#ifndef IVL_DETAILS_FUN_OP_HPP
#define IVL_DETAILS_FUN_OP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace op {

using types::enable_if;
using types::is_tuple;
using types::any_tuple;

}  // namespace op

//-----------------------------------------------------------------------------

#define IVL_VEC_OP(NAME)                                 \
                                                         \
namespace fun {                                          \
namespace op {                                           \
	using NAME = afun::vec_apply <afun::op::NAME>;        \
}                                                        \
}                                                        \
                                                         \
namespace op {                                           \
	static __attribute__ ((unused)) fun::op::NAME NAME;   \
}                                                        \

//-----------------------------------------------------------------------------

#define IVL_VEC_OP1(NAME, OP)          \
                                       \
IVL_VEC_OP(NAME)                       \
                                       \
namespace op {                         \
                                       \
template <typename A>                  \
INLINE constexpr auto                  \
operator OP (A&& a)                    \
	-> decltype(op::NAME(fwd <A>(a)))   \
	{ return op::NAME(fwd <A>(a)); }    \
                                       \
}                                      \
                                       \
using op::operator OP;                 \

//-----------------------------------------------------------------------------

// #define IVL_OP1_PRE(NAME, OP)            \
//                                          \
// struct NAME                              \
// {                                        \
// 	template <typename A>                 \
// 	INLINE auto                           \
// 	operator()(A&& a) const               \
// 		-> decltype(OP fwd <A>(a))         \
// 		{ return OP fwd <A>(a); }          \
// };

//-----------------------------------------------------------------------------

// #define IVL_OP1_POST(NAME, OP)           \
//                                          \
// struct NAME                              \
// {                                        \
// 	template <typename A>                 \
// 	INLINE auto                           \
// 	operator()(A&& a) const               \
// 		-> decltype(fwd <A>(a) OP)         \
// 		{ return fwd <A>(a) OP; }          \
// };

//-----------------------------------------------------------------------------

#define IVL_VEC_OP2(NAME, OP)                      \
                                                   \
IVL_VEC_OP(NAME)                                   \
                                                   \
namespace op {                                     \
                                                   \
template <typename A, typename B>                  \
INLINE constexpr auto                              \
operator OP (A&& a, B&& b)                         \
	-> decltype(op::NAME(fwd <A>(a), fwd <B>(b)))   \
	{ return op::NAME(fwd <A>(a), fwd <B>(b)); }    \
                                                   \
}                                                  \
                                                   \
using op::operator OP;                             \

//-----------------------------------------------------------------------------

// #define IVL_OP2_MUT(NAME, OP)                        \
//                                                      \
// struct NAME                                          \
// {                                                    \
// 	template <typename A, typename B>                 \
// 	INLINE auto                                       \
// 	operator()(A&& a, B&& b) const                    \
// 		-> decltype(fwd <A>(a) OP fwd <B>(b))          \
// 		{ return fwd <A>(a) OP fwd <B>(b); }           \
// };

//-----------------------------------------------------------------------------

// #define IVL_OP_CAST(NAME)                                     \
//                                                               \
// struct _##NAME##_cast                                         \
// {                                                             \
// 	template <typename T, typename A>                          \
// 	INLINE constexpr T                                         \
// 	_(A&& a) const { return NAME##_cast <T>(fwd <A>(a)); }     \
// };

//-----------------------------------------------------------------------------

IVL_VEC_OP1(plus,  +)
IVL_VEC_OP1(minus, -)

// IVL_VEC_OP1_PRE(inc_, ++)
// IVL_VEC_OP1_PRE(dec_, --)
// IVL_VEC_OP1_POST(_inc, ++)
// IVL_VEC_OP1_POST(_dec, --)

IVL_VEC_OP2(add, +)
IVL_VEC_OP2(sub, -)
IVL_VEC_OP2(mul, *)
IVL_VEC_OP2(div, /)
IVL_VEC_OP2(mod, %)

IVL_VEC_OP2(eq,  ==)
IVL_VEC_OP2(neq, !=)
IVL_VEC_OP2(gt,  >)
IVL_VEC_OP2(lt,  <)
IVL_VEC_OP2(ge,  >=)
IVL_VEC_OP2(le,  <=)

IVL_VEC_OP1(_not, !)
IVL_VEC_OP2(_and, &&)
IVL_VEC_OP2(_or,  ||)

IVL_VEC_OP1(bit_not, ~)
IVL_VEC_OP2(bit_and, &)
IVL_VEC_OP2(bit_or,  |)
IVL_VEC_OP2(bit_xor, ^)
// IVL_VEC_OP2_MUT(left,  <<)
// IVL_VEC_OP2_MUT(right, >>)

// IVL_VEC_OP2_MUT(assign, =)
// IVL_VEC_OP2_MUT(add_as, +=)
// IVL_VEC_OP2_MUT(sub_as, -=)
// IVL_VEC_OP2_MUT(mul_as, *=)
// IVL_VEC_OP2_MUT(div_as, /=)
// IVL_VEC_OP2_MUT(mod_as, %=)

// IVL_VEC_OP2_MUT(and_as,   &=)
// IVL_VEC_OP2_MUT(or_as,    |=)
// IVL_VEC_OP2_MUT(xor_as,   ^=)
// IVL_VEC_OP2_MUT(left_as,  <<=)
// IVL_VEC_OP2_MUT(right_as, >>=)

// IVL_VEC_OP1_PRE(deref, *)
// IVL_VEC_OP1_PRE(addr,  &)

// //-----------------------------------------------------------------------------
//
// struct ref_member
// {
// 	template <typename C, typename R>
// 	INLINE constexpr auto operator()(C&& c, R raw_type <C>::*m) const
// 		-> decltype(fwd <C>(c) .* m)
// 		{ return fwd <C>(c) .* m; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct ptr_member
// {
// 	template <typename C, typename R>
// 	INLINE auto operator()(C&& c, R bare_type <C>::*m) const
// 		-> decltype(fwd <C>(c) ->* m)
// 		{ return fwd <C>(c) ->* m; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct ref_call
// {
// 	template <typename C, typename R, typename... A>
// 	INLINE constexpr auto operator()(C&& c, R raw_type <C>::*m, A&&... a) const
// 		-> decltype( ( fwd <C>(c) .* m ) ( fwd <A>(a)... ) )
// 		{ return ( fwd <C>(c) .* m ) ( fwd <A>(a)... ) ; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct ptr_call
// {
// 	template <typename C, typename R, typename... A>
// 	INLINE auto operator()(C&& c, R bare_type <C>::*m, A&&... a) const
// 		-> decltype( ( fwd <C>(c) ->* m ) ( fwd <A>(a)... ) )
// 		{ return ( fwd <C>(c) ->* m ) ( fwd <A>(a)... ) ; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct call
// {
// 	template <typename F, typename... A>
// 	INLINE constexpr auto operator()(F&& f, A&&... a) const
// 		-> decltype(fwd <F>(f) ( fwd <A>(a)... ) )
// 		{ return fwd <F>(f) ( fwd <A>(a)... ) ; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct bracket
// {
// 	template <typename A, typename B>
// 	INLINE constexpr auto operator()(A&& a, B&& b) const
// 		-> decltype(fwd <A>(a) [ fwd <B>(b) ] )
// 		{ return fwd <A>(a) [ fwd <B>(b) ] ; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct comma
// {
// 	template <typename A, typename B>
// 	INLINE constexpr auto operator()(A&& a, B&& b) const
// 		-> decltype(fwd <A>(a) , fwd <B>(b))
// 		{ return fwd <A>(a) , fwd <B>(b); }
// };
//
// //-----------------------------------------------------------------------------
//
// struct cond
// {
// 	template <typename A, typename B, typename C>
// 	INLINE constexpr auto operator()(A&& a, B&& b, C&& c) const
// 		-> decltype(fwd <A>(a) ? fwd <B>(b) : fwd <C>(c))
// 		{ return fwd <A>(a) ? fwd <B>(b) : fwd <C>(c); }
// };
//
// //-----------------------------------------------------------------------------
//
// struct _sizeof
// {
// 	template <typename T>
// 	INLINE constexpr size_t _() const { return sizeof(T); }
//
// 	template <typename T>
// 	INLINE constexpr size_t operator()(T&& v) const
// 		{ return sizeof(fwd <T>(v)); }
// };
//
// struct _alignof
// {
// 	template <typename T>
// 	INLINE constexpr size_t _() const { return alignof(T); }
// };
//
// //-----------------------------------------------------------------------------
//
// struct conv
// {
// 	template <typename T, typename A>
// 	INLINE constexpr T _(A&& a) const{ return (T) fwd <A>(a); }
// };
//
// //-----------------------------------------------------------------------------
//
// IVL_VEC_OP_CAST(static)
// IVL_VEC_OP_CAST(dynamic)
// IVL_VEC_OP_CAST(const)
// IVL_VEC_OP_CAST(reinterpret)
//
// //-----------------------------------------------------------------------------
//
// struct _new
// {
// 	template <typename C>
// 	INLINE auto _() const
// 		-> decltype(new C)
// 		{ return new C; }
//
// 	template <typename C>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new C[n0])
// 		{ return new C[n0]; }
//
// 	template <typename C, size_t n1>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new C[n0][n1])
// 		{ return new C[n0][n1]; }
//
// 	template <typename C, size_t n1, size_t n2>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new C[n0][n1][n2])
// 		{ return new C[n0][n1][n2]; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct new_nothrow
// {
// 	template <typename C>
// 	INLINE auto _() const
// 		-> decltype(new (std::nothrow) C)
// 		{ return new (std::nothrow) C; }
//
// 	template <typename C>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new (std::nothrow) C[n0])
// 		{ return new (std::nothrow) C[n0]; }
//
// 	template <typename C, size_t n1>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new (std::nothrow) C[n0][n1])
// 		{ return new (std::nothrow) C[n0][n1]; }
//
// 	template <typename C, size_t n1, size_t n2>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new (std::nothrow) C[n0][n1][n2])
// 		{ return new (std::nothrow) C[n0][n1][n2]; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct place
// {
// 	template <typename C>
// 	INLINE void operator()(C&& c) const
// 		{ new (fwd <C>(c)) bare_type <C>; }
//
// 	template <typename C>
// 	INLINE void operator()(C&& c, size_t n0) const
// 		{ new (fwd <C>(c)) bare_type <C>[n0]; }
//
// 	template <size_t n1, typename C>
// 	INLINE void _(C&& c, size_t n0) const
// 		{ new (fwd <C>(c)) bare_type <C>[n0][n1]; }
//
// 	template <size_t n1, size_t n2, typename C>
// 	INLINE void _(C&& c, size_t n0) const
// 		{ new (fwd <C>(c)) bare_type <C>[n0][n1][n2]; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct new_val
// {
// 	template <typename C>
// 	INLINE auto _() const
// 		-> decltype(new C())
// 		{ return new C(); }
//
// 	template <typename C>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new C[n0]())
// 		{ return new C[n0](); }
//
// 	template <typename C, size_t n1>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new C[n0][n1]())
// 		{ return new C[n0][n1](); }
//
// 	template <typename C, size_t n1, size_t n2>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new C[n0][n1][n2]())
// 		{ return new C[n0][n1][n2](); }
// };
//
// //-----------------------------------------------------------------------------
//
// struct new_nothrow_val
// {
// 	template <typename C>
// 	INLINE auto _() const
// 		-> decltype(new (std::nothrow) C())
// 		{ return new (std::nothrow) C(); }
//
// 	template <typename C>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new (std::nothrow) C[n0]())
// 		{ return new (std::nothrow) C[n0](); }
//
// 	template <typename C, size_t n1>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new (std::nothrow) C[n0][n1]())
// 		{ return new (std::nothrow) C[n0][n1](); }
//
// 	template <typename C, size_t n1, size_t n2>
// 	INLINE auto _(size_t n0) const
// 		-> decltype(new (std::nothrow) C[n0][n1][n2]())
// 		{ return new (std::nothrow) C[n0][n1][n2](); }
// };
//
// //-----------------------------------------------------------------------------
//
// struct place_val
// {
// 	template <typename C>
// 	INLINE void operator()(C&& c) const
// 		{ new (fwd <C>(c)) bare_type <C>(); }
//
// 	template <typename C>
// 	INLINE void operator()(C&& c, size_t n0) const
// 		{ new (fwd <C>(c)) bare_type <C>[n0](); }
//
// 	template <size_t n1, typename C>
// 	INLINE void _(C&& c, size_t n0) const
// 		{ new (fwd <C>(c)) bare_type <C>[n0][n1](); }
//
// 	template <size_t n1, size_t n2, typename C>
// 	INLINE void _(C&& c, size_t n0) const
// 		{ new (fwd <C>(c)) bare_type <C>[n0][n1][n2](); }
// };
//
// //-----------------------------------------------------------------------------
//
// struct new_direct
// {
// 	template <typename C, typename... A>
// 	INLINE auto _(A&&... a) const
// 		-> decltype(new C ( fwd <A>(a)... ) )
// 		{ return new C ( fwd <A>(a)... ) ; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct new_nothrow_direct
// {
// 	template <typename C, typename... A>
// 	INLINE auto _(A&&... a) const
// 		-> decltype(new (std::nothrow) C ( fwd <A>(a)... ) )
// 		{ return new (std::nothrow) C ( fwd <A>(a)... ) ; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct place_direct
// {
// 	template <typename C, typename... A>
// 	INLINE void operator()(C&& c, A&&... a) const
// 		{ new (fwd <C>(c)) bare_type <C> ( fwd <A>(a)... ) ; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct new_list
// {
// 	template <typename C, typename... A>
// 	INLINE auto _(A&&... a) const
// 		-> decltype(new C { fwd <A>(a)... } )
// 		{ return new C { fwd <A>(a)... } ; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct new_nothrow_list
// {
// 	template <typename C, typename... A>
// 	INLINE auto _(A&&... a) const
// 		-> decltype(new (std::nothrow) C { fwd <A>(a)... } )
// 		{ return new (std::nothrow) C { fwd <A>(a)... } ; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct place_list
// {
// 	template <typename C, typename... A>
// 	INLINE void operator()(C&& c, A&&... a) const
// 		{ new (fwd <C>(c)) bare_type <C> { fwd <A>(a)... } ; }
// };
//
// //-----------------------------------------------------------------------------
//
// struct _delete
// {
// 	template <typename C>
// 	INLINE void operator()(C&& c) const { delete fwd <C>(c); }
// };
//
// //-----------------------------------------------------------------------------
//
// struct delete_array
// {
// 	template <typename C>
// 	INLINE void operator()(C&& c) const { delete [] fwd <C>(c); }
// };

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_AFUN_OP_HPP
