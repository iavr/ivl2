#include <ivl/ivl>

using namespace ivl;
using namespace ivl::types;

struct F
{
	template <size_t I>
	INLINE constexpr size_t _() const { return I; }
};

int main ()
{
	constexpr size_t L = 1<<11;
	afun::lookup_fun <L, F> f;
	for (size_t i = 0; i < L; ++i)
		cout << f(i) << " ";

	cout << endl;

	cout << "Hello, world!" << endl;
}
