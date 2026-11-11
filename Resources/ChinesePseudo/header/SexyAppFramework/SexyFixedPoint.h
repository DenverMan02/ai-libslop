#pragma once
#ifndef SEXYFIXEDPOINT_H
#define SEXYFIXEDPOINT_H

#include <stdint.h>

#ifndef INT_ISNOT_LONG
#define INT_ISNOT_LONG 1
#endif

//It's interesting the fixed div is 10 times slow than float div. Use float div instead.
#define USE_FLOAT_DIV 1

	/**
	 *	Please note that we have to use 22:10 for PVZ2 Android since the world space is 800x600 which requires 22 bits for integer part to avoid overflow in x*x+y*y+z*z.
	 *	Since we also need high precision decimals for screen matrix, a scale value is applied to it magically.
	 *	You need to keep this in mind since we have higher precision for integer part, DIV may lose precision for decimal part.
	 */
	class FixedPoint
	{
	public:
		static const int PRECISION_BITS = 10;
		static const int SQR_PRECISION_BITS = 5;
		int v;
	private:
		// local helpers
		inline static int mul( int l, int r )
		{
			int64_t t = int64_t(l) * int64_t(r);
			t >>= PRECISION_BITS;
			return int(t);

		}

		inline static int div( int l, int r )
		{
			int64_t t = int64_t(l) << PRECISION_BITS;
			int q = int( t / r );
			return q;
		}


		public:
			/** Construction */
			inline static FixedPoint fromRaw( int raw )	{ FixedPoint tmp; tmp.v = raw; return tmp; }
			inline FixedPoint() {}
			inline FixedPoint( const FixedPoint& rhs )	: v( rhs.v ) {}
			inline FixedPoint( float rhs )			: v( (int)( rhs *  (float)( 1 << PRECISION_BITS )) ) {}
			inline FixedPoint( double rhs )		: v( (int)( rhs * (double)( 1 << PRECISION_BITS )) ) {}
			inline FixedPoint( int rhs )			: v( rhs << PRECISION_BITS ) {}
#if INT_ISNOT_LONG
			inline FixedPoint( long rhs )			: v( rhs << PRECISION_BITS ) {}
#endif //INT_ISNOT_LONG

			/** FixedPoint assignment */
			inline FixedPoint& operator=( const FixedPoint& rhs )	{ v = rhs.v; return *this; }
			inline FixedPoint& operator+=( const FixedPoint& rhs )	{ v += rhs.v; return *this; }
			inline FixedPoint& operator-=( const FixedPoint& rhs )	{ v -= rhs.v; return *this; }
			inline FixedPoint& operator*=( const FixedPoint& rhs )	{ v = mul( v, rhs.v ); return *this; }
#if USE_FLOAT_DIV
			inline FixedPoint& operator/=( const FixedPoint& rhs )	{ *this = float(*this)/float(rhs); return *this;}
#else
			inline FixedPoint& operator/=( const FixedPoint& rhs )	{ v = div( v, rhs.v ); return *this; }
#endif //USE_FLOAT_DIV

			/** int assignment */
			inline FixedPoint& operator=( int rhs )					{ v = FixedPoint( rhs ).v; return *this; }
			inline FixedPoint& operator+=( int rhs )				{ v += rhs << PRECISION_BITS; return *this; }
			inline FixedPoint& operator-=( int rhs )				{ v -= rhs << PRECISION_BITS; return *this; }
			inline FixedPoint& operator*=( int rhs )				{ v *= rhs; return *this; }
			inline FixedPoint& operator/=( int rhs )				{ v /= rhs; return *this; }

#if INT_ISNOT_LONG
			/** long assignment */
			inline FixedPoint& operator=( long rhs )				{ v = FixedPoint( rhs ).v; return *this; }
			inline FixedPoint& operator+=( long rhs )				{ v += rhs << PRECISION_BITS; return *this; }
			inline FixedPoint& operator-=( long rhs )				{ v -= rhs << PRECISION_BITS; return *this; }
			inline FixedPoint& operator*=( long rhs )				{ v *= rhs; return *this; }
			inline FixedPoint& operator/=( long rhs )				{ v /= rhs; return *this; }
#endif //INT_ISNOT_LONG
			/** float assignment */
			inline FixedPoint& operator=( float rhs )				{ v = FixedPoint( rhs ).v; return *this; }
			inline FixedPoint& operator+=( float rhs )				{ v += FixedPoint( rhs ).v; return *this; }
			inline FixedPoint& operator-=( float rhs )				{ v -= FixedPoint( rhs ).v; return *this; }
			inline FixedPoint& operator*=( float rhs )				{ *this *= FixedPoint( rhs ); return *this; }
#if USE_FLOAT_DIV
			inline FixedPoint& operator/=( float rhs )				{ *this = float(*this)/rhs; return *this; }
#else
			inline FixedPoint& operator/=( float rhs )				{ *this /= FixedPoint( rhs ); return *this; }
#endif

			/** double assignment */
			inline FixedPoint& operator=( double rhs )				{ v = FixedPoint( rhs ).v; return *this; }
			inline FixedPoint& operator+=( double rhs )				{ v += FixedPoint( rhs ).v; return *this; }
			inline FixedPoint& operator-=( double rhs )				{ v -= FixedPoint( rhs ).v; return *this; }
			inline FixedPoint& operator*=( double rhs )				{ *this *= FixedPoint( rhs ); return *this; }
			inline FixedPoint& operator/=( double rhs )				{ *this /= FixedPoint( rhs ); return *this; }

			/** shift assignment */
			inline FixedPoint& operator<<=( int shift )				{ v <<= shift; return *this; }
			inline FixedPoint& operator>>=( int shift )				{ v >>= shift; return *this; }

			/** converters */
			inline operator int()	const							{ return v >> PRECISION_BITS; }
#if INT_ISNOT_LONG
			inline operator long()	const							{ return v >> PRECISION_BITS; }
#endif
			inline operator float()		const						{ return v * ( 1.0f / static_cast<float>( ( 1 << PRECISION_BITS ) ) ); }
			inline operator double()	const						{ return v * ( 1.0f / static_cast<double>( ( 1 << PRECISION_BITS ) ) ); }


			/**
			 *	Gives access to the integer part of the number.
			 *
			 *	An use of the integer portion could be for lerping fixed-point
			 *	quantities.
			 */
			inline int		getInteger() const  { return( v >> PRECISION_BITS ); }

			/**
			 *	Gives access to the fractional part of the number.
			 */
			inline uint32_t		getFraction() const { return( v & (( 1 << PRECISION_BITS ) - 1) ); }

			inline int		getRaw() const		{ return v; }

			/** Unary operators */
			inline FixedPoint operator+() const		{ return FixedPoint::fromRaw(  v ); }
			inline FixedPoint operator-() const		{ return FixedPoint::fromRaw( -v ); }


			/** Comparison operators */

			// FixedPoint
			inline bool operator==( const FixedPoint& other )const		{ return v == other.v; }
			inline bool operator!=( const FixedPoint& other )const		{ return v != other.v; }
			inline bool operator<( const FixedPoint& other )const		{ return v  < other.v; }
			inline bool operator>( const FixedPoint& other )const		{ return v  > other.v; }
			inline bool operator<=( const FixedPoint& other )const		{ return v <= other.v; }
			inline bool operator>=( const FixedPoint& other )const		{ return v >= other.v; }

			// int
			inline bool operator==( int other )const					{ return v == FixedPoint( other ).v; }
			inline bool operator!=( int other )const					{ return v != FixedPoint( other ).v; }
			inline bool operator<( int other )const						{ return v  < FixedPoint( other ).v; }
			inline bool operator>( int other )const						{ return v  > FixedPoint( other ).v; }
			inline bool operator<=( int other )const					{ return v <= FixedPoint( other ).v; }
			inline bool operator>=( int other )const					{ return v >= FixedPoint( other ).v; }

#if INT_ISNOT_LONG
			// long
			inline bool operator==( long other )const					{ return v == FixedPoint( other ).v; }
			inline bool operator!=( long other )const					{ return v != FixedPoint( other ).v; }
			inline bool operator<( long other )const					{ return v  < FixedPoint( other ).v; }
			inline bool operator>( long other )const					{ return v  > FixedPoint( other ).v; }
			inline bool operator<=( long other )const					{ return v <= FixedPoint( other ).v; }
			inline bool operator>=( long other )const					{ return v >= FixedPoint( other ).v; }
#endif //INT_ISNOT_LONG
			// float
			inline bool operator==( float other )const					{ return v == FixedPoint( other ).v; }
			inline bool operator!=( float other )const					{ return v != FixedPoint( other ).v; }
			inline bool operator<( float other )const					{ return v  < FixedPoint( other ).v; }
			inline bool operator>( float other )const					{ return v  > FixedPoint( other ).v; }
			inline bool operator<=( float other )const					{ return v <= FixedPoint( other ).v; }
			inline bool operator>=( float other )const					{ return v >= FixedPoint( other ).v; }

			// double
			inline bool operator==( double other )const					{ return v == FixedPoint( other ).v; }
			inline bool operator!=( double other )const					{ return v != FixedPoint( other ).v; }
			inline bool operator<( double other )const					{ return v  < FixedPoint( other ).v; }
			inline bool operator>( double other )const					{ return v  > FixedPoint( other ).v; }
			inline bool operator<=( double other )const					{ return v <= FixedPoint( other ).v; }
			inline bool operator>=( double other )const					{ return v >= FixedPoint( other ).v; }


			/** Utilities */

			inline FixedPoint abs()const
			{
				return FixedPoint::fromRaw( ( v & ( 1 << 31 ) ) ? -v : v );
			}

			inline FixedPoint sign()const
			{
				return FixedPoint::fromRaw( ( v & ( 1 << 31 ) ) ? -static_cast<int>( ( 1 << PRECISION_BITS ) ): static_cast<int>( ( 1 << PRECISION_BITS ) ) );
			}

			inline FixedPoint floor()const
			{
				return FixedPoint( (int)( v >> PRECISION_BITS ) );
			}

			inline FixedPoint ceil()const
			{
				int tmp = -( -v >> PRECISION_BITS );
				return FixedPoint( tmp );
			}

			inline FixedPoint round()const
			{
				int64_t tmp = int64_t( v );
				if( tmp > 0 ) tmp += static_cast<int>( ( 1 << ( PRECISION_BITS - 1 ) ) ); else tmp-= static_cast<int>( ( 1 << ( PRECISION_BITS - 1 ) ) );
				tmp /= static_cast<int>( ( 1 << PRECISION_BITS ) );
				return FixedPoint( int( tmp ) );
			}

			inline FixedPoint sqrt()const
			{
				FixedPoint tmp;
				tmp.v = ((int)::sqrt(v)/(1<<SQR_PRECISION_BITS))<<PRECISION_BITS;
				return tmp;
			}
	};


	//////////////////////////////////////////////////////////////////////////
	// "Add" operation on FixedPoint (global)
	//////////////////////////////////////////////////////////////////////////


	// op: FixedPoint + FixedPoint

	inline FixedPoint operator+( const FixedPoint& lhs, const FixedPoint& rhs )
	{
		FixedPoint result( lhs );
		result += rhs;
		return result;
	}


	/**
	 *	int
	 */

	// op: FixedPoint + int

	inline FixedPoint operator+( const FixedPoint& lhs, int rhs )
	{
		FixedPoint result( lhs );
		result += rhs;
		return result;
	}

	// op: int + FixedPoint

	inline FixedPoint operator+( int lhs, const FixedPoint& rhs )
	{
		return rhs + lhs;
	}


	/**
	 *	float
	 */

	// op: FixedPoint + float

	inline FixedPoint operator+( const FixedPoint& lhs, float rhs )
	{
		FixedPoint result( lhs );
		result += rhs;
		return result;
	}

	// op: float + FixedPoint

	inline FixedPoint operator+( float lhs, const FixedPoint& rhs )
	{
		return rhs + lhs;
	}


	/**
	 *	double
	 */

	// op: FixedPoint + double

	inline FixedPoint operator+( const FixedPoint& lhs, double rhs )
	{
		FixedPoint result( lhs );
		result += rhs;
		return result;
	}

	// op: double + FixedPoint

	inline FixedPoint operator+( double lhs, const FixedPoint& rhs )
	{
		return rhs + lhs;
	}


	//////////////////////////////////////////////////////////////////////////
	// "Subtract" operation on FixedPoint (global)
	//////////////////////////////////////////////////////////////////////////


	// op: FixedPoint - FixedPoint

	inline FixedPoint operator-( const FixedPoint& lhs, const FixedPoint& rhs )
	{
		FixedPoint result( lhs );
		result -= rhs;
		return result;
	}


	/**
	 *	int
	 */

	// op: FixedPoint - int

	inline FixedPoint operator-( const FixedPoint& lhs, int rhs )
	{
		FixedPoint result( lhs );
		result -= rhs;
		return result;
	}

	// op: int - FixedPoint

	inline FixedPoint operator-( int lhs, const FixedPoint& rhs )
	{
		return FixedPoint( lhs ) - rhs;
	}
