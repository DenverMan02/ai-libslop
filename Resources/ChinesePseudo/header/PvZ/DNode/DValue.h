//
//  DValue.h
//  DCore
//
//  Created by lzjseed on 16/3/11.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DValue_h
#define DValue_h

#include <string>
#include <vector>
#include <unordered_map>
//#include <map>

class DValue;

typedef std::vector<DValue> DValueVector;
typedef std::unordered_map<std::string, DValue> DValueMap;
typedef std::unordered_map<int, DValue> DValueMapIntKey;

extern const DValueVector DValueVectorNull;
extern const DValueMap DValueMapNull;
extern const DValueMapIntKey DValueMapIntKeyNull;

class DValue
{
public:
    static const DValue Null;
    
    DValue();
    
    explicit DValue(unsigned char v);
    
    explicit DValue(int v);
    
    explicit DValue(unsigned long long v);
    
    explicit DValue(float v);
    
    explicit DValue(double v);
    
    explicit DValue(bool v);

    explicit DValue(const char* v);
    
    explicit DValue(const std::string& v);
    
    explicit DValue(const DValueVector& v);
   
    explicit DValue(DValueVector&& v);
    
    explicit DValue(const DValueMap& v);
    
    explicit DValue(DValueMap&& v);
    
    explicit DValue(const DValueMapIntKey& v);
    
    explicit DValue(DValueMapIntKey&& v);
    
    DValue(const DValue& other);
    
    DValue(DValue&& other);
    
    ~DValue();

    DValue& operator= (const DValue& other);

    DValue& operator= (DValue&& other);
    
    DValue& operator= (unsigned char v);

    DValue& operator= (int v);
    
    DValue& operator= (unsigned long long v);

    DValue& operator= (float v);

    DValue& operator= (double v);

    DValue& operator= (bool v);

    DValue& operator= (const char* v);

    DValue& operator= (const std::string& v);
    
    DValue& operator= (const DValueVector& v);

    DValue& operator= (DValueVector&& v);
    
    DValue& operator= (const DValueMap& v);

    DValue& operator= (DValueMap&& v);

    DValue& operator= (const DValueMapIntKey& v);

    DValue& operator= (DValueMapIntKey&& v);
    
    bool operator!= (const DValue& v);
    
    bool operator!= (const DValue& v) const;

    bool operator== (const DValue& v);

    bool operator== (const DValue& v) const;
    
  
    unsigned char asByte() const;
  
    int asInt() const;
    
    unsigned long long asUInt64() const;
    
    float asFloat() const;
  
    double asDouble() const;
  
    bool asBool() const;
  
    std::string asString() const;
    
    DValueVector& asDValueVector();
    
    const DValueVector& asDValueVector() const;
    
    DValueMap& asDValueMap();
    
    const DValueMap& asDValueMap() const;
    
    
    DValueMapIntKey& asIntKeyMap();
    
    const DValueMapIntKey& asIntKeyMap() const;
    
    
    inline bool isNull() const { return _type == Type::NONE; }
    inline bool isByte() const { return _type == Type::BYTE; }
    inline bool isInteger() const { return _type == Type::INTEGER; }
    inline bool isUInt64() const { return _type == Type::INTEGER64; }
    inline bool isFloat() const { return _type == Type::FLOAT; }
    inline bool isDouble() const { return _type == Type::DOUBLE; }
    inline bool isBool() const { return _type == Type::BOOLEAN; }
    inline bool isString() const { return _type == Type::STRING; }
    inline bool isDValueVector() const { return _type == Type::VECTOR; }
    inline bool isDValueMap() const { return _type == Type::MAP; }
    inline bool isIntKeyMap() const { return _type == Type::INT_KEY_MAP; }
    
    enum class Type
    {
        /// no DValue is wrapped, an empty DValue
        NONE = 0,
        /// wrap byte
        BYTE,
        /// wrap integer
        INTEGER,
        /// wrap float
        FLOAT,
        /// wrap double
        DOUBLE,
        /// wrap int64
        INTEGER64,
        /// wrap bool
        BOOLEAN,
        /// wrap string
        STRING,
        /// wrap vector
        VECTOR,
        /// wrap DValueMap
        MAP,
        /// wrap DValueMapIntKey
        INT_KEY_MAP
    };
    
    
    inline Type getType() const { return _type; }
    
    
    std::string getDescription() const;
    
private:
    void clear();
    void reset(Type type);
    
    union
    {
        unsigned char byteVal;
        int intVal;
        float floatVal;
        double doubleVal;
        bool boolVal;
        unsigned long long int64Val;
        
        std::string* strVal;
        DValueVector* vectorVal;
        DValueMap* mapVal;
        DValueMapIntKey* intKeyMapVal;
    }_field;
    
    Type _type;
};

#endif 