//
//  DStream.h
//  DCore
//
//  Created by lzjseed on 16/3/11.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

//use UTF-8

#ifndef DStream_h
#define DStream_h

#include "DString.h"

#define D_HOST_IS_BIG_ENDIAN (bool)(*(unsigned short *)"\0\xff" < 0x100)
#define D_SWAP32(i)  ((i & 0x000000ff) << 24 | (i & 0x0000ff00) << 8 | (i & 0x00ff0000) >> 8 | (i & 0xff000000) >> 24)
#define D_SWAP16(i)  ((i & 0x00ff) << 8 | (i &0xff00) >> 8)
#define D_SWAP_INT32_LITTLE_TO_HOST(i) ((D_HOST_IS_BIG_ENDIAN == true)? D_SWAP32(i) : (i) )
#define D_SWAP_INT16_LITTLE_TO_HOST(i) ((D_HOST_IS_BIG_ENDIAN == true)? D_SWAP16(i) : (i) )
#define D_SWAP_INT32_BIG_TO_HOST(i)    ((D_HOST_IS_BIG_ENDIAN == true)? (i) : D_SWAP32(i) )
#define D_SWAP_INT16_BIG_TO_HOST(i)    ((D_HOST_IS_BIG_ENDIAN == true)? (i):  D_SWAP16(i) )

class  DInputStream
{
public:
    DInputStream(bool isBigEndian = false);
    ~DInputStream();
    /** 加载并检查数据是否正确
     * @param [in]  const char* 标示符
     * @return[out] bool 加载是否成功
     */
    bool       loadAndCheckData(const std::string& header = "DSE");
    /** 读字节
     * @return[out] unsigned char 数据
     */
    unsigned char readByte();
    /** 读整形
     * @return[out] int 数据
     */
    int        readInt();
    /** 读短整形
     * @return[out] short 数据
     */
    short      readShort();
    /** 读浮点数
     * @return[out] float 数据
     */
    float      readFloat();
    /** 读双精度浮点数
     * @return[out] double 数据
     */
    double     readDouble();
    /** 读64位长整形
     * @return[out] long long 数据
     */
    long long  readLongLong();
    /** 读布尔型
     * @return[out] bool 数据
     */
    bool       readBoolean();
    /** 读字符串
     * @return[out] std::string 数据
     */
    std::string   readString();
    
    DString   readString(size_t length);
    
    /** 读buffer
     * @param[in] void* 流的指针
     * @param[in] unsigned long 流的长度
     * @return[out] size_t 真正的长度
     */
    size_t       readBuffer(void* buff,size_t length);
    
    /** 读一行
     * @return[out] std::string 数据
     */
    std::string  readLine();
    
    /** 设置否是用大端方式读取
     * @param[in] bool 是否是大端
     */
    inline void  setUsDigEndian(bool _isBigEndian)
    {
        this->isBigEndian = _isBigEndian;
        if(D_HOST_IS_BIG_ENDIAN == _isBigEndian)
        {
            needToHost = false;
        }
        else
        {
            needToHost = true;
        }
    }
    /** 返回当前读取方式是否是大端
     * @return[out] bool 是否是大端
     */
    inline bool       getIsBigEndian()const {return isBigEndian;}
    
    /** 通过数据流创建并初始化
     * @param[in] const std::string 字符串
     * @return[out] bool 是否成功
     */
    bool readFromString(const std::string& str);
    
    /** 通过数据流创建并初始化
     * @param[in] unsigned char * 流指针
     * @param[in] unsigned long 长度
     * @return[out] bool 是否成功
     */
    bool readFromBuffer(const unsigned char* buffer,size_t length);
    /** 打开该文件并初始化
     * @param[in] const char * 文件名
     * @return[out] bool 是否成功
     */
    bool readFromFile(const std::string& fileName);
    /** 通过全局路径打开该文件并初始化
     * @param[in] const char * 文件名
     * @return[out] bool 是否成功
     */
    bool readFromFullPathFile(const std::string& fullPathFileName);
    /** 从可写目录中打开该文件并初始化
     * @param[in] const char * 文件名
     * @return[out] bool 是否成功
     */
    bool readFromWritabelPathFile(const std::string& fileName);
    /** 获取数据流长度
     * @return[out] size_t 长度
     */
    inline size_t  getLength()const {return length;}
    
    /** 返回数据流指针
     * @return[out] const void* 流指针
     */
    inline const void* getBuff()const{return pBuff;}
    
    /** 设置偏移
     * @return[out] bool 是否成功
     */
    bool  seek(size_t offset);
private:
    std::string    readHeader(size_t size);
    bool           decodeVarInt(unsigned long long *dest);
private:
    bool           needToHost;
    bool           isBigEndian;
    unsigned char* pBuff;
    size_t         pos;
    size_t         length;
};

class  DOutputStream
{
public:
    DOutputStream(bool isBigEndian = false);
    ~DOutputStream();
    