#if INT_ISNOT_LONG
	/**
	 *	long
	 */

	// op: FixedPoint - long

	inline FixedPoint operator-( const FixedPoint& lhs, long rhs )
	{
		FixedPoint result( lhs );
		result -= rhs;
		return result;
	}

	// op: long - FixedPoint

	inline FixedPoint operator-( long lhs, const FixedPoint& rhs )
	{
		return FixedPoint( lhs ) - rhs;
	}
#endif //INT_ISNOT_LONG

	/**
	 *	float
	 */

	// op: FixedPoint - float

	inline FixedPoint operator-( const FixedPoint& lhs, float rhs )
	{
		FixedPoint result( lhs );
		result -= rhs;
		return result;
	}

	// op: float - FixedPoint

	inline FixedPoint operator-( float lhs, const FixedPoint& rhs )
	{
		return FixedPoint( lhs ) - rhs;
	}


	/**
	 *	double
	 */

	// op: FixedPoint - double

	inline FixedPoint operator-( const FixedPoint& lhs, double rhs )
	{
		FixedPoint result( lhs );
		result -= rhs;
		return result;
	}

	// op: double - FixedPoint

	inline FixedPoint operator-( double lhs, const FixedPoint& rhs )
	{
		return FixedPoint( lhs ) - rhs;
	}


	//////////////////////////////////////////////////////////////////////////
	// "Multiply" operation on FixedPoint (global)
	//////////////////////////////////////////////////////////////////////////


	// op: FixedPoint * FixedPoint

	inline FixedPoint operator*( const FixedPoint& lhs, const FixedPoint& rhs )
	{
		FixedPoint result( lhs );
		result *= rhs;
		return result;
	}


	/**
	*	int
	*/

	// op: FixedPoint * int

	inline FixedPoint operator*( const FixedPoint& lhs, int rhs )
	{
		FixedPoint result( lhs );
		result *= rhs;
		return result;
	}

	// op: int * FixedPoint

	inline FixedPoint operator*( int lhs, const FixedPoint& rhs )
	{
		return rhs * lhs;
	}
