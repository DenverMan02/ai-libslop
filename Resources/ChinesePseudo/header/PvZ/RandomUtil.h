///////////////////////////////////
//
//	random util
//
////////////////////////////////////
#ifndef __RANDOM_UTIL_H__
#define __RANDOM_UTIL_H__

#include "SexyAppFramework/Common.h"

class RandomUtil {
public:
    // random between a <-> b (not inclde b, but include a)
	template<class T>
	static T RandRange(const T& a, const T& b){
		return a + Sexy::Rand(b - a);
	}

	template<class T>
	static bool IsInRandom(const T& value, const T& a, const T& b) {
		T randomValue = RandRange(a, b);
		return value >= randomValue;
	}
};

#endif
