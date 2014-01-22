#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;
namespace op = ivl::op;

//-----------------------------------------------------------------------------

template <char C>
struct rf
{
	char operator()(int x) { return x + C; }
};

template <char C>
struct pf
{
	void operator()(int x) { cout << char(x + C) << " "; }
};

template <char C> using vrf = afun::vec_apply <rf <C> >;
template <char C> using vpf = afun::vec_loop <pf <C> >;
template <char C> using arf = afun::vec_auto <rf <C> >;
template <char C> using apf = afun::vec_auto <pf <C> >;

//-----------------------------------------------------------------------------

template <template <char> class R, template <char> class V>
void call()
{
	{
		cout << "custom operator()" << endl;
		auto f = R <'A'>();
		auto F = val(R <'A'>(), R <'N'>());
		auto p = 5;
		auto P = val(5, val(0, 2));
		cout << f(p) << endl;
		cout << f(P) << endl;
		cout << F(p) << endl;
		cout << F(P) << endl;
		cout << _[F](P) << endl;
		cout << F(_[P]) << endl;
		cout << endl;
	}

	{
		cout << "custom void operator()" << endl;
		auto f = V <'A'>();
		auto F = val(V <'A'>(), V <'N'>());
		auto p = 5;
		auto P = val(5, val(0, 2));
		f(p); cout << endl;
		f(P); cout << endl;
		F(p); cout << endl;
		F(P); cout << endl;
		_[F](P); cout << endl;
		F(_[P]); cout << endl;
		cout << endl;
	}
}

//-----------------------------------------------------------------------------

void run()
{
	// TODO: val needed only for GCC; clang working also with _

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
		auto t = val(5, 6, -7, 2);
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
		cout << _[a][_(2, 0)] << endl;
// 		cout << _[t][_(2, 0, 1, 0)] << endl;
		cout << endl;
	}

	{
		cout << "op ()" << endl;
		auto mid = [](double x, double y) { return (x + y) / 2; };
		auto f = val(op::add, _[mid], op::div);
		auto y = val(4, -2, 16.);
		cout << f(8, 4) << endl;
		cout << f(8, y) << endl;
		cout << f(8, _[y]) << endl;
		cout << endl;
	}

	{
		call <vrf, vpf>();
		call <arf, apf>();
	}

// // TODO: runtime errors
// 	{
// 		cout << "expression" << endl;
// 		double x = 0;
// 		int i = -2;
// 		auto t = _(x, _(i));
// // 		auto a = val(3.14, val(7));
// // 		auto b = val(6.18, val(-2));
// 		auto a = _(3.14, _(7));
// 		auto b = _(6.18, _(-2));
//
// // 		cout << (a + 2 * b).at <0>() << endl;
// // 		cout << (a + 2 * b).at <1>() << endl;
//
// // 		report <tup_types <decltype(a + 2 * b)> >();
// // 		report <rtel <0, tup_types <decltype(a + 2 * b)> > >();
// // 		report <rtel <1, tup_types <decltype(a + 2 * b)> > >();
//
// // 		t = a + 2 * b;
// // 		cout << t << endl;
// // 		cout << (a + 2 * b) << endl;
// // 		cout << endl;
// 	}

}
//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