#if INT_ISNOT_LONG
	/**
	*	long
	*/

	// op: FixedPoint * long

	inline FixedPoint operator*( const FixedPoint& lhs, long rhs )
	{
		FixedPoint result( lhs );
		result *= rhs;
		return result;
	}

	// op: long * FixedPoint

	inline FixedPoint operator*( long lhs, const FixedPoint& rhs )
	{
		return rhs * lhs;
	}
#endif //INT_ISNOT_LONG
	/**
	*	float
	*/

	// op: FixedPoint * float

	inline FixedPoint operator*( const FixedPoint& lhs, float rhs )
	{
		FixedPoint result( lhs );
		result *= rhs;
		return result;
	}

	// op: float * FixedPoint

	inline FixedPoint operator*( float lhs, const FixedPoint& rhs )
	{
		return rhs * lhs;
	}


	/**
	*	double
	*/

	// op: FixedPoint * double

	inline FixedPoint operator*( const FixedPoint& lhs, double rhs )
	{
		FixedPoint result( lhs );
		result *= rhs;
		return result;
	}

	// op: double * FixedPoint

	inline FixedPoint operator*( double lhs, const FixedPoint& rhs )
	{
		return rhs * lhs;
	}


	//////////////////////////////////////////////////////////////////////////
	// "Division" operation on FixedPoint (global)
	//////////////////////////////////////////////////////////////////////////


	// op: FixedPoint / FixedPoint

	inline FixedPoint operator/( const FixedPoint& lhs, const FixedPoint& rhs )
	{
#if USE_FLOAT_DIV
		return float(lhs)/float(rhs);
#else
		FixedPoint result( lhs );
		result /= rhs;
		return result;
#endif
	}


	/**
	 *	int
	 */

	// op: FixedPoint / int

	inline FixedPoint operator/( const FixedPoint& lhs, int rhs )
	{
		FixedPoint result( lhs );
		result /= rhs;
		return result;
	}

	// op: int / FixedPoint

	inline FixedPoint operator/( int lhs, const FixedPoint& rhs )
	{
		return FixedPoint( lhs ) / rhs;
	}
