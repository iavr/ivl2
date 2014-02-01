#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace run {

using namespace std;
using namespace ivl;
using ivl::array;

//-----------------------------------------------------------------------------

struct A
{
	int& i;
	A(const A& a) : i(a.i) { cout << "construct A with A." << i << endl; }
	A(int& i) : i(i) { cout << "construct A with " << i << endl; }
	~A() { cout << "destruct A" << endl; }
	operator int() const { return i; }
};

struct B
{
	int i;
	B(const B& b) : i(b.i) { cout << "construct B with B." << i << endl; }
	B(int i = 35) : i(i) { cout << "construct B with " << i << endl; }
	~B() { cout << "destruct B" << endl; }
	operator int() const { return i; }
};

//-----------------------------------------------------------------------------

void run()
{
	{
		const size_t K = 3;

		array <int> x(K, 5);

		for (size_t k = 0; k < K; k++)
			x[k] = 2 * k;

		cout << "x = " << x << endl;
		cout << endl;

//-----------------------------------------------------------------------------

// 	int i = -8;
// 	array <A> a(K, i);
// 	cout << "a = " << a << endl;
//
// 	for (size_t k = 0; k < K; k++)
// 		a[k].i = 3 * k;
//
// 	cout << "a = " << a << endl;
// 	cout << endl;

//-----------------------------------------------------------------------------

		const size_t L = 6;

		x.init(L, 9);
		cout << "x = " << x << endl;

		for (size_t k = 0; k < L; k++)
			x[k] = 15 * k;

		cout << "x = " << x << endl;

		x.resize(12, -14);
		cout << "x = " << x << endl;

		x.resize(16);
		cout << "x = " << x << endl;

		x.resize(7, 28);
		cout << "x = " << x << endl;

		x.resize(4);
		cout << "x = " << x << endl;
		cout << endl;

//-----------------------------------------------------------------------------

// 	array <B> b(L, 4);
// 	cout << "b = " << b << endl;
//
// 	b.resize(12, -14);
// 	cout << "b = " << b << endl;
//
// 	b.resize(15);
// 	cout << "b = " << b << endl;
//
// 	b.resize(7, 28);
// 	cout << "b = " << b << endl;
//
// 	b.resize(4);
// 	cout << "b = " << b << endl;
//
// 	cout << endl;

//-----------------------------------------------------------------------------

		const size_t M = 6;

		array <int> y;

		for (size_t k = 0; k < M; k++)
			y.push_back(k);

		cout << "y = " << y << endl;

		for (size_t k = 0; k < 3; k++)
			y.pop_back();

		cout << "y = " << y << endl;
		cout << endl;

//-----------------------------------------------------------------------------

		array <B> z = x;
		cout << "z = " << z << endl;
		cout << endl;

// 		z = y;
		cout << "z = " << z << endl;
		cout << endl;

//-----------------------------------------------------------------------------

		cout << "x = " << x << endl;
		cout << "y = " << y << endl;

		x.swap(y);
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;

// 		x = y;

		cout << "x = " << x << endl;
		cout << "y = " << y << endl;

		y.push_back();
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		array <array <int> >a(4, _(3, 48));
		cout << a << endl;
		cout << endl;
	}

}

//-----------------------------------------------------------------------------

}  // namespace run

//-----------------------------------------------------------------------------

int main()
{
	run::run();
}
