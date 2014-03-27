#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;
using ivl::seq;

//-----------------------------------------------------------------------------

template <typename T>
class func : private raw_tuple <T>
{
	using B = raw_tuple <T>;
	using B::val;

public:
	template <typename... A>
	func(A&&... a) : B(fwd <A>(a)...) { }

	template <typename A, typename B>
	auto operator()(A&& a, B&& b) const
	-> decltype(fwd <A>(a) + fwd <B>(b) + gen <const T&>())
		{ return fwd <A>(a) + fwd <B>(b) + val(); }
};

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "op ++" << endl;
		auto a = seq(-1, 3.14, 2, 12);
		cout << a++ << endl;
		cout << a << endl;
		cout << ++a << endl;
		cout << a << endl;
		cout << endl;
	}

	{
		cout << "op <" << endl;
		auto a = seq(-1, 3.14, 2, 12);
		cout << (1 < 2) << endl;
		cout << (2 < a) << endl;
		cout << (a < 2) << endl;
		cout << (a < a) << endl;
		cout << endl;
	}

	{
		cout << "op +=" << endl;
		int i = -1;
		auto a = seq(5, 6, -7, 2);
		cout << (i += 1) << endl;
		cout << (i += a) << endl;
		cout << (a += i) << endl;
		cout << (a += a) << endl;
		cout << endl;
	}

	{
		cout << "op <<" << endl;
		auto a = seq(0, 1, 2, 3);
		cout << (1 << 2) << endl;
		cout << (1 << a) << endl;
		cout << (a << 2) << endl;
		cout << (a << a) << endl;
		cout << endl;
	}

	{
		cout << "op *" << endl;
		int i = 0, j = 1, k = 2;
		cout << *seq(&i, &j, &k) << endl;
		cout << endl;
	}

	{
		cout << "op []" << endl;
		auto a = seq(  0,    4,   8);
		auto b = seq(  1,    5, 9.1);
		auto c = seq(  2,  6.1,  10);
		auto d = seq(3.1,    7,  11);
		auto v = seq(a, b, c, d);
// 		auto i = seq(2, 0, 1, 0);
// 		cout << v[2] << endl;
// 		cout << v[_][2] << endl;
// 		cout <<   v[_] [  i ] << endl; // TODO: test assignment
// 		cout << _[v[_]][  i ] << endl;
// 		cout <<   v[_] [_[i]] << endl;
		cout << endl;
	}

	{
		cout << "op ()" << endl;
		array <func <double>, 3> fn = {1, 2, 3};
		auto f = fn[_];
		auto y = seq(4, -2, 16.1);
		cout << f(8, 4) << endl;
		cout << f(8, y) << endl;
		cout << f(8, _[y]) << endl;
		cout << _(f, op::add)(8, _(y, 1)) << endl;
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
