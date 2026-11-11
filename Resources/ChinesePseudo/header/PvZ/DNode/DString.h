//
//  DString.h
//  DCore
//
//  Created by lzjseed on 16/2/19.
//

#ifndef DString_h
#define DString_h

#include <vector>

class DStringBlock;

class DString
{
public:
    enum DTimeFormat
    {
        FORMAT_HMS = 0, //h:m:s
        FORMAT_MS,      //m:s
        FORMAT_S,       //s
        FORMAT_DHMS,    //d:h:m:s
    };
    
    static const ssize_t npos = -1;
    
public:
    
    DString();
    DString(const float v);
    DString(const int v);
    DString(const long src);
    DString(const double src);
    DString(const long long src);
    DString(const char * src);
    DString(const char * src,size_t len);
    DString(char src);
    DString(DString* s);
    DString(const DString &s);
    DString(DString &&s);
    DString(const std::string& s);
    //DString(bool s);
    
    virtual ~DString();
    
    static DString Format(const char * _format,...);
    static DString CreateWithTime(unsigned long long time,DTimeFormat format = FORMAT_HMS);
    static DString Join(const std::vector<DString>& strs,const char* code);
    
    
    DString& format(const char * _format,...);
    
    bool compare(const DString& src)const;
    bool compareWithNoCase(const DString& src)const;
    
    DString& operator = (const std::string& src);
    DString& operator = (std::string&& src);
    
    //DString& operator = (bool s);
    DString& operator = (const int src);
    DString& operator = (const float src);
    DString& operator = (const long src);
    DString& operator = (const double src);
    DString& operator = (const long long src);
    
    DString& operator = (char * src);
    DString& operator = (const char * src);
    DString& operator = (const DString& s);
    DString& operator = (DString&& s);
    
    const char operator [] (int index)const;
    char& operator [] (int index);
    
    bool operator == (char * src)const;
    bool operator == (const char * src)const;
    bool operator == (const DString& s)const;
    bool operator == (const std::string& s)const;
    
    bool operator != (char * src)const;
    bool operator != (const char * src)const;
    bool operator != (const DString& s)const;
    bool operator != (const std::string& s)const;
    
    bool operator < (char * src)const;
    bool operator < (const char * src)const;
    bool operator < (const DString& src)const;
    bool operator < (const std::string& s)const;
    
    bool operator <= (char * src)const;
    bool operator <= (const char * src)const;
    bool operator <= (const DString& src)const;
    bool operator <= (const std::string& s)const;
    
    bool operator > (char * src)const;
    bool operator > (const char * src)const;
    bool operator > (const DString& src)const;
    bool operator > (const std::string& s)const;
    
    bool operator >= (char * src)const;
    bool operator >= (const char * src)const;
    bool operator >= (const DString& src)const;
    bool operator >= (const std::string& s)const;
    
    DString& operator += (const char * src);
    DString& operator += (char * src);
    DString& operator += (char src);
    DString& operator += (DString* s);
    DString& operator += (const DString& s);
    DString& operator += (DString&& s);
    DString& operator += (const std::string& s);
    DString& operator += (const int s);
    DString& operator += (const float s);
    DString& operator += (const double s);
    DString& operator += (const long s);
    DString& operator += (const long long s);
    
    DString& operator -= (const char * src);
    DString& operator -= (char * src);
    DString& operator -= (char src);
    DString& operator -= (DString* s);
    DString& operator -= (const DString& s);
    DString& operator -= (const std::string& s);
    
    operator int() const;
    operator float() const;
    operator char*();
    operator const char*() const;
    operator std::string() const;
    operator long() const;
    operator long long() const;
    
