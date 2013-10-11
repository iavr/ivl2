#include <ivl/ivl>

//-----------------------------------------------------------------------------

struct A { int x; };
struct B { float f(int x) { return sqrt(x); } };
struct C { C(int x) { } };
struct D
{
	void f(int x)        { std::cout << "void: " << x << std::endl; }
	int  g(int x)        { std::cout << "int: " << x << std::endl; return 0; }
	void fc(int x) const { std::cout << "void const: " << x << std::endl; }
	int  gc(int x) const { std::cout << "int const: " << x << std::endl; return 0; }
};

//-----------------------------------------------------------------------------

namespace operators {

using namespace std;
using namespace ivl;
using namespace ivl::scalar_fun;

//-----------------------------------------------------------------------------

void run()
{
	{
		cout << "member:" << endl;
		A a;
		B b;
		op::ref_member()(a, &A::x) = 3;
		float x = op::ref_call()(b, &B::f, 2);
		float y = op::ptr_call()(&b, &B::f, 4);
		cout << a.x << " " << x << " " << y << endl;
		cout << endl;
	}

	{
		cout << "call:" << endl;
		D d;
		op::ref_call()(d, &D::f, 1);
		op::ref_call()(d, &D::g, 2);
		op::ref_call()(d, &D::fc, 3);
		op::ref_call()(d, &D::gc, 4);
		op::ref_call()(D(), &D::f, 1);
		op::ref_call()(D(), &D::g, 2);
		op::ref_call()(D(), &D::fc, 3);
		op::ref_call()(D(), &D::gc, 4);
		cout << endl;
	}

	{
		cout << "new:" << endl;
		A* a = op::_new()._<A>();
		C* c = op::new_direct()._<C>(8);
		int s = 4;
		op::_new()._<A>(s);
		op::_new()._<A, 3, 5>(s);
		A* a2 = op::new_list()._<A>(8);
		cout << a2->x << endl;
		cout << endl;
	}
}

//-----------------------------------------------------------------------------

}  // namespace operators

//-----------------------------------------------------------------------------

int main()
{
	operators::run();
}