#if INT_ISNOT_LONG
	/**
	 *	long
	 */

	// op: FixedPoint / long

	inline FixedPoint operator/( const FixedPoint& lhs, long rhs )
	{
		FixedPoint result( lhs );
		result /= rhs;
		return result;
	}

	// op: long / FixedPoint

	inline FixedPoint operator/( long lhs, const FixedPoint& rhs )
	{
		return FixedPoint( lhs ) / rhs;
	}
#endif //INT_ISNOT_LONG
	/**
	 *	float
	 */

	// op: FixedPoint / float

	inline FixedPoint operator/( const FixedPoint& lhs, float rhs )
	{
#if USE_FLOAT_DIV
		return float(lhs)/rhs;
#else
		FixedPoint result( lhs );
		result /= rhs;
		return result;
#endif
	}

	// op: float / FixedPoint

	inline FixedPoint operator/( float lhs, const FixedPoint& rhs )
	{
#if USE_FLOAT_DIV
		return lhs/float(rhs);
#else
		return FixedPoint( lhs ) / rhs;
#endif
	}


	/**
	 *	double
	 */

	// op: FixedPoint / double

	inline FixedPoint operator/( const FixedPoint& lhs, double rhs )
	{
		FixedPoint result( lhs );
		result /= rhs;
		return result;
	}

	// op: double / FixedPoint

	inline FixedPoint operator/( double lhs, const FixedPoint& rhs )
	{
		return FixedPoint( lhs ) / rhs;
	}


	//////////////////////////////////////////////////////////////////////////
	// Shift operators
	//////////////////////////////////////////////////////////////////////////


	inline FixedPoint operator<<( const FixedPoint& x, int shift )
	{
		FixedPoint result( x );
		result <<= shift;
		return result;
	}


	inline FixedPoint operator>>( const FixedPoint& x, int shift )
	{
		FixedPoint result( x );
		result >>= shift;
		return result;
	}


	//////////////////////////////////////////////////////////////////////////
	// Comparison operators
	//////////////////////////////////////////////////////////////////////////

	// int
		inline bool operator==( int lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) == rhs;	}
		inline bool operator!=( int lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) != rhs;	}
		inline bool operator<( int lhs, const FixedPoint& rhs )						{ return FixedPoint( lhs )  < rhs;	}
		inline bool operator<=( int lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) <= rhs;	}
		inline bool operator>( int lhs, const FixedPoint& rhs )						{ return FixedPoint( lhs )  > rhs;	}
		inline bool operator>=( int lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) >= rhs;	}
