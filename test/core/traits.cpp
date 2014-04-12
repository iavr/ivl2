#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {
namespace types {
namespace traits {
IVL_HAS_MEMBER(x)
IVL_HAS_MEMBER(a)
IVL_HAS_MEMBER(f)
} } }

//-----------------------------------------------------------------------------

namespace trait {

using namespace ivl;
using namespace ivl::types;

//-----------------------------------------------------------------------------

struct A { };
struct B { operator A() const { return A(); } };
union  C final { int x; };
struct D { virtual void f() = 0; };
struct E { virtual void f() { } };
struct F { using base_type = A; };
struct G : A, id_t <int> { };
enum H { a };
struct I;
struct J { int x; };
struct K { float f(int x) { return sqrt(x); } };
struct L { L(int,int) {} void operator=(int) {} };
struct M { A a; };
struct N { void f(); int f(int); };
struct O { int J::* a; };

//-----------------------------------------------------------------------------

double f(int);

template <typename... T> struct tup { };

struct func
{
	template <typename... T> tup <T...> operator()(T...);
	template <typename... T> tup <T...> _();
};

//-----------------------------------------------------------------------------

void run()
{

// 	report_pred <is_const, int>();
// 	report_pred <is_const, const int>();
// 	report_pred <is_const, int const>();
// 	report_pred <is_const, int const&>();
// 	report_pred <is_const, int const*>();
// 	report_pred <is_const, int const[]>();
//
// 	report_pred <is_rref, int>();
// 	report_pred <is_rref, int&>();
// 	report_pred <is_rref, const int&>();
// 	report_pred <is_rref, int&&>();
// 	report_pred <is_rref, const int&&>();
// 	report_pred <is_rref, int*>();
// 	report_pred <is_rref, int*&>();
// 	report_pred <is_rref, int*&&>();
//
// 	report_pred <is_lref, int>();
// 	report_pred <is_lref, int&>();
// 	report_pred <is_lref, const int&>();
// 	report_pred <is_lref, int&&>();
// 	report_pred <is_lref, const int&&>();
// 	report_pred <is_lref, int*>();
// 	report_pred <is_lref, int*&>();
// 	report_pred <is_lref, int*&&>();
//
// //-----------------------------------------------------------------------------
//
// 	report_map <add_lref, int>();
// 	report_map <add_lref, int&>();
// 	report_map <add_lref, void>();
// 	report_map <add_lref, const void>();
// 	report_map <add_lref, volatile void>();
// 	report_map <add_lref, const volatile void>();
//
// 	report_map <remove_ptr, int>();
// 	report_map <remove_ptr, int*>();
// 	report_map <remove_ptr, int&>();
// 	report_map <remove_ptr, int&&>();
// 	report_map <remove_ptr, const int*>();
// 	report_map <remove_ptr, const int&>();
// 	report_map <remove_ptr, const int&&>();
// 	report_map <remove_ptr, int* const>();
// 	report_map <remove_ptr, int const*>();
// 	report_map <remove_ptr, int const&>();
// 	report_map <remove_ptr, int const&&>();
//
// 	report_map <add_lref, int>();
// 	report_map <add_lref, int&>();
// 	report_map <add_lref, int&&>();
// 	report_map <add_lref, int*>();
// 	report_map <add_lref, int* const>();
// 	report_map <add_lref, int[]>();
// 	report_map <add_lref, const int>();
// 	report_map <add_lref, const int&>();
// 	report_map <add_lref, const int&&>();
// 	report_map <add_lref, const int*>();
// 	report_map <add_lref, const int* const>();
// 	report_map <add_lref, const int[]>();
//
// 	report_map <add_rref, int>();
// 	report_map <add_rref, int&>();
// 	report_map <add_rref, int&&>();
// 	report_map <add_rref, int*>();
// 	report_map <add_rref, int* const>();
// 	report_map <add_rref, int[]>();
// 	report_map <add_rref, const int>();
// 	report_map <add_rref, const int&>();
// 	report_map <add_rref, const int&&>();
// 	report_map <add_rref, const int*>();
// 	report_map <add_rref, const int* const>();
// 	report_map <add_rref, const int[]>();
//
// 	report_map <add_const, int&>();
// 	report_map <add_const, void (int)>();
// 	report_map <add_const, const int>();
//
// //-----------------------------------------------------------------------------
//
// 	report_map <check_t, int>();
// 	report_map <check_t, nat>();
// 	report_map <check_t, tup <int, double> >();
//
// //-----------------------------------------------------------------------------
//
// 	report_pred <is_fun, int>();
// 	report_pred <is_fun, void (int)>();
// 	report_pred <is_fun, void (*)(int)>();
// 	report_pred <is_fun, void>();
//
// 	report_pred <is_fun, int J::*>();
// 	report_pred <is_fun, float (K::*)(int)>();
// 	report_pred <is_prop_ptr, int J::*>();
// 	report_pred <is_prop_ptr, float (K::*)(int)>();
// 	report_pred <is_method_ptr, int J::*>();
// 	report_pred <is_method_ptr, float (K::*)(int)>();
//
// 	report_map <member_class, int J::*>();
// 	report_map <member_class, float (K::*)(int)>();
// 	report_map <member_type, int J::*>();
// 	report_map <member_type, int J::*>();
// 	report_map <member_type, float (K::*)(int) const>();
// 	report_map <member_fun, float (K::*)(int) const>();
// 	report_map <member_ret, float (K::*)(int) const>();
// 	report_map <member_arg, float (K::*)(int) const>();
//
// 	report_map <result, decltype(f)&, int>();
// 	report_map <result, decltype(f)&(int)>();
// 	report_map <result, func(int, double)>();
// 	report_map <result, func, int, double>();
// 	report_map <result, func, pack <char> >();
// 	report_map <result, func(pack <char>)>();
// 	report_map <ret,    func(int, double)>();
// 	report_map <ret,    func, int, double>();
// 	report_map <ret,    func, pack <char> >();
// 	report_map <ret,    func(pack <char>)>();
//
// 	report_map <result, decltype(&J::x)(J)>();
// 	report_map <result, decltype(&J::x)(J&)>();
// 	report_map <result, decltype(&J::x)(J*)>();
// 	report_pred <has__type, result_t <decltype(&J::x)(K)> >();
// 	report_map <result, decltype(&K::f)(K, int)>();
// 	report_map <result, decltype(&K::f)(K&, int)>();
// 	report_map <result, decltype(&K::f)(K*, int)>();
// 	report_pred <has__type, result_t <decltype(&K::f)(J, int)> >();
//
// //-----------------------------------------------------------------------------
//
// 	report_pred <is_signed, int>();
// 	report_pred <is_signed, size_t>();
// 	report_pred <is_signed, double>();
// 	report_pred <is_signed, void>();
// 	report_pred <is_signed, A>();
// 	report_pred <is_signed, func>();
//
// 	report_pred <is_enum, A>();
// 	report_pred <is_enum, H>();
// 	report_pred <is_enum, int>();
//
// 	report_pred <is_union, A>();
// 	report_pred <is_union, B>();
// 	report_pred <is_union, C>();
// 	report_pred <is_union, D>();
// 	report_pred <is_union, int>();
//
// 	report_pred <is_class, A>();
// 	report_pred <is_class, B>();
// 	report_pred <is_class, C>();
// 	report_pred <is_class, D>();
// 	report_pred <is_class, int>();
//
// 	report_pred <is_empty, A>();
// 	report_pred <is_empty, C>();
// 	report_pred <is_empty, D>();
// 	report_pred <is_empty, int>();
//
// 	report_pred <is_abstract, A>();
// 	report_pred <is_abstract, D>();
// 	report_pred <is_abstract, E>();
// 	report_pred <is_abstract, G>();
//
// 	report_pred <is_polymorphic, A>();
// 	report_pred <is_polymorphic, D>();
// 	report_pred <is_polymorphic, E>();
// 	report_pred <is_polymorphic, G>();
//
// 	report_pred <is_final, A>();
// 	report_pred <is_final, B>();
// 	report_pred <is_final, C>();
// 	report_pred <is_final, int>();
//
// //-----------------------------------------------------------------------------
//
// 	report_pred <is_void, L>();
// 	report_pred <is_arithmetic, L>();
// 	report_pred <is_enum, L>();
// 	report_pred <is_ref, L>();
// 	report_pred <is_union, L>();
// 	report_pred <is_class, L>();
// 	report_pred <is_fun, L>();
// 	report_pred <is_arr, L>();
// 	report_pred <is_ptr, L>();
// 	report_pred <is_nullptr, L>();
// 	report_pred <is_member_ptr, L>();
//
// //-----------------------------------------------------------------------------
//
// 	report_pred <is_base_eq, A, B>();
// 	report_pred <is_base_eq, A, C>();
// 	report_pred <is_base_eq, A, G>();
// 	report_pred <is_base_eq, A, A>();
//
// 	report_pred <is_base, A, B>();
// 	report_pred <is_base, A, C>();
// 	report_pred <is_base, A, G>();
// 	report_pred <is_base, A, A>();
//
// 	report_pred <is_conv, B, A>();
// 	report_pred <is_conv, C, A>();
// 	report_pred <is_conv, G, A>();
//
// 	report_pred <is_cons, int>();
// 	report_pred <is_cons, int, float>();
// 	report_pred <is_cons, int, float, float>();
// 	report_pred <is_cons, L>();
// 	report_pred <is_cons, L, int>();
// 	report_pred <is_cons, L, int, int>();
// 	report_pred <is_cons, L, int, int, int>();
//
// 	report_pred <is_assign, int, float>();
// 	report_pred <is_assign, int, L>();
// 	report_pred <is_assign, int&, float>();
// 	report_pred <is_assign, int&, L>();
// 	report_pred <is_assign, L, int>();
// 	report_pred <is_assign, L, L&&>();
// 	report_pred <is_assign, L, L&>();
// 	report_pred <is_assign, L, const L&>();
// 	report_pred <is_assign, L, A>();
// 	report_pred <is_assign, void, int>();
// 	report_pred <is_assign, int&, void>();
// 	report_pred <is_assign, void, void>();
//
// 	report_map <base_opt, A&&>();
// 	report_map <base_opt, B&&>();
// 	report_map <base_opt, C&&>();
// 	report_map <base_opt, D&>();
// 	report_map <base_opt, G&>();
// 	report_map <base_opt, M&>();
// 	report_map <base_opt, int>();
// 	report_map <base_opt, int&>();
// 	report_map <base_opt, int*>();
//
// //-----------------------------------------------------------------------------
//
// 	report_map <fun_ret, void (int)>();
// 	report_map <fun_arg, void (int)>();
// 	report_map <member_class, int I::*>();
// 	report_map <member_type, int I::*>();
// 	report_map <member_class, void (I::*)(int)>();
// 	report_map <member_type, void (I::*)(int)>();
// 	report_map <member_ret, void (I::*)(int)>();
// 	report_map <member_arg, void (I::*)(int)>();
//
// 	report_pred <is_complete, int>();
// 	report_pred <is_complete, void>();
// 	report_pred <is_complete, A>();
// 	report_pred <is_complete, I>();
// 	report_pred <is_complete, A(int)>();
// 	report_pred <is_complete, I(int)>();
// 	report_pred <is_complete, void(int)>();
// 	report_pred <is_complete, A(*)(int)>();
// 	report_pred <is_complete, I(*)(int)>();
// 	report_pred <is_complete, void(*)(int)>();
// 	report_pred <is_complete, int A::*>();
// 	report_pred <is_complete, int I::*>();
// 	report_pred <is_complete, void (A::*)(int)>();
// 	report_pred <is_complete, void (I::*)(int)>();
// 	report_pred <is_complete, void (A::*)(int) const>();
// 	report_pred <is_complete, void (I::*)(int) const>();
// 	report_pred <is_complete, void (A::*)(int) &&>();
// 	report_pred <is_complete, void (I::*)(int) &&>();
//
// //-----------------------------------------------------------------------------
//
// 	report_pred <has__base_type, A>();
// 	report_pred <has__base_type, F>();
// 	report_pred <has__type, G>();
// 	report_pred <has__type, H>();
//
// 	report_pred <has_member__a, A>();
// 	report_pred <has_member__a, M>();
// 	report_pred <has_member__x, A>();
// 	report_pred <has_member__x, J>();
//
// 	report_pred <has_member__begin, A>();
// // 	report_pred <has_member__begin, array <int> >();  // TODO: ARRAY
// 	report_pred <has_member__size, J>();
// // 	report_pred <has_member__size, array <int> >();  // TODO: ARRAY
//
// 	report_pred <has_unique__a, A>();
// 	report_pred <has_unique__a, M>();
// 	report_pred <has_unique__x, A>();
// 	report_pred <has_unique__x, J>();
//
// 	report_pred <has_member__f, K>();
// 	report_pred <has_unique__f, K>();
// 	report_pred <has_member__f, N>();
// 	report_pred <has_unique__f, N>();
//
// 	report_pred <has_member_ptr__f, K, void (K::*)()>();
// 	report_pred <has_member_ptr__f, K, float (K::*)(int)>();
// 	report_pred <has_member_ptr__f, K, float (K::*)(int)&&>();
// 	report_pred <has_member_ptr__f, N, void (N::*)()>();
// 	report_pred <has_member_ptr__f, N, void (N::*)(int)>();
// 	report_pred <has_member_ptr__f, N, int (N::*)(int)>();
//
// 	report_pred <has_member__f, K, void ()>();
// 	report_pred <has_member__f, K, float (int)>();
// 	report_pred <has_member__f, K&&, float (int)>();
// 	report_pred <has_member__f, N, void ()>();
// 	report_pred <has_member__f, N, void (int)>();
// 	report_pred <has_member__f, N, int (int)>();
//
// 	report_map <member_type__a, M>();
// 	report_map <member_type__x, J>();
// 	report_map <member_type__f, D>();
// 	report_map <member_type__f, K>();
//
// 	report_map <member_ptr, N, void (N::*)(int)>();
// 	report_map <member_ptr, N, void (int)>();
// 	report_map <member_ptr, N const, void (int)>();
// 	report_map <member_ptr, N const&&, void (int)>();
//
// //-----------------------------------------------------------------------------
//
// 	{
// 		using C = pack <double&, int&&>;
// 		using T = tuple <double&, int>;
// 		report_map <tup_type, C>();
// 		report_map <tup_type, T>();
// 		report_pred <tup_cons, C, T>();
// 		report_pred <tup_assign, C, T>();
// 		report_pred <tup_conv, T, C>();
// 	}
//
// //-----------------------------------------------------------------------------
//
// 	{
// 		using T = tuple <int, double&, const char, volatile long&, int&&>;
// 		report_map <tup_type, T>();
// 		report_map <tup_type, const T>();
// 		report_map <tup_type, volatile T>();
// 		report_map <tup_type, const volatile T>();
// 		report_map <tup_type, T&>();
// 		report_map <tup_type, const T&>();
// 		report_map <tup_type, T&&>();
// 		report_map <tup_type, const volatile T&&>();
// 	}
//
// //-----------------------------------------------------------------------------
//
// 	{
// 		using T = pack <int, char, double, A, B, C, D, E, F>;
// 		report_map <choose_p, sz_range <1, 4>, T>();
// 		report_map <choose_p, sz_range <2, 7, 2>, T>();
// 		report_map <choose_p, sz_range <6, 1, -1>, T>();
// 	}
//
// //-----------------------------------------------------------------------------
//
// 	{
// 		using T = pack <A, B, C>;
// 		using S = pack <int, char, double>;
// 		report_map <tran, T, S>();
// 	}
//
// //-----------------------------------------------------------------------------
//
// 	{
// 		using T = pack <int, char, float>;
// 		using U = pack <A, B>;
// 		using V = pack <C, D, E>;
// 		using W = pack <F>;
// 		using X = pack <>;
// 		using Y = pack <G, I>;
// 		report_map <major, T, U, V, W, X, Y>();
// 		report_map <minor, T, U, V, W, X, Y>();
// 	}

}

//-----------------------------------------------------------------------------

struct I { };

//-----------------------------------------------------------------------------

}  // namespace trait

//-----------------------------------------------------------------------------

int main()
{
	trait::run();
}
