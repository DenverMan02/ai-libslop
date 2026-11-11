#ifndef __RATIO_H__
#define __RATIO_H__

namespace Sexy
{
	struct Ratio
	{
		Ratio();
		Ratio(int theNumerator, int theDenominator);
		void Set(int theNumerator, int theDenominator);
		float Get();
		bool operator==(const Ratio& theRatio) const;
		bool operator!=(const Ratio& theRatio) const;
		bool operator<(const Ratio& theRatio) const;
		bool operator>(const Ratio& theRatio) const;
		template< typename T > int operator*(T t) const;
		template< typename T > int operator/(T t) const;
		int mNumerator;
		int mDenominator;
	};

	inline bool Ratio::operator==(const Ratio& theRatio) const
	{
		return mNumerator == theRatio.mNumerator && mDenominator == theRatio.mDenominator;
	}

	inline bool Ratio::operator!=(const Ratio& theRatio) const
	{
		return ! (*this == theRatio);
	}

	inline bool Ratio::operator<(const Ratio& theRatio) const
	{
		return (mNumerator*theRatio.mDenominator/mDenominator < theRatio.mNumerator)
			|| (mNumerator < theRatio.mNumerator*mDenominator/theRatio.mDenominator);
	}

	inline bool Ratio::operator>(const Ratio& theRatio) const
	{
		return (mNumerator*theRatio.mDenominator/mDenominator > theRatio.mNumerator)
			|| (mNumerator > theRatio.mNumerator*mDenominator/theRatio.mDenominator);
	}

	template< typename T >
	inline int Ratio::operator*(T t) const
	{
		return t * mNumerator / mDenominator;
	}

	template< typename T >
	inline int Ratio::operator/(T t) const
	{
		return t * mDenominator / mNumerator;
	}

	template< typename T >
	inline int operator*(T t, const Ratio& theRatio)
	{
		return t * theRatio.mNumerator / theRatio.mDenominator;
	}

	template< typename T >
	inline int operator/(T t, const Ratio& theRatio)
	{
		return t * theRatio.mDenominator / theRatio.mNumerator;
	}

}

#endif
