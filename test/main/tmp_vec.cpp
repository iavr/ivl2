#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;
namespace op = ivl::op;

//-----------------------------------------------------------------------------

struct conv
{
	template <typename P, typename T>
	P _(T&& x) { return (P) fwd <T>(x); }
};

//-----------------------------------------------------------------------------

struct A { int x; };
struct B : A { };
struct C : A { };

template <typename S>
S& operator<<(S& s, B) { return s << "B"; }

template <typename S>
S& operator<<(S& s, C) { return s << "C"; }

//-----------------------------------------------------------------------------

void run()
{

	{
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
		using C = afun::tmp_vec_apply <conv>;
		using S = pack <char, int, double>;
		float f = '0' + 3.14;
		double d = '0' + 6.18;
		size_t s = 1234567890;
		auto x = _(f, d, s);
		cout << C()._<S>(x) << endl;
		cout << C()._<S>(_[x]) << endl;
		cout << endl;
	}

// 	{
// 		B b;
// 		C c;
// 		A &rb = b, &rc = c;
// 		_static_cast._<pack <B&> >(rb);
// 		cout << _static_cast._<pack <C&, B&> >(_(rc, rb)) << endl;
// 	}

}

//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
