#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;
namespace op = ivl::op;

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "op ++" << endl;
		auto t = _('a', 3.14, _(2, 5));
		cout << t++ << endl;
		cout << t << endl;
		cout << ++t << endl;
		cout << t << endl;
		cout << endl;
	}

	{
		cout << "op <" << endl;
		auto t = _(0, 1, 2, 3);
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
		auto t = _(0, 1, 2, 3);
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
		array <double> b[] = {{2, 3.14}, {1, 2}, {3, 7}};
		const char c[] = "hello";
		std::vector <string> d = { "hello", ",", "world" };
		auto t = _(a, b, c, d);
		cout << t[2] << endl;
		cout << t[_(2, 0 , 1, 0)] << endl;
		cout << _[a][_(2, 0, _(1, 0))] << endl;
		cout << _[t][_(2, 0, _(1, 0))] << endl;
		cout << endl;
	}

	{
		cout << "op ()" << endl;
		auto mid = [](double x, double y) { return (x + y) / 2; };
		auto f = _(op::add, _[mid], op::div);
		auto y = _(4, -2, 16.);
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
