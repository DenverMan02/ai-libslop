#ifndef __SEXYAPPFRAMEWORK_MINMAX__
#define __SEXYAPPFRAMEWORK_MINMAX__

#include <algorithm>
#include <limits>
using std::min;
using std::max;

#if defined(__aarch64__)
inline
std::size_t operator ""_sz(unsigned long long int x)
{
	return static_cast<std::size_t>(x);
}
#else
#ifndef HOST_WINDOWS
inline
std::size_t operator "" _sz(unsigned long long int x)
{
    return static_cast<std::size_t>(x);
}
#endif
#endif

template <typename T, typename U>
bool TypeCanFitValue(const U value)
{
	const intmax_t bot_t = intmax_t(std::numeric_limits<T>::min() );
	const intmax_t bot_u = intmax_t(std::numeric_limits<U>::min() );
	const uintmax_t top_t = uintmax_t(std::numeric_limits<T>::max() );
	const uintmax_t top_u = uintmax_t(std::numeric_limits<U>::max() );
	return !((bot_t > bot_u && value < static_cast<U>(bot_t)) || (top_t < top_u && value > static_cast<U>(top_t)));
}

#endif
