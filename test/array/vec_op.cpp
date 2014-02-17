#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;

//-----------------------------------------------------------------------------

void run()
{

// 	{
// 		cout << "op ++" << endl;
// 		auto t = _('a', 3.14, _(2, 5));
// 		cout << t++ << endl;
// 		cout << t << endl;
// 		cout << ++t << endl;
// 		cout << t << endl;
// 		cout << endl;
// 	}

	{
		cout << "op <" << endl;
		using A = array <int, 4>;
		A a = {-1, 3.14, 2, 12};
		cout << (1 < 2) << endl;
		cout << (2 < a) << endl;
		cout << (a < 2) << endl;
		cout << (a < a) << endl;
		cout << endl;
	}

	{
		cout << "op +=" << endl;
		int i = -1;
		using A = array <int, 4>;
		A a = {5, 6, -7, 2};
		cout << (i += 1) << endl;
		cout << (i += a) << endl;
		cout << (a += i) << endl;
		cout << (a += a) << endl;
		cout << endl;
	}

// 	{
// 		cout << "op <<" << endl;
// 		auto t = _(0, 1, 2, 3);
// 		cout << (1 << 2) << endl;
// 		cout << (1 << t) << endl;
// 		cout << (t << 2) << endl;
// 		cout << (t << t) << endl;
// 		cout << endl;
// 	}

	{
		cout << "op *" << endl;
		int i = 0, j = 1, k = 2;
		int *p = &i, *q = &j, *r = &k;
		using A = array <int*, 3>;
		cout << *A{p, q, r} << endl;
		cout << endl;
	}

// 	{
// 		cout << "op []" << endl;
// 		int a[] = {7, 9, -2, 0};
// 		double b[] = {2, 3.14, 6.28};
// // 		array <double> b[] = {{2, 3.14}, {1, 2}, {3, 7}};  // TODO: ARRAY
// 		const char c[] = "hello";
// 		std::vector <string> d = { "hello", ",", "world" };
// 		auto t = _(a, b, c, d);
// 		cout << t[2] << endl;
// 		cout << t[_(2, 0 , 1, 0)] << endl;
// 		cout << _[a][_(2, 0, _(1, 0))] << endl;
// 		cout << _[t][_(2, 0, _(1, 0))] << endl;
// 		cout << endl;
// 	}
//
// 	{
// 		cout << "op ()" << endl;
// 		auto mid = [](double x, double y) { return (x + y) / 2; };
// 		auto f = _(op::add, _[mid], op::div);
// 		auto y = _(4, -2, 16.);
// 		cout << f(8, 4) << endl;
// 		cout << f(8, y) << endl;
// 		cout << f(8, _[y]) << endl;
// 		cout << _(f, op::add)(8, _(y, 1)) << endl;
// 		cout << endl;
// 	}

}

//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
