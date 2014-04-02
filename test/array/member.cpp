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

using ivl::seq;
using ivl::size;
using ivl::empty;

//-----------------------------------------------------------------------------

struct A
{
	int p;
	std::string q;
	int f(int x, char c) const { return x + c - 'a'; }
	double g(double x, int i) const { return i / x; }
	void h() { p++; }
};

int pow(const A& a, int e) { return std::pow(a.p, e); }

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "op ->*" << endl;
// 		using A = array <int>;  // TODO: ARRAY
		using A = std::vector <int>;
		A a(3), v(5);
		auto s = seq(a, v);
		auto m = _(size, empty);
		cout << seq(_(a.size(), a.empty()), _(v.size(), v.empty())) << endl;
		cout << s ->* m._() << endl;
		cout << (s ->* m)() << endl;
		cout << _(seq(a.size(), v.size()), seq(a.empty(), v.empty())) << endl;
		cout << _[s] ->* m._() << endl;
		cout << (_[s] ->* m)() << endl;
		cout << endl;
	}

	{
		cout << "op ->* (custom, key)" << endl;
		A a{4, "hello"}, b{3, "there"};
		auto s = seq(a, b);
		auto m = _(p, q);
		auto F = _(f, g);
		cout << seq(_(a.p, a.q), _(b.p, b.q)) << endl;
		cout << s ->* m << endl;
		cout << _(seq(a.p, b.p), seq(a.q, b.q)) << endl;
		cout << _[s] ->* m << endl;
		cout << seq(a.f(5, 'c'), b.f(5, 'd')) << endl;
		cout << s ->* f._(5, seq('c', 'd')) << endl;
		cout << (s ->* f)(5, seq('c', 'd')) << endl;
		cout << seq(_(a.f(5, 'c'), a.g(5, 'c')), _(b.f(5, 'd'), b.g(5, 'd'))) << endl;
		cout << s ->* F._(5, seq('c', 'd')) << endl;
		cout << (s ->* F)(5, seq('c', 'd')) << endl;
		cout << _(seq(a.f(5, 'c'), b.f(5, 'c')), seq(a.g(5, 'd'), b.g(5, 'd'))) << endl;
		cout << _[s] ->* F._(5, _('c', 'd')) << endl;
		cout << (_[s] ->* F)(5, _('c', 'd')) << endl;
		cout << (a.h(), b.h(), s ->* m) << endl;
		cout << (s ->* h._(), s ->* m) << endl;
		cout << ((s ->* h)(), s ->* m) << endl;
		cout << endl;

		cout << "op ->* (custom, vec member ptr)" << endl;
		auto Am = _(&A::p, &A::q);
		auto AF = _(&A::f, &A::g);
		auto H  = _[&A::h];
		cout << seq(a.f(10, 'c'), a.f(10, 'd')) << endl;
		cout << a ->* _[&A::f]._(10, seq('c', 'd')) << endl;
		cout << (a ->* &A::f)(10, seq('c', 'd')) << endl;
		cout << seq(_(a.p, a.q), _(b.p, b.q)) << endl;
		cout << s ->* Am << endl;
		cout << seq(_(a.f(4, 'b'), a.g(4, 'b')), _(b.f(4, 2), b.g(4, 2))) << endl;
		cout << s ->* AF._(4, seq('b', 2)) << endl;
		cout << (s ->* AF)(4, seq('b', 2)) << endl;
		cout << (a.h(), b.h(), s ->* m) << endl;
		cout << (s ->* H._(), s ->* m) << endl;
		cout << ((s ->* H)(), s ->* m) << endl;
		cout << endl;

		cout << "op ->* (custom, atom member ptr)" << endl;
		auto af = a ->* &A::f;
		cout << a.p << endl;
		cout << a ->* &A::p << endl;
		cout << a.f(5, 'c') << endl;
		cout << af(5, 'c') << endl;
		cout << seq(a.f(5, 'c'), a.f(7, 'c')) << endl;
		cout << af(seq(5, 7), 'c') << endl;
		cout << endl;

		cout << "op ->* (pow)" << endl;
		using P = afun::pow;
		using VP = afun::vec_apply <P>;
		cout << P()(2, 3) << endl;
		cout << _[2] ->* 3 << endl;
		cout << VP()(2, seq(3, 2, 1, 0)) << endl;
		cout << 2 ->* seq(3, 2, 1, 0) << endl;
		cout << seq(pow(a, 2), pow(b, 2)) << endl;
		cout << s ->* 2 << endl;
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