    /** 写字节流
     * @param[in] unsigned char* 字节流指针
     * @param[in] unsigned int 长度
     */
    void writDytes(unsigned char * bytes,size_t size);
    /** 写字节
     * @param[in] unsigned char 数据
     */
    void writDyte(unsigned char value);
    /** 写整形
     * @param[in] int 数据
     */
    void writeInt(int value);
    /** 写短整形
     * @param[in] short 数据
     */
    void writeShort(short value);
    /** 写浮点数
     * @param[in] float 数据
     */
    void writeFloat(float value);
    /** 写双精度浮点数
     * @param[in] double 数据
     */
    void writeDouble(double value);
    /** 写64位整数
     * @param[in] long long 数据
     */
    void writeLongLong(long long value);
    /** 写布尔值
     * @param[in] bool 数据
     */
    void writDoolean(bool value);
    /** 写字符串
     * @param[in] const char* 数据
     */
    void writeString(const char* str);
    /** 写入文件
     * @param[in] const char* 文件名
     * @param[in] const char* 头标示符
     * @param[in] bool 是否加密
     */
    void writeToFile(const char * fileName,const char * header,bool encode);
    /** 设置否是用大端方式读取
     * @param[in] bool 是否是大端
     */
    inline void setUsDigEndian(bool _isBigEndian)
    {
        this->isBigEndian = _isBigEndian;
        if(D_HOST_IS_BIG_ENDIAN == _isBigEndian)
        {
            needToHost = false;
        }
        else
        {
            needToHost = true;
        }
    }
    /** 返回当前读取方式是否是大端
     * @return[out] bool 是否是大端
     */
    inline bool getIsBigEndian()const {return isBigEndian;}
    /** 返回数据流指针
     * @return[out] const void* 流指针
     */
    const void* getBuff()const;
    /** 返回数据流长度
     * @return[out] unsigned long 流长度
     */
    ssize_t getLength()const;
    
private:
    void resetMemory(unsigned long size);
	void encodeVarint(unsigned long long value);
private:
    bool           needToHost;
    bool           isBigEndian;
    unsigned char* pBuff;
    unsigned long  pos;
    ssize_t        length;
};

class DStreamBuffer
{
public:
    DStreamBuffer(const uint64_t lBuffLen);
    virtual ~DStreamBuffer();
    void addDatas(const char* pData,const uint64_t lDataLen);
    void reset();
    void popDatas(const uint64_t size);
    
    inline char*     getBuff()const {return m_pBuff;}
    inline uint64_t  getLength()const {return m_lLimited;}
private:
    char*     m_pBuff;
    uint64_t  m_lCapacity;
    uint64_t  m_lLimited;
};

//需要进行写文件的时候，可以用这个类进行写入
class  DWriteFile
{
public:
    DWriteFile();
    ~DWriteFile();
    /** 初始化
     * @param [in]  const char* 文件名
     * @param [in]  bool （wb+ 还是 ab+）
     * @return[out] bool 初始化是否成功
     */
    bool init(const char* fileName,bool bAppend = false,bool force = false);
    
    
    /** 写入字符串
     * @param [in]  const DCString& 字符串
     * @return[out] size_t 实际写入的长度
     */
    size_t writeString(const std::string& str);
    /** 写入字节流
     * @param [in]  void* 流的指针
     * @param [in]  size_t 长度
     * @return[out] size_t 实际写入的长度
     */
    size_t writeBytes(const void* bytes,size_t size);
    size_t writeBytes(const void* bytes,size_t size,size_t nmemb);
    /** 写入字节
     * @param [in]  unsigned char 字节
     * @return[out] size_t 实际写入的长度
     */
    size_t writeBytes(unsigned char byte);
    /** 文件长度
     * @return[out] size_t 文件长度
     */
    inline size_t getLength()const {return size;}
    
    void close();
    
    const std::string& getFileName()const{return m_fileName;}
    
private:
    FILE* file;
    size_t size;
    std::string m_fileName;
};

class DFileHandler
{
public:
	DFileHandler();
    virtual ~DFileHandler();
    
    bool initWithString(const std::string& str,bool sercet = false);
    
	bool initWithFile(const std::string& fileName,bool sercet = false);
    
    bool initWithWritablePath(const std::string& fileName,bool sercet = false);
    
    bool writeToFile(const std::string& fileName,bool sercet = false,bool force = false);
    
    bool copyToFile(const std::string& fileName);
    
    bool reload();
    
	void close();
    
    bool write();
    
    bool flush();
    
    void setSercetType(int type);
    
    void removeAllItems();
    
    bool isModify();
    
    const std::string& getFileName();
    
    
    virtual bool isEmpty();

protected:
    
    virtual void clear() = 0;
    virtual void readBuff(const char *buf) = 0;
    virtual void writeBuff(DStreamBuffer& stream) = 0;
    
protected:
    bool         read();
	
protected:
	bool		 m_bModify;
	bool		 m_bSercet;
    bool         m_bWritable;
    bool         m_bBuffer;
    int          m_sercetType;
    std::string	 m_strName;
};

class DFinder
{
public:
    //创建文件夹
    static bool createDirectory(const std::string& path);
    //删除文件
    static bool removeFile(const std::string& path);
};

unsigned char* getAESKey();

void sercet(unsigned char* pBuff,unsigned long len,int type);

void unsercet(unsigned char* pBuff,unsigned long len,int type);

#endif