    /**
     * 通过时间值初始化
     * @param[in] time       秒数
     * @param[in] format     时间格式
     * @return[out] DString& 自身
     **/
    DString& setWithTime(unsigned long long time,DTimeFormat format = FORMAT_HMS);
    
    
    /**
     * 用连接符拼接数组字符串成为新字符串
     * @param[in] strs    字符串数组
     * @param[in] code    连接符
     * @return[out] DString& 自身
     **/
    DString& join(const std::vector<DString>& strs,const char* code);
    /**
     * 添加字串
     * @param[in] src  字串
     * @return[out] DString& 自身
    **/
    DString& addString(const char * src);
    /**
     * 添加指定长度的子串
     * @param[in] src  字串
     * @param[in] len  字串长度
     * @return[out] DString& 自身
     **/
    DString& addString(const char * src,size_t len);
    /**
     * 添加字符
     * @param[in] src  字符
     * @return[out] DString& 自身
     **/
    DString& addChar(char src);
    /**
     * 添加字串
     * @param[in] s  字串类
     * @return[out] DString& 自身
     **/
    DString& addDString(DString* s);
    DString& addDString(const DString &s);
    
    /**
     *	从左往右截取指定范围的子串
     * @param[in] start  目标起点
     * @param[in] end    目标终点
     * @return[out] DString 子串
     **/
    DString subString(ssize_t start,ssize_t end) const;
    /**
     *	从左往右截取start开始到底的子串
     * @param[in] start  目标起点
     * @return[out] DString 子串
     **/
    DString subString(ssize_t start) const;
    /**
     *	从右往左截取start开始到头的子串
     * @param[in] start  目标起点
     * @param[in] end    目标终点
     * @return[out] DString 子串
     **/
    DString subStringLeft(ssize_t start) const;
    /**
     *	从右往左截取指定范围的子串
     * @param[in] start  目标起点
     * @param[in] end    目标终点
     * @return[out] DString 子串
     **/
    DString subStringLeft(ssize_t start,ssize_t end) const;
    /**
     *	子串全部大写
     * @return[out] DString 大写子串
     **/
    DString makeUpper()const;
    /**
     *	子串全部小写
     * @return[out] DString 小写子串
     **/
    DString makeLower()const;
    /**
     *	查找子串
     * @param[in] start  原串的起点
     * @param[in] sub    查找的子串
     * @return[out] int 子串在原始串中的起始位置,-1表示未找到
     **/
    ssize_t	findString(ssize_t start,const char* sub) const;
    ssize_t	findString(const char* sub) const;
    
    ssize_t	findNumber(ssize_t start = npos) const;
    
    /**
     *	反向查找子串
     * @param[in] start  原串的起点
     * @param[in] sub    查找的子串
     * @return[out] int 子串在原始串中的起始位置,-1表示未找到
     **/
    ssize_t rfindString(ssize_t start,const char* sub) const;
    ssize_t rfindString(const char* sub) const;
    
    /**
     *	替换匹配串
     * @param[in] oldStr  原串中需要被替换的字串
     * @param[in] newStr  代替字串
     * @return[out] DString 替换后的新串
     **/
    DString replace(const char* oldStr,const char* newStr);
    
    /**
     *	剔除前后的空格
     * @return[out] DString 格式化后的新串
     **/
    DString trim()const;
    
    /**
     *	在目录串中截取文件名，不带后缀名
     * @return[out] DString 文件名
     **/
    DString getFileNameString()const;
    
    /**
     *	在目录串中截取文件名，带后缀名
     * @return[out] DString 文件名
     **/
    DString getFileExtNameString()const;
    
    /**
     *	在目录串中截取目录名
     * @param[in] retainSign  是否保留斜杠
     * @return[out] DString 文件名
     **/
    DString getDirNameString(bool retainSign = false)const;
    
    /**
     *	在目录串中截取文件后缀名
     * @return[out] DString 后缀名
     **/
    DString getFileExtString()const;
    
    /**
     *	字符串是十六进制表示的转换成整数
     * @return[out] int 整数
     **/
    int  toHex()const;
    
    /**
     *	转换成整数
     * @return[out] int 整数
     **/
    int	  toInt() const;
    /**
     *	转换成浮点数
     * @return[out] float 浮点数
     **/
    float toFloat() const;
    /**
     *	转换成双精度浮点数
     * @return[out] double 浮点数
     **/
    double toDouble() const;
    
    /**
     *	转换成长整形
     * @return[out] long 长整形
     **/
    long toLong()const;
    
    /**
     *	转换成64位整形
     * @return[out] long long 64位整形
     **/
    long long toInt64()const;
    
    /**
     *	判断是否为空串
     * @return[out] bool 是否为空
     **/
    bool empty() const;
    /**
     *	获得串的长度
     * @return[out] size_t 串长
     **/
    size_t size() const;
    
