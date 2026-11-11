//
//  DIniFile.h
//  DCore
//
//  Created by lzjseed on 16/3/11.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//


#ifndef DIniFile_h
#define DIniFile_h

#include "DStream.h"
#include <map>


class DIniFile;

class DIniItem
{
public:
	DIniItem() = default;
    DIniItem(const std::string& strValue):m_strValue(strValue){}
    virtual~DIniItem() = default;
    inline const std::string& getValue()const{return m_strValue;}
    std::string m_strValue;
};

class DIniField
{
public:
	DIniField() = default;
	virtual~DIniField() = default;
public:
	void addItem(const std::string& m_strName);
	void addItem(const std::string& strName,const std::string& strValue);
	
    void addItem(const std::string& strName,int strValue);
    void addItemBool(const std::string& strName,bool strValue);
    void addItem(const std::string& strName,float strValue);
    
    void removeItem(const std::string& strName);
    
    const std::string getItem(const std::string& strName,const std::string& defaultValue = "");
    const int   getItemInt(const std::string& strName,int defaultValue = 0);
    const bool  getItemBool(const std::string& strName,bool defaultValue = false);
    const float getItemFloat(const std::string& strName,float defaultValue = 0.0f);

    std::map<std::string,DIniItem>& getItemsList();
    
private:
    void addItemInner(const std::string& strName,const std::string& strValue);
	
private:
    DIniFile*   m_pObserver;
    std::map<std::string,DIniItem> m_itemList;
    
    friend class DIniFile;
};

class DIniFile:public DFileHandler
{
public:
    virtual bool isEmpty() override;
    
    virtual ~DIniFile();
    
public:
    static const std::string getString(const std::string& fileName,bool isWriteable,const std::string& fieldName,const std::string& itemName,const std::string& valueName = "");
    static int getInt(const std::string& fileName,bool isWriteable,const std::string& fieldName,const std::string& itemName,int valueName = 0);
    static float getFloat(const std::string& fileName,bool isWriteable,const std::string& fieldName,const std::string& itemName,float valueName = 0.0f);
    
public:
	void	 setItem(const std::string& fieldName,const std::string &itemName,const std::string &valueName);
	void	 setItem(const std::string& fieldName,const std::string &itemName, int	valueName);
    void	 setItemBool(const std::string& fieldName,const std::string &itemName, bool	valueName);
	void	 setItem(const std::string& fieldName,const std::string &itemName, float valueName);
    
	const std::string getItem(const std::string& fieldName,const std::string &itemName,const std::string &defaultItemName = "");
	const int   getItemInt(const std::string& fieldName,const std::string &itemName, int defaultValue = 0);
	const float	getItemFloat(const std::string& fieldName,const std::string &itemName, float defaultValue = 0.0f);
    const bool  getItemBool(const std::string& fieldName,const std::string& strName, bool defaultValue = false);
    
    void     removeItem(const std::string& fieldName,const std::string& itemName);
    void     removeField(const std::string& fieldName);
    void     cleanField(const std::string& fieldName);     //不同于removeField，仅仅清除field下的所有items，不清除field
    
    DIniField* getField(const std::string& fieldName);
    DIniField* addField(const std::string& fieldName);
    DIniField* copyField(const std::string& newfieldName,const std::string& fieldName);
    bool        renameField(const std::string& newfieldName,const std::string& fieldName);
    
    std::map<std::string, DIniField>& getFieldsList();
    
private:
    
	DIniField*  addFieldInner(const std::string& strName);
protected:
    
    virtual void clear() override;
	virtual void readBuff(const char *buf) override;
	virtual void writeBuff(DStreamBuffer& stream) override;

private:
    std::map<std::string, DIniField> m_fieldList;
    
    friend class DIniField;
};

inline std::map<std::string, DIniField>& DIniFile::getFieldsList()
{
    return m_fieldList;
}

inline std::map<std::string,DIniItem>& DIniField::getItemsList()
{
    return m_itemList;
}

#endif