#include <ivl/ivl>

using namespace ivl;
using namespace ivl::types;

int main ()
{
	using ivl::flip;
	using ivl::join;
	array <int, 2> a = {2,3}, b;
	array <double, 2> c;
// 	report <seq_type <decltype(join(a,b))> >();
// 	report <seq_type <decltype(join(a,c))> >();
	report <u_seq_ref <decltype(join(a,b))> >();
	report <u_seq_ref <decltype(join(a,c))> >();
	cout << "Hello, world!" << endl;
}
