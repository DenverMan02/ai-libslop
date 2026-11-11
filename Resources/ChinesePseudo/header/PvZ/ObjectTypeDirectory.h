//
//  ObjectTypeDirectory.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//	  In PVZ2, many of our object types are defined externally in JSON packages.
//
//	  This utility class will collect all of the types from an RtDb table and provide
// 	an easy interface for finding them by TypeName (a string), or iterating over the
//	set of them.

#ifndef __OBJECTTYPEDIRECTORY_H__
#define __OBJECTTYPEDIRECTORY_H__

#include "Precompile.h"
#include "RtObject.h"
#include "RtDb.h"
#include "PVZDB.h"
#include "Singleton.h"

template<class T>
class ObjectTypeDirectoryIterator;

template<class T>
class ObjectTypeDirectory : public LazySingleton<ObjectTypeDirectory<T> >
{
public:
	typedef T ObjectType;
	typedef RtWeakPtr<const T> ObjectTypePtr;
	typedef ObjectTypeDirectoryIterator<T> Iterator;
	
	ObjectTypeDirectory() : m_directoryBuilt(false) {}

	void Init(PVZDB::TableIndex i_fromTable);
    void Clear();
	void SortTypes(const std::vector<std::string>& i_typeOrder);
	
	int GetCount() const;
	
	ObjectTypePtr GetTypeFromIndex(uint i_idx) const;
	ObjectTypePtr GetTypeFromTypeName(const std::string& i_typeName) const;
	
protected:
	typedef std::map<std::string, ObjectTypePtr> StringToObjectTypeMap;
	typedef std::vector<ObjectTypePtr> ObjectTypeVector;

	StringToObjectTypeMap m_objectTypeMap;
	ObjectTypeVector m_objectTypeVector;
	
	bool m_directoryBuilt;
};

template<class T>
void ObjectTypeDirectory<T>::Init(PVZDB::TableIndex i_table)
{
	// Right now, only support one initialization
	DBG_ASSERT(!m_directoryBuilt);
	
	for (RtDbTable::Iterator iter = PVZDB::GetInstance().GetObjectIteratorForTable(i_table); iter; ++iter)
	{
		RtWeakPtr<RtObject> obj = *iter;
		if (obj && obj->IsA(ObjectType::StaticGetClass()))
		{
			ObjectTypePtr objTypePtr = obj;
			m_objectTypeMap[objTypePtr->TypeName] = objTypePtr;
			m_objectTypeVector.push_back(objTypePtr);
		}
	}
	
	// Done!
	m_directoryBuilt = true;
}

template<class T>
void ObjectTypeDirectory<T>::Clear()
{
    m_objectTypeMap.clear();
    m_objectTypeVector.clear();
    m_directoryBuilt = false;
}

template<class T>
void ObjectTypeDirectory<T>::SortTypes(const std::vector<std::string> &i_typeOrder)
{
	DBG_ASSERT(m_directoryBuilt);
	
	std::set<ObjectTypePtr> allObjectTypes(m_objectTypeVector.begin(), m_objectTypeVector.end());
	m_objectTypeVector.clear();
	
	// Put all of our types into our m_objectTypeVector, ordered according to the passed in list
	for (int i = 0; i < (int)i_typeOrder.size(); ++i)
	{
		const std::string& plantTypeName = i_typeOrder[i];
		typename std::map<std::string, ObjectTypePtr>::const_iterator findIter = m_objectTypeMap.find(plantTypeName);
		if (findIter != m_objectTypeMap.end())
		{
			// Put this one in the actual type list and remove it from the temp full type set
			m_objectTypeVector.push_back((*findIter).second);
			typename std::set<ObjectTypePtr>::iterator setFindIter = allObjectTypes.find((*findIter).second);
			allObjectTypes.erase(setFindIter);
		}
	}
	// Add any types left in the temp full type set to the list
	for (typename std::set<ObjectTypePtr>::iterator setIter = allObjectTypes.begin(); setIter != allObjectTypes.end(); ++setIter)
	{
		const ObjectTypePtr& objectType = (*setIter);
		m_objectTypeVector.push_back(objectType);
	}
}

template<class T>
RtWeakPtr<const T> ObjectTypeDirectory<T>::GetTypeFromTypeName(const std::string &i_typeName) const
{
	DBG_ASSERT(m_directoryBuilt);
	typename std::map<std::string, ObjectTypePtr>::const_iterator findIter = m_objectTypeMap.find(i_typeName);
	if (findIter == m_objectTypeMap.end())
	{
		// Return an empty (m_id == 0 ~= NULL) ptr
		return ObjectTypePtr();
	}
	return (*findIter).second;
}

template<class T>
RtWeakPtr<const T> ObjectTypeDirectory<T>::GetTypeFromIndex(uint i_idx) const
{
	DBG_ASSERT(m_directoryBuilt);
	DBG_ASSERT(i_idx >= 0 && i_idx < m_objectTypeVector.size());
	return m_objectTypeVector[i_idx];
}

template<class T>
int ObjectTypeDirectory<T>::GetCount() const
{
	return static_cast<int>(m_objectTypeVector.size());
}

template<class T>
class ObjectTypeDirectoryIterator
{
public:
	ObjectTypeDirectoryIterator<T>() : m_idx(0) {}
	inline RtWeakPtr<const T> operator * () { return ObjectTypeDirectory<T>::GetInstance().GetTypeFromIndex(m_idx); }
	inline ObjectTypeDirectoryIterator<T>& operator ++ () { ++m_idx; return *this; }
	inline operator bool() const { return m_idx < ObjectTypeDirectory<T>::GetInstance().GetCount(); }
private:
	int m_idx;
};
		

#endif // __OBJECTTYPEDIRECTORY_H__
