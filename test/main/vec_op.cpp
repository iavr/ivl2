#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

IVL_KEY(p)
IVL_KEY(q)
IVL_KEY(f)
IVL_KEY(g)
IVL_KEY(h)

}

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;
namespace op = ivl::op;

using ivl::size;
using ivl::empty;

//-----------------------------------------------------------------------------

struct A
{
	int p;
	std::string q;
	int f(int x, char c) const { return x + c - 'a';}
	double g(double x, int i) const { return i / x; }
	void h() { p++; }
};

struct B
{
	array <int> p;
	double q;
	int f(int x, char c) const { return x;}
	double g(double x, int i) const { return 3 * x; }
	void h() { q *= 2; }
};

int pow(const A& a, int e) { return std::pow(a.p, e); }

//-----------------------------------------------------------------------------

void run()
{
	{
		cout << "op ++" << endl;
		auto t = val('a', 3.14, _(2, 5));
		cout << t++ << endl;
		cout << t << endl;
		cout << ++t << endl;
		cout << t << endl;
		cout << endl;
	}

	{
		cout << "op <" << endl;
		auto t = val(0, 1, 2, 3);
		cout << (1 < 2) << endl;
		cout << (2 < t) << endl;
		cout << (t < 2) << endl;
		cout << (t < t) << endl;
		cout << endl;
	}

	{
		cout << "op +=" << endl;
		int i = -1;
		auto t = _(5, 6, -7, 2);
		cout << (i += 1) << endl;
		cout << (i += t) << endl;
		cout << (t += i) << endl;
		cout << (t += t) << endl;
		cout << endl;
	}

	{
		cout << "op <<" << endl;
		auto t = val(0, 1, 2, 3);
		cout << (1 << 2) << endl;
		cout << (1 << t) << endl;
		cout << (t << 2) << endl;
		cout << (t << t) << endl;
		cout << endl;
	}

	{
		cout << "op *" << endl;
		int i = 0, j = 1, k = 2;
		int *p = &i, *q = &j, *r = &k;
		cout << *_(p, q, r) << endl;
		cout << endl;
	}

	{
		cout << "op []" << endl;
		int a[] = {7, 9, -2, 0};
		array <double> b[] = {{2, 3.14}, {}, {3, 7}};
		const char c[] = "hello";
		std::vector <string> d = { "hello", ",", "world" };
		auto t = _(a, b, c, d);
		cout << t[2] << endl;
		cout << t[_(2, 0 , 1, 0)] << endl;
		cout << endl;
	}

	{
		cout << "op ()" << endl;
		auto mid = [](double x, double y) { return (x + y) / 2; };
		auto f = _(op::add, _[mid], op::div);
		auto y = _(4, -2, 16.);
		cout << f(8, 4) << endl;
		cout << f(8, y) << endl;
		cout << f(8, _[y]) << endl;  // not in GCC
		cout << endl;
	}

	{
		cout << "op ->*" << endl;
		using A = array <int>;
		using V = std::vector <double>;
		A a(3);
		V v(5);
		auto t = _(a, v);
		auto m = _(size, empty);
		cout << _(a.size(), v.empty()) << endl;
		cout << t ->* m._() << endl;
		cout << (t ->* m)() << endl;  // not in GCC
		cout << _(_(a.size(), a.empty()), _(v.size(), v.empty())) << endl;
		cout << t ->* _[m]._() << endl;
		cout << (t ->* _[m])() << endl;  // not in GCC
		cout << endl;
	}

	{
		cout << "op ->* (custom, key)" << endl;
		A a{4, "hello"};
		B b{array <int>(3, 2), 3.14};
		auto t = _(a, b);
		auto m = _(p, q);
		auto F = _(f, g);
		cout << _(a.p, b.q) << endl;
		cout << t ->* m << endl;
		cout << _(_(a.p, b.p), _(a.q, b.q)) << endl;
		cout << _[t] ->* m << endl;
		cout << _(a.f(5, 'c'), b.g(5, 'd')) << endl;
		cout << t ->* F._(5, _('c', 'd')) << endl;
		cout << (t ->* F)(5, _('c', 'd')) << endl;  // not in GCC
		cout << _(_(a.f(5, 'c'), b.f(5, 'c')), _(a.g(5, 'd'), b.g(5, 'd'))) << endl;
		cout << _[t] ->* F._(5, _('c', 'd')) << endl;
		cout << (_[t] ->* F)(5, _('c', 'd')) << endl;  // not in GCC
		cout << (a.h(), b.h(), t ->* m) << endl;
		cout << (t ->* h._(), t ->* m) << endl;
		cout << ((t ->* h)(), t ->* m) << endl;
		cout << endl;

		cout << "op ->* (custom, vec member ptr)" << endl;
		auto Am = _(&A::p, &A::q);
		auto Bm = _(&B::p, &B::q);
		auto AF = _(&A::f, &A::g);
		auto BF = _(&B::f, &B::g);
		auto H  = _(&A::h, &B::h);
		cout << _(_(a.p, a.q), _(b.p, b.q)) << endl;
		cout << _(a, b) ->* _(Am, Bm) << endl;  // not in GCC
		cout << _(_(a.f(4, 'b'), a.g(4, 2)), _(b.f(4, 'b'), b.g(4, 2))) << endl;
		cout << _(a, b) ->* _(AF, BF)._(4, _[_('b', 2)]) << endl;  // not in GCC
		cout << (_(a, b) ->* _(AF, BF))(4, _[_('b', 2)]) << endl;  // not in GCC
		cout << (a.h(), b.h(), t ->* m) << endl;
		cout << (t ->* H._(), t ->* m) << endl;
		cout << ((t ->* H)(), t ->* m) << endl;
		cout << endl;

		cout << "op ->* (custom, atom member ptr)" << endl;
		auto mf = a ->* &A::f;
		cout << a.p << endl;
		cout << a ->* &A::p << endl;
		cout << a.f(5, 'c') << endl;
		cout << mf(5, 'c') << endl;
		cout << _(a.f(5, 'c'), a.f(7, 'c')) << endl;
		cout << mf(_(5, 7), 'c') << endl;
		cout << endl;

		cout << "op ->* (pow)" << endl;
		using P = afun::pow;
		using VP = afun::vec_apply <P>;
		cout << P()(2, 3) << endl;
		cout << _[2] ->* 3 << endl;
		cout << VP()(2, _(3, 2, 1, 0)) << endl;
		cout << 2 ->* _(3, 2, 1, 0) << endl;
		cout << pow(a, 2) << endl;
		cout << a ->* 2 << endl;
		cout << endl;
	}

}
//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
