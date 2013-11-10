#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

void run()
{
	{
		cout << "++" << endl;
		auto t = val('a', 3.14, _(2, 5));
		cout << t++ << endl;
		cout << t << endl;
		cout << ++t << endl;
		cout << t << endl;
		cout << endl;
	}

	{
		cout << "<" << endl;
		auto t = val(0, 1, 2, 3);
		cout << (1 < 2) << endl;
		cout << (2 < t) << endl;
		cout << (t < 2) << endl;
		cout << (t < t) << endl;
		cout << endl;
	}

	{
		cout << "+=" << endl;
		int i = -1;
		auto t = _(5, 6, -7, 2);
		cout << (i += 1) << endl;
		cout << (i += t) << endl;
		cout << (t += i) << endl;
		cout << (t += t) << endl;
		cout << endl;
	}

	{
		cout << "<<" << endl;
		auto t = val(0, 1, 2, 3);
		cout << (1 << 2) << endl;
		cout << (1 << t) << endl;
		cout << (t << 2) << endl;
		cout << (t << t) << endl;
		cout << endl;
	}

	{
		cout << "*" << endl;
		int i = 0, j = 1, k = 2;
		int *p = &i, *q = &j, *r = &k;
		cout << *_(p, q, r) << endl;
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