#if INT_ISNOT_LONG
	// long
		inline bool operator==( long lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) == rhs;	}
		inline bool operator!=( long lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) != rhs;	}
		inline bool operator<( long lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs )  < rhs;	}
		inline bool operator<=( long lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) <= rhs;	}
		inline bool operator>( long lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs )  > rhs;	}
		inline bool operator>=( long lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) >= rhs;	}
#endif //INT_ISNOT_LONG

	// float
		inline bool operator==( float lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) == rhs;	}
		inline bool operator!=( float lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) != rhs;	}
		inline bool operator<( float lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs )  < rhs;	}
		inline bool operator<=( float lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) <= rhs;	}
		inline bool operator>( float lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs )  > rhs;	}
		inline bool operator>=( float lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) >= rhs;	}

	// double
		inline bool operator==( double lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) == rhs;	}
		inline bool operator!=( double lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) != rhs;	}
		inline bool operator<( double lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs )  < rhs;	}
		inline bool operator<=( double lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) <= rhs;	}
		inline bool operator>( double lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs )  > rhs;	}
		inline bool operator>=( double lhs, const FixedPoint& rhs )					{ return FixedPoint( lhs ) >= rhs;	}


	//////////////////////////////////////////////////////////////////////////
	// Other assignments
	//////////////////////////////////////////////////////////////////////////

	// int
		inline int& operator+=( int& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs + rhs; return lhs; }
		inline int& operator-=( int& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs - rhs; return lhs; }
		inline int& operator*=( int& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs * rhs; return lhs; }
		inline int& operator/=( int& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs / rhs; return lhs; }
