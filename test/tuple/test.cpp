#include <ivl/ivl>

using namespace ivl;
using namespace types;

int main ()
{
	{
		using namespace tuples;

		using T = zip_tup <
			pre_tuple <int &, double &>,
			pre_tuple <int &, double &>
		>;

		using V = pre_tuple <
			pre_tuple <int, int>,
			pre_tuple <double, double>
		>;

		using A = tup_assign <tup_val <T>, V>;

		cout << A{} << endl;
		report <tup_val <T> >();
		report <tup_type <T> >();
		report <tup_ref <T> >();
	}

// 	{
// 		int k = 8, j = 0;
// 		double x = 4.5, z = 0;
// 		_(k, x) = _(j, z);
// 	}

	cout << "Hello, world!" << endl;
}
