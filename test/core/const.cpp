#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace constant {

using namespace ivl;
using namespace ivl::types;
namespace op = afun::op;
using ivl::seq;

//-----------------------------------------------------------------------------

namespace lit {

inline const char* hello() { return "hello"; }
inline const char* world() { return "world"; }

};

//-----------------------------------------------------------------------------

struct A { void operator()() { cout << "A "; } };
struct B : A { void operator()() { cout << "B "; } };
A aa;
B bb;

int a[6] = {4, 9, -2, 0, 1, 7};

struct C { array <int, 3> operator()(int n) { return seq(n, n+1, n+2); } };
struct D { int x; D(int x = 14) : x{x} {}};
struct E
{
	int i;
	E(int i = 8) : i(i) { }
	void f(int x)       { cout << "non-const-call "  << x << " " << i << endl; }
	void f(int x) const { cout << "const-call " << x << " " << i << endl; }
};

struct F
{
	int i;
	F(int i = 14) : i(i) { }
	void f(int x) &&      { cout << "rref-call "  << x << " " << i << endl; }
	void f(int x) &       { cout << "lref-call "  << x << " " << i << endl; }
	void f(int x) const&  { cout << "cref-call " << x << " " << i << endl; }
};

struct G { int x; G() : x(4) { } };

D dd{8};
E ee{};
F ff{};

// TODO: remove; const have internal linkage; "extern" required by gcc
extern const D cdd{9};
extern const E cee{};
extern const F cff{};

int f(int i) { return i + 3; }

array <int, 3> g(size_t n) { return seq(n, n+1, n+2); };

//-----------------------------------------------------------------------------

template <typename S>
S& operator<<(S& s, const D& d) { return s << d.x; }

template <typename T, size_t N>
void print_array(const T(&a)[N])
{
	cout << "[ ";
	for (size_t i =0; i < N; i++)
		cout << a[i] << " ";
	cout << "]" << endl;
}

//-----------------------------------------------------------------------------

