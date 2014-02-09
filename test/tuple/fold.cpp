#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "min" << endl;
		auto t = _(14, 7, 3, -8, 9, 0);
		cout << min(_()) << endl;
		cout << max(_()) << endl;
		cout << min(t) << endl;
		cout << max(t) << endl;
		cout << min_off(_()) << endl;
		cout << max_off(_()) << endl;
		cout << min_off(t) << endl;
		cout << max_off(t) << endl;
		cout << endl;
	}

	{
		int m;
		size_t p;
		types::sep sep;

		cout << "vec-min" << endl;
		auto t = _(14, 7, 3, -8, 9, 0);
		cout << min(14, 7, 3, -8, 9, 0) << endl;
		cout << max(14, 7, 3, -8, 9, 0) << endl;
		cout << min(6, t) << endl;
		cout << max(6, t) << endl;
		cout << min(14) << endl;
		cout << max(14) << endl;
		cout << (min.io(m, p, sep, t), _(m, p)) << endl;
		cout << (max.io(m, p, sep, t), _(m, p)) << endl;
		cout << endl;
	}

	{
		cout << "lim::min" << endl;
		cout << min._<int>() << endl;
		cout << max._<int>() << endl;
		cout << min._<double>() << endl;
		cout << max._<double>() << endl;
		cout << endl;
	}

	{
		int m;
		size_t p;

		cout << "key min" << endl;
		auto t = _(14, 7, 3, -8, 9, 0);
		min=14;
		min._(6, t);
		cout << (_(m, p) = min._(_())) << endl;
		cout << (_(m, p) = max._(_())) << endl;
		cout << (_(m, p) = min._(t)) << endl;
		cout << (_(m, p) = max._(t)) << endl;
		_(max._()) = max._();  // ambiguity check
		cout << endl;
	}

	{
		cout << "foo min" << endl;
		auto t = foos(14, 7, 3, -8, 9, 0);
		cout << endl;
		cout << "begin" << endl;
		cout << min(t) << endl;
		cout << "end" << endl;
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
