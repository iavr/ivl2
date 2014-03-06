#include <ivl/ivl>

using namespace ivl;

struct A     { virtual void f() = 0; };
struct B : A { virtual void f() = 0; };

int main ()
{
	cout << "Hello, world!" << endl;
}
