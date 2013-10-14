#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace vec_test {

using namespace ivl;
using namespace ivl::types;
using ivl::apply;

//-----------------------------------------------------------------------------

struct
{
	template <typename X>
	X operator()(const X& x) { return x + 1; }
}
inc;

struct
{
	template <typename X, typename Y, typename Z>
	tuple <Y&&, Z&&, X&&>
	operator()(X&& x, Y&& y, Z&& z)
	{
		return _(fwd <Y>(y), fwd <Z>(z), fwd <X>(x));
	}
}
shift;

afun::op::add add;

afun_details::tup_vec <afun::op::add> Add;

//-----------------------------------------------------------------------------

void run()
{
	{
		cout << "apply unary" << endl;
		auto t = val('a', 3.14, 2);
		cout << apply(inc, t) << endl;
		cout << endl;

		cout << "apply binary (zip)" << endl;
		cout << apply(add, t, _(1, 2, 3)) << endl;
		cout << endl;
	}

	{
		cout << "inner" << endl;
		auto t = val('a', 3.14, 2);
		cout << inner(t, 'X', _(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "apply ternary (inner)" << endl;
		auto t = val('a', 3.14, 2);
		cout << apply(shift, t, 'X', _(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "apply operator functor (inner)" << endl;
		auto t = val('a', 3.14, 2, "hello");
		cout << t << endl;
		cout << apply(add, t, _(1, 2, 3, 4)) << endl;
		cout << apply(add, t, 2) << endl;
		cout << apply(add, 2, t) << endl;
		cout << apply(add, 2, _(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "vec operator functor" << endl;
		auto t = val('a', 3.14, 2, "hello");
		cout << t << endl;
		cout << Add(t, _(1, 2, 3, 4)) << endl;
		cout << Add(t, 2) << endl;
		cout << Add(2, t) << endl;
		cout << Add(2, _(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "binary vec operator" << endl;
		auto t = val('a', 3.14, 2, "hello");
		cout << t << endl;
		cout << t + _(1, 2, 3, 4) << endl;
		cout << t + 2 << endl;
		cout << 2 + t << endl;
		cout << 2 + _(1, 2, 3, 4) << endl;
		cout << endl;
	}

	{
		cout << "binary vec operator" << endl;
		auto t = val(5, 6, 7, 8);
		cout << 1 + 2 << endl;
		cout << t + 2 << endl;
		cout << 2 + t << endl;
		cout << t + _(1, 2, 3, 4) << endl;
		cout << t + _(1, 2, 3, 4, 5, 6) << endl;
		cout << t + _(1, 2, 3, _(4, 5, 6, _(7, 8))) << endl;
		cout << endl;
	}
}
//-----------------------------------------------------------------------------

}  // namespace vec_test

//-----------------------------------------------------------------------------

int main()
{
	vec_test::run();
}