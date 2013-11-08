#include <ivl/ivl>

//-----------------------------------------------------------------------------

struct A { };
struct B { operator A() const { return A(); } };
union  C final { int x; };
struct D { virtual void f() = 0; };
struct E { virtual void f() { } };
struct F { typedef A base_type; };
struct G : public A { typedef int type; };
enum H { a };
struct I;
struct J { int x; };
struct K { float f(int x) { return sqrt(x); } };
struct L { L (int,int) {}; };
struct M { A a; };

//-----------------------------------------------------------------------------

template <typename A, typename B>
struct tup { };

struct func
{
	template <typename A, typename B>
	tup <A, B> operator()(A, B);
};

//-----------------------------------------------------------------------------

namespace trait {

using namespace ivl;
using namespace ivl::types;
using types::base_opt;

//-----------------------------------------------------------------------------

void run()
{
	report_pred <is_const, int>();
	report_pred <is_const, const int>();
	report_pred <is_const, int const>();
	report_pred <is_const, int const&>();
	report_pred <is_const, int const*>();
	report_pred <is_const, int const[]>();

	report_pred <is_rref, int>();
	report_pred <is_rref, int&>();
	report_pred <is_rref, const int&>();
	report_pred <is_rref, int&&>();
	report_pred <is_rref, const int&&>();
	report_pred <is_rref, int*>();
	report_pred <is_rref, int*&>();
	report_pred <is_rref, int*&&>();

	report_pred <is_lref, int>();
	report_pred <is_lref, int&>();
	report_pred <is_lref, const int&>();
	report_pred <is_lref, int&&>();
	report_pred <is_lref, const int&&>();
	report_pred <is_lref, int*>();
	report_pred <is_lref, int*&>();
	report_pred <is_lref, int*&&>();

//-----------------------------------------------------------------------------

	report_map <add_lref, int>();
	report_map <add_lref, int&>();
	report_map <add_lref, void>();
	report_map <add_lref, const void>();
	report_map <add_lref, volatile void>();
	report_map <add_lref, const volatile void>();

	report_map <remove_ptr, int>();
	report_map <remove_ptr, int*>();
	report_map <remove_ptr, int&>();
	report_map <remove_ptr, int&&>();
	report_map <remove_ptr, const int*>();
	report_map <remove_ptr, const int&>();
	report_map <remove_ptr, const int&&>();
	report_map <remove_ptr, int* const>();
	report_map <remove_ptr, int const*>();
	report_map <remove_ptr, int const&>();
	report_map <remove_ptr, int const&&>();

	report_map <add_lref, int>();
	report_map <add_lref, int&>();
	report_map <add_lref, int&&>();
	report_map <add_lref, int*>();
	report_map <add_lref, int* const>();
	report_map <add_lref, int[]>();
	report_map <add_lref, const int>();
	report_map <add_lref, const int&>();
	report_map <add_lref, const int&&>();
	report_map <add_lref, const int*>();
	report_map <add_lref, const int* const>();
	report_map <add_lref, const int[]>();

	report_map <add_rref, int>();
	report_map <add_rref, int&>();
	report_map <add_rref, int&&>();
	report_map <add_rref, int*>();
	report_map <add_rref, int* const>();
	report_map <add_rref, int[]>();
	report_map <add_rref, const int>();
	report_map <add_rref, const int&>();
	report_map <add_rref, const int&&>();
	report_map <add_rref, const int*>();
	report_map <add_rref, const int* const>();
	report_map <add_rref, const int[]>();

	report_map <add_const, int&>();
	report_map <add_const, void (int)>();
	report_map <add_const, const int>();

//-----------------------------------------------------------------------------

	report_map <keep, int>();
	report_map <keep, int&>();
	report_map <keep, int&&>();
	report_map <keep, int*>();
	report_map <keep, int* const>();
	report_map <keep, int[]>();
	report_map <keep, const int>();
	report_map <keep, const int&>();
	report_map <keep, const int&&>();
	report_map <keep, const int*>();
	report_map <keep, const int* const>();
	report_map <keep, const int[]>();

	report_map <check_t, int>();
	report_map <check_t, nat>();
	report_map <check_t, tup <int, double> >();

//-----------------------------------------------------------------------------

	report_pred <is_fun, int>();
	report_pred <is_fun, void (int)>();
	report_pred <is_fun, void (*)(int)>();
	report_pred <is_fun, void>();

	report_pred <is_fun, int J::*>();
	report_pred <is_fun, float (K::*)(int)>();
	report_pred <is_prop_ptr, int J::*>();
	report_pred <is_prop_ptr, float (K::*)(int)>();
	report_pred <is_method_ptr, int J::*>();
	report_pred <is_method_ptr, float (K::*)(int)>();

	report_map <member_class, int J::*>();
	report_map <member_class, float (K::*)(int)>();
	report_map <member_ret, int J::*>();
	report_map <member_ret, float (K::*)(int)>();
	report_map <member_arg, float (K::*)(int)>();

	report_map <ret,    func (int, double)>();
	report_map <result, func (int, double)>();
	report_map <ret,    func, int, double>();
	report_map <result, func, int, double>();

//-----------------------------------------------------------------------------

	report_pred <is_signed, int>();
	report_pred <is_signed, size_t>();
	report_pred <is_signed, double>();
	report_pred <is_signed, void>();
	report_pred <is_signed, A>();
	report_pred <is_signed, func>();

	report_pred <is_enum, A>();
	report_pred <is_enum, H>();
	report_pred <is_enum, int>();

	report_pred <is_union, A>();
	report_pred <is_union, B>();
	report_pred <is_union, C>();
	report_pred <is_union, D>();
	report_pred <is_union, int>();

	report_pred <is_class, A>();
	report_pred <is_class, B>();
	report_pred <is_class, C>();
	report_pred <is_class, D>();
	report_pred <is_class, int>();

	report_pred <is_empty, A>();
	report_pred <is_empty, C>();
	report_pred <is_empty, D>();
	report_pred <is_empty, int>();

	report_pred <is_abstract, A>();
	report_pred <is_abstract, D>();
	report_pred <is_abstract, E>();
	report_pred <is_abstract, G>();

	report_pred <is_polymorphic, A>();
	report_pred <is_polymorphic, D>();
	report_pred <is_polymorphic, E>();
	report_pred <is_polymorphic, G>();

	report_pred <is_complete, A>();
	report_pred <is_complete, D>();
	report_pred <is_complete, E>();
	report_pred <is_complete, I>();
	report_pred <is_complete, int>();

	report_pred <is_final, A>();
	report_pred <is_final, B>();
	report_pred <is_final, C>();
	report_pred <is_final, int>();

//-----------------------------------------------------------------------------

	report_pred <is_void, L>();
	report_pred <is_arithmetic, L>();
	report_pred <is_enum, L>();
	report_pred <is_ref, L>();
	report_pred <is_union, L>();
	report_pred <is_class, L>();
	report_pred <is_fun, L>();
	report_pred <is_arr, L>();
	report_pred <is_ptr, L>();
	report_pred <is_nullptr, L>();
	report_pred <is_member_ptr, L>();

//-----------------------------------------------------------------------------

	report_pred <is_base_eq, A, B>();
	report_pred <is_base_eq, A, C>();
	report_pred <is_base_eq, A, G>();
	report_pred <is_base_eq, A, A>();

	report_pred <is_base, A, B>();
	report_pred <is_base, A, C>();
	report_pred <is_base, A, G>();
	report_pred <is_base, A, A>();

	report_pred <is_conv, B, A>();
	report_pred <is_conv, C, A>();
	report_pred <is_conv, G, A>();

	report_pred <has_base_type, A>();
	report_pred <has_base_type, F>();
	report_pred <has_type, G>();

	report_pred <is_cons, int>();
	report_pred <is_cons, int, float>();
	report_pred <is_cons, int, float, float>();
	report_pred <is_cons, L>();
	report_pred <is_cons, L, int>();
	report_pred <is_cons, L, int, int>();
	report_pred <is_cons, L, int, int, int>();

//-----------------------------------------------------------------------------

	{
		typedef pack <double&, int&&> C;
		typedef tuple <double&, int> T;
		report_map <tup_types, C>();
		report_map <tup_types, T>();
		report_pred <tup_cons, C, T>();
		report_pred <tup_assign, C, T>();
		report_pred <tup_conv, T, C>();
	}

//-----------------------------------------------------------------------------

	{
		typedef tuple <int, double&, const char, volatile long&, int&&> T;
		report_map <tup_types, T>();
		report_map <tup_types, const T>();
		report_map <tup_types, volatile T>();
		report_map <tup_types, const volatile T>();
		report_map <tup_types, T&>();
		report_map <tup_types, const T&>();
		report_map <tup_types, T&&>();
		report_map <tup_types, const volatile T&&>();
	}

//-----------------------------------------------------------------------------

	{
		typedef pack <int, char, double, A, B, C, D, E, F> T;
		report_map <choose_p, sz_range <1, 4>, T>();
		report_map <choose_p, sz_range <2, 7, 2>, T>();
		report_map <choose_p, sz_range <6, 1, -1>, T>();
	}

//-----------------------------------------------------------------------------

	{
		typedef pack <A, B, C> T;
		typedef pack <int, char, double> S;
		report_map <tran, T, S>();
	}

//-----------------------------------------------------------------------------

	{
		typedef pack <int, char, float> T;
		typedef pack <A, B> U;
		typedef pack <C, D, E> V;
		typedef pack <F> W;
		typedef pack <> X;
		typedef pack <G, I> Y;
		report_map <major, T, U, V, W, X, Y>();
		report_map <minor, T, U, V, W, X, Y>();
	}

//-----------------------------------------------------------------------------

	{
		report_map <base_opt, A>();
		report_map <base_opt, B>();
		report_map <base_opt, C>();
		report_map <base_opt, D>();
		report_map <base_opt, G>();
		report_map <base_opt, M>();
		report_map <base_opt, int>();
		report_map <base_opt, int&>();
		report_map <base_opt, int*>();
	}

}

//-----------------------------------------------------------------------------

}  // namespace trait

//-----------------------------------------------------------------------------

struct I { };

//-----------------------------------------------------------------------------

int main()
{
	trait::run();
}
