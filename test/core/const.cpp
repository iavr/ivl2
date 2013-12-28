#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace constant {

using namespace ivl;
using namespace ivl::types;
namespace op = afun::op;

//-----------------------------------------------------------------------------

namespace lit {

inline const char* hello() { return "hello"; }
inline const char* world() { return "world"; }

};

//-----------------------------------------------------------------------------

struct A { void operator()() { cout << "A "; } };
struct B : public A { void operator()() { cout << "B "; } };
A aa;
B bb;

int a[6] = {4, 9, -2, 0, 1, 7};

struct C { array <int> operator()(size_t n) { return array <int>(n, 2); } };
struct D { int x; };
struct E
{
	void f(int x)       { cout << "call "  << x << endl; }
	void f(int x) const { cout << "ccall " << x << endl; }
};

struct F
{
	void f(int x) &       { cout << "lcall "  << x << endl; }
	void f(int x) &&      { cout << "rcall "  << x << endl; }
	void f(int x) const&  { cout << "clcall " << x << endl; }
	void f(int x) const&& { cout << "crcall " << x << endl; }
};

struct G { int x; G() : x(4) { } };

D dd{8};
E ee{};
F ff{};

// "extern" required by gcc (only for const ?)
extern const D cdd{9};
extern const E cee{};
extern const F cff{};

array <int> f(size_t n) { return array <int>(n, 2); };

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
		cout << c_float <359, 1>() << endl;
		cout << c_float <-359, 7>() << endl;
		cout << c_float <359, -7>() << endl;
		cout << endl;

		cout << c_norm_double <359, 1>() << endl;
		cout << c_norm_double <-359, 7>() << endl;
		cout << c_norm_double <359, -7>() << endl;
		cout << endl;

		cout << c_norm_float  <359, -50>() << endl;
		cout << c_norm_double <359, -50>() << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		cout << "int array:" << endl;
		typedef c_int_array <int, 5, 3, -2, 0, 1, 8, -6, 9> A;
		print_array(A()());
		cout << endl;

		cout << "bracket:" << endl;
		cout << c_bracket <A, c_int <0> >() << " ";
		cout << c_bracket <A, c_int <1> >() << " ";
		cout << c_bracket <A, c_int <2> >() << " ";
		cout << c_bracket <A, c_int <3> >() << " ";
		cout << c_bracket <A, c_int <4> >() << " ";
		cout << c_bracket <A, c_int <5> >() << " ";
		cout << c_bracket <A, c_int <6> >() << " ";
		cout << c_bracket <A, c_int <7> >() << " ";
		cout << endl;
		cout << endl;

		cout << "cons:" << endl;
		cout << c_cons <G>()().x << endl;
		cout << c_cons <array <int>(c_unsigned <12>, c_int <-4>)>() << endl;
		// TODO: array bug: array <int>() also not working
// 		cout << c_cons <array <int> >() << endl;
		cout << endl;

		cout << "cons_list:" << endl;
		cout << c_cons_list <D (c_int <7>)>()().x << endl;
		cout << endl;

		cout << "array_list:" << endl;
		using L = c_array_list <D, pack <c_int <-4> >, pack <c_int <13> > >;
		print_array(L()());
		cout << endl;

		cout << "string:" << endl;
		cout
			<< c_string <lit::hello>() << ", "
			<< c_string <lit::world>() << "!" << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		cout << "ref_member:" << endl;
		cout << c_ref_member  <int, D, dd,  &D::x>() << endl;
		cout << c_cref_member <int, D, cdd, &D::x>() << endl;
		cout << endl;

		cout << "ptr_member:" << endl;
		cout << c_ptr_member  <int, D, &dd,  &D::x>() << endl;
		cout << c_cptr_member <int, D, &cdd, &D::x>() << endl;
		cout << endl;
	}

	{
		cout << "call:" << endl;
		c_call <c_cons <A>()>()();
		cout << endl;

		cout << c_call <c_cons <C>(c_int <2>)>() << endl;
		cout << endl;

		cout << "sig:" << endl;
		typedef c_sig <array <int> (size_t)> S;
		typedef S::function <f> F;
		cout << F()(4) << endl;
		cout << c_call <F(c_int <6>)>() << endl;
		cout << S::call <f, c_int <8> >() << endl;
		cout << endl;
	}

	{
		cout << "debug:" << endl;
		typedef void S(int);
		typedef void (E::*SC)(int) const;
		c_fun_call <op::ptr_call (c_cons <E>, c_sig <S>::method <E, &E::f>, c_int <8>)>()();
		c_fun_call <op::ptr_call (c_cons <E>, c_sig <S>::cmethod <E, &E::f>, c_int <8>)>()();
		SC s = c_sig <S>::cmethod <E, &E::f>()();
		op::ptr_call()(E(), s, 8);
		op::ptr_call()(E(), (SC)&E::f, 8);
		cout << endl;
	}

	{
		typedef void S(int);
		cout << "fun_call:" << endl;
		c_sig <S>::fun_call <E, &E::f, c_int <1> >()();
		c_sig <S>::cfun_call <E, &E::f, c_int <4> >()();
#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)
		c_sig <S>::rfun_call <F, &F::f, c_int <3> >()();
		c_sig <S>::crfun_call <F, &F::f, c_int <6> >()();
#endif
		cout << endl;

		cout << "ref_call:" << endl;
		c_sig <S>::ref_call <E, ee, &E::f, c_int <1> >()();
		c_sig <S>::cref_call <E, cee, &E::f, c_int <4> >()();
#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)
		c_sig <S>::lref_call <F, ff, &F::f, c_int <2> >()();
		c_sig <S>::clref_call <F, cff, &F::f, c_int <5> >()();
#endif
		cout << endl;

		cout << "ptr_call:" << endl;
		c_sig <S>::ptr_call <E, &ee, &E::f, c_int <1> >()();
		c_sig <S>::cptr_call <E, &cee, &E::f, c_int <4> >()();
#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)
		c_sig <S>::lptr_call <F, &ff, &F::f, c_int <2> >()();
		c_sig <S>::clptr_call <F, &cff, &F::f, c_int <5> >()();
#endif
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		cout << "op:" << endl;
		cout << c_add <c_int <3>, c_norm_double <314> >() << endl;
		cout << endl;

		cout << "fun:" << endl;
		cout << "inf = " << c_inf <>() << endl;
		cout << "-inf = " << c_minus <c_inf <> >() << endl;
		cout << "nan = " << c_nan <>() << endl;
		cout << "e = " << c_e <>() << endl;
		cout << "pi = " << c_pi <>() << endl;
		cout << "i = " << c_i <>() << endl;
		cout << "j = " << c_j <>() << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		cout << "sizeof : " << c_sizeof <array <double> >() << endl;

		cout << "static_cast : ";
		aa(); bb();
		c_static_cast <A, c_ref <B, bb> >()()();
		cout << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
	}

}

//-----------------------------------------------------------------------------

}  // namespace constant

//-----------------------------------------------------------------------------

int main()
{
	constant::run();
}
