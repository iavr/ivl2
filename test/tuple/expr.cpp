#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;

//-----------------------------------------------------------------------------

struct foo
{
	int val;

	foo(int v) : val(v) { cout << "foo(" << val << ")" << endl; }

	foo(foo&& f) : val(f.val)
		{ cout << "&&foo(" << val << ")" << endl; }

	foo(const foo& f) : val(f.val)
		{ cout << "&foo(" << val << ")" << endl; }

	~foo() { cout << "~foo(" << val << ")" << endl; }

	foo& operator=(foo&&)
		{ cout << "=&&foo(" << val << ")" << endl; return *this; }

	foo& operator=(const foo&)
		{ cout << "=&foo(" << val << ")" << endl; return *this; }

	friend std::ostream& operator<<(std::ostream& os, const foo& f)
		{ return os << "<<foo(" << f.val << ")"; }

	foo operator+(const foo& f) const
	{
		cout << "+foo(" << val << "+" << f.val << "=" << val + f.val << ")" << endl;
		return val + f.val;
	}

	foo operator*(const foo& f) const
	{
		cout << "*foo(" << val << "*" << f.val << "=" << val * f.val << ")" << endl;
		return val * f.val;
	}
};

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "expression" << endl;
		int x = 0, i = -2, j = 9;
		auto t = _(x, _(i, j));
		auto a = _(1, _(7, 6));
		auto b = _(5, _(-2, 3));
		cout << a + 2 * b << endl;
		t = a + 2 * b;
		cout << t << endl;
		cout << endl;
	}

	{
		cout << "expression (foo)" << endl;
		foo x = 0, i = -2, j = 9, z = 2;
		auto t = _(x, _(i, j));
		auto a = _(foo(1), _(foo(7), foo(6)));
		auto b = _(foo(5), _(foo(-2), foo(3)));
		cout << endl;
		cout << "begin" << endl;
		cout << at._<0>(at._<1>((a + z * b))) << endl;
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
