
#ifndef __LAWN_KEY_FIELD_H__
#define __LAWN_KEY_FIELD_H__

class LawnKeyField;

#define MAGIC_SEED_NUM (13)
#define DATA_WIDTH (32)

typedef union U_signed_unsigned
{
	uint32 long_;
	int32 int_;
} U_signed_unsigned;


class LawnKeyField
{
public:
	uint32 data;
    uint32 seednum;// = 13;//magic seed num.
//    int32 DATA_WIDTH;
	LawnKeyField()
	{
		data = 0;
		seednum = MAGIC_SEED_NUM;
//        DATA_WIDTH = sizeof(U_signed_unsigned) * 8;
	}

	LawnKeyField(int32 value)
	{
		data = 0;
		seednum = MAGIC_SEED_NUM;
//        DATA_WIDTH = sizeof(U_signed_unsigned) * 8;
        
		U_signed_unsigned u;
		u.int_ = value;
		data = encode(u.long_);
	}
	LawnKeyField(int64 value)

	{
		data = 0;
		seednum = MAGIC_SEED_NUM;
//        DATA_WIDTH = sizeof(U_signed_unsigned) * 8;

		U_signed_unsigned u;
		u.int_ = static_cast<int> (value);
		data = encode(u.long_);

	}
    inline void setseed(uint32 aseed)
    {
        U_signed_unsigned u;
        u.long_ = decode(data);
        seednum = aseed;
        data = encode(u.long_);
    }
    
    inline void updateToAug05LawnKey()
    {
        U_signed_unsigned u;
        u.long_ = (data >> MAGIC_SEED_NUM) | (data << (DATA_WIDTH - MAGIC_SEED_NUM));
        this->data = encode(u.long_);
    }
    
    inline uint32 encode(uint32 value) const
    {
        value ^= seednum;
        return (value << (seednum % DATA_WIDTH)) | (value >> (DATA_WIDTH - (seednum % DATA_WIDTH)));
    }
    
    inline uint32 decode(uint32 value) const
    {
        value = (value >> (seednum % DATA_WIDTH)) | (value << (DATA_WIDTH - (seednum % DATA_WIDTH)));
        value ^= seednum;
        return value;
    }

	inline LawnKeyField& operator= (const LawnKeyField& value)
	{
		data = value.data;

		return *this;
	}

	inline LawnKeyField& operator= (int32 value)
	{
		U_signed_unsigned u;
		u.int_ = value;
		data = encode(u.long_);

		return *this;
	}

	inline int32 operator +(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		u.int_ += value;
		return u.int_;
	}

	inline int32 operator -(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		u.int_ -= value;
		return u.int_;
	}

	inline int32 operator *(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		u.int_ *= value;
		return u.int_;
	}

	inline int32 operator /(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		u.int_ /= value;
		return u.int_;
	}

	inline LawnKeyField& operator +=(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		u.int_ += value;
		data = encode(u.long_);

		return *this;
	}

	inline LawnKeyField& operator -=(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		u.int_ -= value;
		data = encode(u.long_);

		return *this;
	}

	inline LawnKeyField& operator *=(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		u.int_ *= value;
		data = encode(u.long_);

		return *this;
	}

	inline LawnKeyField& operator /=(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		u.int_ /= value;
		data = encode(u.long_);

		return *this;
	}

	inline bool operator <(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		return (u.int_ < value);
	}

	inline bool operator >(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		return (u.int_ > value);
	}

	inline bool operator <=(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		return (u.int_ <= value);
	}

	inline bool operator >=(int32 value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		return (u.int_ >= value);
	}

	inline bool operator <(const LawnKeyField& value)
	{
		U_signed_unsigned u1;
		u1.long_ = decode(data);
		U_signed_unsigned u2;
		u2.long_ = decode(value.data);
		return (u1.int_ < u2.int_);
	}

	inline bool operator >(const LawnKeyField& value)
	{
		U_signed_unsigned u1;
		u1.long_ = decode(data);
		U_signed_unsigned u2;
		u2.long_ = decode(value.data);
		return (u1.int_ > u2.int_);
	}

	inline bool operator <=(const LawnKeyField& value)
	{
		U_signed_unsigned u1;
		u1.long_ = decode(data);
		U_signed_unsigned u2;
		u2.long_ = decode(value.data);
		return (u1.int_ <= u2.int_);
	}

	inline bool operator >=(const LawnKeyField& value)
	{
		U_signed_unsigned u1;
		u1.long_ = decode(data);
		U_signed_unsigned u2;
		u2.long_ = decode(value.data);
		return (u1.int_ >= u2.int_);
	}
    

	inline LawnKeyField& operator *(float value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		u.int_ = (int)(((float)u.int_)*value);
		data = encode(u.long_);

		return *this;
	}

	inline LawnKeyField& operator *(double value)
	{
		U_signed_unsigned u;
		u.long_ = decode(data);
		u.int_ = (int)(((double)u.int_)*value);
		data = encode(u.long_);

		return *this;
	}

	operator int32()
	{
		U_signed_unsigned u1;
		u1.long_ = decode(data);
		return u1.int_;
	} 


	operator int32() const
	{
		U_signed_unsigned u1;
		u1.long_ = decode(data);
		return u1.int_;
	}
};



#endif //__LAWN_KEY_FIELD_H__
