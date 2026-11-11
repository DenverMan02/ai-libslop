#ifndef __BIGINT_H__
#define __BIGINT_H__

#include "Common.h"
#include <ostream>

typedef std::vector<char> CharVector;

class BigInt
{
public:	
	bool					mNeg;

	ushort*					mWords;	
	int						mNumWords;
	int						mAllocWords;

protected:
	void					Resize(int theNewSize);
	void					DoubleSize();
	void					Trim();
	bool					IsNegative() const;	
	void					SetZero();
	bool					IsEven();
	bool					IsOdd();
	int						NumWords() const;	
	ushort					HighWord() const;
	ushort					GetWord(int theWordIdx) const;
	void					SetWord(int theWordIdx, ushort theValue);	

public:
	BigInt();
	BigInt(int theInt);
	BigInt(int64 theInt);
	BigInt(const BigInt& theBigInt);
	BigInt(const std::string& theString);
	virtual ~BigInt();

	static BigInt			RandNum(int theNumBits);

	bool					operator==(const BigInt& theBigInt) const;
	bool					operator!=(const BigInt& theBigInt) const;
	bool					operator<(const BigInt& theBigInt) const;
	bool					operator<=(const BigInt& theBigInt) const;
	bool					operator>(const BigInt& theBigInt) const;
	bool					operator>=(const BigInt& theBigInt) const;

	BigInt					operator-() const;

	BigInt&					operator=(const BigInt& theBigInt);
	BigInt&					operator/=(const BigInt& theBigInt);
	BigInt&					operator*=(const BigInt& theBigInt);
	BigInt&					operator+=(const BigInt& theBigInt);
	BigInt&					operator-=(const BigInt& theBigInt);
	BigInt&					operator%=(const BigInt& theBigInt);
	BigInt&					operator<<=(int theNumBits);
	BigInt&					operator>>=(int theNumBits);	
	BigInt&					operator|=(const BigInt& theBigInt);
	BigInt&					operator&=(const BigInt& theBigInt);
	BigInt&					operator++();
	BigInt					operator++(int);

	BigInt					operator+(const BigInt& theBigInt) const;
	BigInt					operator-(const BigInt& theBigInt) const;
	BigInt					operator/(const BigInt& theBigInt) const;
	BigInt					operator*(const BigInt& theBigInt) const;
	BigInt					operator%(const BigInt& theBigInt) const;
	BigInt					operator<<(int theNumBits) const;
	BigInt					operator>>(int theNumBits) const;	
	BigInt					operator|(const BigInt& theBigInt) const;
	BigInt					operator&(const BigInt& theBigInt) const;
	
	BigInt&					ShiftLeft(int theNumBits);
	BigInt&					ShiftRight(int theNumBits);
	void					Divide(const BigInt& theDivisor, BigInt& theQuotient, BigInt& theRemaindier) const;	

	int						NumBits() const;
	bool					IsBitSet(int theBitNum) const;	
	void					SetBit(int theBitNum);
	
	BigInt					Pow(int thePower) const;
	BigInt					ModPow(const BigInt& thePower, const BigInt& theMod) const;
	BigInt					InvMod(const BigInt& theModulus);
	BigInt					Gcd(const BigInt& theBigInt);
	bool					IsPrime() const;

	int						ToInt() const;
	std::string				ToHex() const;
};

std::ostream& operator<<(std::ostream& ostr, const BigInt& theBigInt);

#endif //__BIGINT_H__