void run()
{
	{
		cout << "floating:" << endl;
		cout << c_float <359, 1>{} << endl;
		cout << c_float <-359, 7>{} << endl;
		cout << c_float <359, -7>{} << endl;
		cout << endl;

		cout << "normalized floating:" << endl;
		cout << c_norm_double <359, 1>{} << endl;
		cout << c_norm_double <-359, 7>{} << endl;
		cout << c_norm_double <359, -7>{} << endl;
		cout << endl;

		cout << c_norm_float  <359, -50>{} << endl;
		cout << c_norm_double <359, -50>{} << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		cout << "int array:" << endl;
		using A = c_int_array <int, 5, 3, -2, 0, 1, 8, -6, 9>;
		print_array(A{}());
		cout << endl;

		cout << "bracket:" << endl;
		cout << c_bracket <A, c_int <0> >{} << " ";
		cout << c_bracket <A, c_int <1> >{} << " ";
		cout << c_bracket <A, c_int <2> >{} << " ";
		cout << c_bracket <A, c_int <3> >{} << " ";
		cout << c_bracket <A, c_int <4> >{} << " ";
		cout << c_bracket <A, c_int <5> >{} << " ";
		cout << c_bracket <A, c_int <6> >{} << " ";
		cout << c_bracket <A, c_int <7> >{} << " ";
		cout << endl;
		cout << endl;

		cout << "cons:" << endl;
		cout << c_cons <G>{}().x << endl;
		cout << c_cons <array <int, 2>(c_unsigned <12>, c_int <-4>)>{} << endl;
		cout << endl;

		cout << "cons_list:" << endl;
		cout << c_cons_list <D (c_int <7>)>{}().x << endl;
		cout << endl;

		cout << "array_list:" << endl;
		using L = c_array_list <D, pack <c_int <-4> >, pack <c_int <13> > >;
		print_array(L{}());
		cout << endl;

		cout << "string:" << endl;
		cout
			<< c_string <lit::hello>{} << ", "
			<< c_string <lit::world>{} << "!" << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		cout << "ref_member:" << endl;
		cout << c_ref_member <D(c_int <3>), int, &D::x>{} << endl;
		cout << c_ref_member <D,            int, &D::x>{} << endl;
		cout << c_ref_member <D,            int, &D::x, dd>{} << endl;
		cout << c_ref_member <D const,      int, &D::x, cdd>{} << endl;
		cout << endl;
	}

	{
		cout << "call:" << endl;
		cout << c_call <decltype(f)&(c_int <2>), f>{}() << endl;
		c_call <A()>{}();
		cout << endl;
		cout << c_call <C(c_int <2>)>{} << endl;

		using S = array <int, 3>(size_t);
		using R = c_lref <decltype(g), g>;
		cout << R{}(4) << endl;
		cout << c_call <R(c_int <6>)>{} << endl;
		cout << c_call <S&(c_int <8>), g>{} << endl;
		cout << endl;
	}

	{
		cout << "debug:" << endl;
		using S = void(int);
		using SC = void(E::*)(int) const;
		c_call <op::ref_call(E, c_member <E,       S, &E::f>, c_int <8>)>{}();
		c_call <op::ref_call(E, c_member <E const, S, &E::f>, c_int <9>)>{}();
		op::ref_call{}(E{}, c_member <E, S, &E::f>{}(), 8);
		op::ref_call{}(E{}, SC(&E::f), 9);
		cout << endl;
	}

	{
		using S = void(int);
		cout << "member call:" << endl;
		c_ref_call <E(c_int <6>), S&(c_int <1>), &E::f>{}();
		c_ref_call <E,            S&(c_int <1>), &E::f>{}();
		c_ref_call <E,            S&(c_int <6>), &E::f, ee>{}();
		c_ref_call <E const,      S&(c_int <4>), &E::f, cee>{}();
		cout << endl;

#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)
		cout << "member ref_call:" << endl;
		c_ref_call <F&&(c_int <2>), S&(c_int <3>), &F::f>{}();
		c_ref_call <F&&,            S&(c_int <3>), &F::f>{}();
		c_ref_call <F&,             S&(c_int <2>), &F::f, ff>{}();
		c_ref_call <F const&,       S&(c_int <5>), &F::f, cff>{}();
		cout << endl;
#endif
	}

//-----------------------------------------------------------------------------

	{
		cout << "op:" << endl;
		cout << c_add <c_int <3>, c_norm_double <314> >{} << endl;
		cout << endl;

		cout << "fun:" << endl;
		cout << "min(size_t) = " << c_min <size_t>{} << endl;
		cout << "min(int) = " << c_min <int>{} << endl;
		cout << "inf = " << c_inf <>{} << endl;
		cout << "-inf = " << c_minus <c_inf <> >{} << endl;
		cout << "nan = " << c_nan <>{} << endl;
		using E = c_gen <1, double(c_one), std::exp>;
		using P = c_mul <c_gen <1, double(c_one), std::atan>, c_int <4> >;
		cout << "e = " << E{} << endl;
		cout << "e = " << c_e <>{} << endl;
		cout << "pi = " << P{} << endl;
		cout << "pi = " << c_pi <>{} << endl;
		cout << "i = " << c_i <>{} << endl;
		cout << "j = " << c_j <>{} << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		cout << "sizeof : " << c_sizeof <array <double, 4> >{} << endl;
		cout << "sizeof : " << c_sizeof <tuple <int, double> >{} << endl;

		cout << "static_cast : ";
		aa(); bb();
		c_static_cast <A, c_lref <B, bb> >{}()();
		cout << endl;
		cout << endl;
	}

}

//-----------------------------------------------------------------------------

}  // namespace constant

//-----------------------------------------------------------------------------

int main()
{
	constant::run();
}
