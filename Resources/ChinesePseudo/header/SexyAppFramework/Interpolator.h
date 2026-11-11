
#pragma once

#include "EaseFunction.h"
#include "Point.h"
#include "Color.h"
#include <map>

namespace Sexy
{

	/** */
	struct Key
	{
		int tick;
		bool ease;
		bool tween;
	};
	
	static const bool kTween = true;
	static const bool kNoTween = false;

	static const bool kEase = true;
	static const bool kNoEase = false;
	/** */
	template< typename T >
	struct TypedKey
		: public Key
	{
		T value;
	};

	/** */
	template< typename T >
	struct KeyLess
	{
		bool operator()( const TypedKey<T>& lhs, const TypedKey<T>& rhs ) const
		{
			return lhs.tick < rhs.tick;
		}
	};

	/** */
	class Interpolator
	{
	protected:
		Interpolator();
		EaseFunction mEaseFunc;
		bool mEaseFuncSet;
		void SetupEaseFunc( Key& from, Key& to );
	};

	/** */
	template< typename T >
	class KeyInterpolator
		: public Interpolator
	{
		typedef Interpolator super;
	public:
		KeyInterpolator& operator=( const KeyInterpolator& rhs );
		void Clear();
		bool Empty();
		void SetKey( int tick, const T& value, bool ease = kNoEase, bool tween = kTween );
		int FirstTick();
		int LastTick();
		T operator()( float tick );
		typedef std::map< int, TypedKey<T> > Keys;
		typedef typename Keys::iterator KeyIterator;
		Keys mKeys;
		KeyIterator mKey;
	};

	template< typename T >
	inline T tlerp( float t, const T& a, const T& b )
	{
		return a + t * (b - a);
	}
	
	template<>
	inline Sexy::Point tlerp<Sexy::Point>( float t, const Sexy::Point& a, const Sexy::Point& b )
	{
		return Sexy::Point( tlerp(t,a.mX,b.mX), tlerp(t,a.mY,b.mY) );
	}

	template<>
	inline Color tlerp<Color>( float t, const Color& a, const Color& b )
	{
		return Color( tlerp(t,a.mRed,b.mRed), tlerp(t,a.mGreen,b.mGreen), tlerp(t,a.mBlue,b.mBlue), tlerp(t,a.mAlpha,b.mAlpha) );
	}
	
	typedef KeyInterpolator<int> IntInterpolator;
	typedef KeyInterpolator<bool> BoolInterpolator;
	typedef KeyInterpolator<float> FloatInterpolator;
	typedef KeyInterpolator<Sexy::Point> PointInterpolator;
	typedef KeyInterpolator<Color> ColorInterpolator;
}