#if INT_ISNOT_LONG
	// long
		inline long& operator+=( long& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs + rhs; return lhs; }
		inline long& operator-=( long& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs - rhs; return lhs; }
		inline long& operator*=( long& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs * rhs; return lhs; }
		inline long& operator/=( long& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs / rhs; return lhs; }
#endif //INT_ISNOT_LONG

	// float
		inline float& operator+=( float& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs + rhs; return lhs; }
		inline float& operator-=( float& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs - rhs; return lhs; }
		inline float& operator*=( float& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs * rhs; return lhs; }
#if USE_FLOAT_DIV
		inline float& operator/=( float& lhs, const FixedPoint& rhs)		{ lhs = lhs / (float)rhs; return lhs; }
#else
		inline float& operator/=( float& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs / rhs; return lhs; }
#endif

	// double
		inline double& operator+=( double& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs + rhs; return lhs; }
		inline double& operator-=( double& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs - rhs; return lhs; }
		inline double& operator*=( double& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs * rhs; return lhs; }
		inline double& operator/=( double& lhs, const FixedPoint& rhs)		{ lhs = (FixedPoint)lhs / rhs; return lhs; }



	// Predefines
	typedef FixedPoint fixed_t;

	inline fixed_t max(float a, fixed_t b) { return ((fixed_t(a)>fixed_t(b))?fixed_t(a):fixed_t(b)); }
	inline fixed_t min(float a, fixed_t b) { return ((fixed_t(a)<fixed_t(b))?fixed_t(a):fixed_t(b)); }
	inline fixed_t max(fixed_t a, float b) { return ((fixed_t(a)>fixed_t(b))?fixed_t(a):fixed_t(b)); }
	inline fixed_t min(fixed_t a, float b) { return ((fixed_t(a)<fixed_t(b))?fixed_t(a):fixed_t(b)); }

	inline fixed_t sqrtf(const fixed_t a){ return a.sqrt(); }
	inline fixed_t sqrt(const fixed_t a){ return a.sqrt(); }

#endif	// SEXYFIXEDPOINT_H
