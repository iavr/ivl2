#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;

//-----------------------------------------------------------------------------

struct A { int x; };
struct B : A { };
struct C : A { };

template <typename S>
S& operator<<(S& s, A) { return s << "A"; }

template <typename S>
S& operator<<(S& s, B) { return s << "B"; }

template <typename S>
S& operator<<(S& s, C) { return s << "C"; }

//-----------------------------------------------------------------------------

struct convert
{
	template <typename P, typename T>
	P _(T&& x) const { return (P) fwd <T>(x); }
};

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "sizeof, alignof, C-style conversion" << endl;
		using S = pack <char, int, double>;
		using T = pack <char, int, double, array <double> >;
		cout << _sizeof(_('a', 5, 3.14, array <double>())) << endl;
		cout << _sizeof._<T>() << endl;
		cout << _alignof._<T>() << endl;
		float x = '0' + 3.14;
		cout << op::conv._<S>(x) << endl;
		cout << endl;
	}

	{
		cout << "static_cast" << endl;
		B b;
		C c;
		A &lb = b, &lc = c;
		A &&rb = B(), &&rc = C();
		cout << _static_cast._<A>(_(c, b)) << endl;
		cout << _static_cast._<pack <C&, B&> >(_(lc, lb)) << endl;  // only if B, C are non-empty
		cout << _static_cast._<pack <C&&, B&&> >(_(rc, rb)) << endl;
		cout << endl;
	}

	{
		cout << "custom template _" << endl;
		using C = afun::tmp_vec_apply <convert>;
		using S = pack <char, int, double>;
		float f = '0' + 3.14;
		double d = '0' + 6.18;
		size_t s = 12345;
		auto x = _(f, d, s);
		cout << C()._<S>(x) << endl;
		cout << C()._<S>(_[x]) << endl;
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