    /**
     *	获得字串头指针
     * @return[out] const char * 字符串指针
     **/
    const char * c_str()const;
    /**
     *	获得字串头指针
     * @return[out] char * 字符串指针
     **/
    char * c_str();
    
    /**
     *	获得字符
     * @param[in] index         字符的索引
     * @return[out] const char  字符
     **/
    inline const char getChar(int index)const;
    
    /**
     *	获得字符
     * @param[in] index         字符的索引
     * @return[out] char&  字符
     **/
    inline char& getChar(int index);
    
    /**
     *	清空字符串
     **/
    void clear();
    
    /**
     *	用数组方式分割原字符串
     * @param[in] const char*           分隔符
     * @param[in] unsigned int          分割出来的最大数量,(number = 0)表示没有限制
     * @return[out] vector<DString>   子串数组
     **/
    std::vector<DString> split(const char* code,size_t number = 0) const;
    
    friend DString operator+(const char* pch1, const DString& str2);
    friend DString operator+(char ch1, const DString& str2);
    friend DString operator+(const DString& pch1, const DString& str2);
    friend DString operator+(const DString& pch1, const char* str2);
    friend DString operator+(const DString& ch1,char str2);
    
    friend DString operator+(const char* pch1, DString&& str2);
    friend DString operator+(char ch1, DString&& str2);
    friend DString operator+(DString&& pch1, const char* str2);
    friend DString operator+(DString&& ch1, char str2);
    friend DString operator+(DString&& pch1, DString&& str2);
    friend DString operator+(const DString& pch1, DString&& str2);
    friend DString operator+(DString&& pch1, const DString& str2);
    
    friend DString operator+(const DString& pch1, const std::string& str2);
    friend DString operator+(const std::string& pch1, const DString& str2);
    friend DString operator+(DString&& pch1, const std::string& str2);
    friend DString operator+(const std::string& pch1, DString&& str2);
    
    friend DString operator+(DString&& pch1, std::string&& str2);
    friend DString operator+(std::string&& pch1, DString&& str2);
    friend DString operator+(const DString& pch1, std::string&& str2);
    friend DString operator+(std::string&& pch1, const DString& str2);
    
private:
    DStringBlock* str;
    void newString(const char * src);
    void newString(const char * src,size_t newLen);
    bool camp(const char * src)const;
    bool campn(const char * src)const;
    
private:
    inline void initWithFormatAndValist(const char* format, va_list list);
    inline DStringBlock* copy()const;
};

namespace std {
    template<>
    struct hash<DString>
    {
        static hash<string> m_hasher;
        size_t operator() (const DString& i_name) const
        {
            return m_hasher(i_name.c_str());
        }
    };
}

inline ssize_t DString::findString(const char* sub) const
{
    return findString(npos,sub);
}

inline ssize_t DString::rfindString(const char* sub) const
{
    return rfindString(npos,sub);
}

DString operator+(const DString& pch1, const DString& str2);
DString operator+(const char* pch1, const DString& str2);
DString operator+(char ch1, const DString& str2);
DString operator+(const DString& pch1, const char* str2);
DString operator+(const DString& ch1,char str2);
DString operator+(const char* pch1, DString&& str2);
DString operator+(char ch1, DString&& str2);
DString operator+(DString&& pch1, const char* str2);
DString operator+(DString&& ch1, char str2);
DString operator+(DString&& pch1, DString&& str2);
DString operator+(const DString& pch1, DString&& str2);
DString operator+(DString&& pch1, const DString& str2);

DString operator+(const DString& pch1, const std::string& str2);
DString operator+(const std::string& pch1, const DString& str2);
DString operator+(DString&& pch1, const std::string& str2);
DString operator+(const std::string& pch1, DString&& str2);

DString operator+(DString&& pch1, std::string&& str2);
DString operator+(std::string&& pch1, DString&& str2);
DString operator+(const DString& pch1, std::string&& str2);
DString operator+(std::string&& pch1, const DString& str2);

/**
 *	输入串剔除前后的空格，返回新串和长度
 **/
size_t trim(char* node);

size_t d_utf16_to_gb_len(const unsigned short* str);


#endif
