#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

IVL_KEY_MEMBER(begin)
IVL_KEY_MEMBER(empty)
IVL_KEY_MEMBER(end)
IVL_KEY_MEMBER(length)
IVL_KEY_MEMBER(size)

IVL_KEY_MEMBER(p)
IVL_KEY_MEMBER(q)
IVL_KEY_MEMBER(f)
IVL_KEY_MEMBER(g)
IVL_KEY_MEMBER(h)

}

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;

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
// 	array <int> p;  // TODO: ARRAY
	int p;
	double q;
	int f(int x, char c) const { return x;}
	double g(double x, int i) const { return 3 * x; }
	void h() { q *= 2; }
};

int pow(const A& a, int e) { return std::pow(a.p, e); }
int pow(const B& b, int e) { return std::pow(b.p, e); }

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "op ->*" << endl;
// 		using A = array <int>;  // TODO: ARRAY
		using A = std::vector <int>;
		using V = std::vector <double>;
		A a(3);
		V v(5);
		auto t = _(a, v);
		auto m = _(size, empty);
		cout << _(a.size(), v.empty()) << endl;
		cout << t ->* m._() << endl;
		cout << (t ->* m)() << endl;
		cout << _(_(a.size(), a.empty()), _(v.size(), v.empty())) << endl;
		cout << t ->* _[m]._() << endl;
		cout << (t ->* _[m])() << endl;
		cout << endl;
	}

	{
		cout << "op ->* (custom, key)" << endl;
		A a{4, "hello"};
// 		B b{array <int>(3, 2), 3.14};  // TODO: ARRAY
		B b{3, 3.14};
		auto t = _(a, b);
		auto m = _(p, q);
		auto F = _(f, g);
		cout << _(a.p, b.q) << endl;
		cout << t ->* m << endl;
		cout << _(_(a.p, b.p), _(a.q, b.q)) << endl;
		cout << _[t] ->* m << endl;
		cout << _(a.f(5, 'c'), b.g(5, 'd')) << endl;
		cout << t ->* F._(5, _('c', 'd')) << endl;
		cout << (t ->* F)(5, _('c', 'd')) << endl;
		cout << _(_(a.f(5, 'c'), b.f(5, 'c')), _(a.g(5, 'd'), b.g(5, 'd'))) << endl;
		cout << _[t] ->* F._(5, _('c', 'd')) << endl;
		cout << (_[t] ->* F)(5, _('c', 'd')) << endl;
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
		cout << _(a.f(10, 'c'), a.f(10, 'd')) << endl;
		cout << a ->* _[&A::f]._(10, _('c', 'd')) << endl;
		cout << (a ->* &A::f)(10, _('c', 'd')) << endl;
		cout << _(_(a.p, a.q), _(b.p, b.q)) << endl;
		cout << _(a, b) ->* _(Am, Bm) << endl;
		cout << _(_(a.f(4, 'b'), a.g(4, 2)), _(b.f(4, 'b'), b.g(4, 2))) << endl;
		cout << _(a, b) ->* _(AF, BF)._(4, _[_('b', 2)]) << endl;
		cout << (_(a, b) ->* _(AF, BF))(4, _[_('b', 2)]) << endl;
		cout << (a.h(), b.h(), t ->* m) << endl;
		cout << (t ->* H._(), t ->* m) << endl;
		cout << ((t ->* H)(), t ->* m) << endl;
		cout << endl;

		cout << "op ->* (custom, atom member ptr)" << endl;
		auto af = a ->* &A::f;
		cout << a.p << endl;
		cout << a ->* &A::p << endl;
		cout << a.f(5, 'c') << endl;
		cout << af(5, 'c') << endl;
		cout << _(a.f(5, 'c'), a.f(7, 'c')) << endl;
		cout << af(_(5, 7), 'c') << endl;
		cout << endl;

		cout << "op ->* (pow)" << endl;
		using P = afun::pow;
		using VP = afun::vec_apply <P>;
		cout << P()(2, 3) << endl;
		cout << _[2] ->* 3 << endl;
		cout << VP()(2, _(3, 2, 1, 0)) << endl;
		cout << 2 ->* _(3, 2, 1, 0) << endl;
		cout << _(pow(a, 2), pow(b, 2)) << endl;
		cout << t ->* 2 << endl;
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
