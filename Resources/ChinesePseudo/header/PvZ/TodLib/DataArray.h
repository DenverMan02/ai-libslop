// DataArray.h

#ifndef __DATAARRAY_H__
#define __DATAARRAY_H__

enum
{
	DATA_ARRAY_INDEX_MASK		= 0x0000FFFF,
	DATA_ARRAY_KEY_MASK			= 0xFFFF0000,
	DATA_ARRAY_KEY_SHIFT		= 16,
	DATA_ARRAY_MAX_SIZE			= DATA_ARRAY_INDEX_MASK + 1,
	DATA_ARRAY_KEY_FIRST		= 1,	// Keys start at this value. 0 is reserved for DATAID_NULL
};

typedef unsigned int DataID;
#define DATAID_NULL ((DataID)0)

template <class ITEM>
class DataArray
{
public:
	DataArray();
	~DataArray();

	class DataArrayItem
	{
	public:
		ITEM m_item;
		DataID m_iD;
	};

	void DataArrayInitialize(unsigned int i_maxSize, const char *i_name);
	void DataArrayDispose();

	void DataArrayFreeAll();

	bool IterateNext(ITEM *&i_item);

	ITEM* DataArrayAlloc();
	void DataArrayFree(ITEM *i_item);

	ITEM* DataArrayGet(DataID i_id);
	ITEM* DataArrayTryToGet(DataID i_id);

	DataID DataArrayGetID(ITEM *i_item);

	DataArrayItem *m_block;
	unsigned int m_maxUsedCount;
	unsigned int m_maxSize;
	unsigned int m_freeListHead;
	unsigned int m_size;
	unsigned int m_nextKey;
	const char *m_name;
};

template <class ITEM>
ITEM* DataArray<ITEM>::DataArrayGet(DataID i_id)
{
	DBG_ASSERT_MSG(DataArrayTryToGet(i_id) != NULL, "Failed: DataArrayGet(0x%x) for %s", i_id, m_name);
	DataArrayItem *item = m_block + (i_id & DATA_ARRAY_INDEX_MASK);
	return &item->m_item;
}

template <class ITEM>
ITEM* DataArray<ITEM>::DataArrayTryToGet(DataID i_id)
{
	if (i_id == DATAID_NULL)
	{
		return NULL;
	}

	unsigned int index = i_id & DATA_ARRAY_INDEX_MASK;

	if (index >= m_maxSize)
	{
		return NULL;
	}

	DataArrayItem *item = m_block + index;

	if (item->m_iD != i_id)
	{
		return NULL;
	}

	return &item->m_item;
}

template<class ITEM>
DataID DataArray<ITEM>::DataArrayGetID(ITEM *i_item)
{
	DataArrayItem *item = (DataArrayItem *)i_item;
	DBG_ASSERT_MSG(DataArrayGet(item->m_iD) == i_item, "Failed: DataArrayGetID(0x%x) for %s", i_item, m_name);
	return item->m_iD;
}

template<class ITEM>
DataArray<ITEM>::DataArray()
{
	m_block = NULL;
	m_maxUsedCount = 0;
	m_maxSize = 0;
	m_freeListHead = 0;
	m_size = 0;
	m_nextKey = DATA_ARRAY_KEY_FIRST;
	m_name = NULL;
}

template<class ITEM>
DataArray<ITEM>::~DataArray()
{
	DataArrayDispose();
}

template<class ITEM>
void DataArray<ITEM>::DataArrayInitialize(unsigned int i_maxSize, const char *i_name)
{
	DBG_ASSERT(m_block == NULL);
	DBG_ASSERT(i_maxSize <= DATA_ARRAY_MAX_SIZE);

	unsigned int bytes = sizeof(DataArrayItem) * i_maxSize;
	
	// Note we can't new this as a DataArrayItem because it will call the constructor on all the ITEMs
	m_block = (DataArrayItem *)new char[bytes];

	m_maxSize = i_maxSize;
	m_name = i_name;

	// We start the key at a random number so two data arrays don't have the same starting DataID. This
	// makes it usually fail if you try to do a look up with a DataID from the wrong data array.
	unsigned int randomStart = (i_name[0] << 16) + (i_name[1] << 8) + i_name[2];

	// D is the first hex letter of data array so they will tend to show up in the debugger looking
	// something like 0xD19A0001. Note that after the game runs for a while D won't be the first letter.
	m_nextKey = 0xD000 | (randomStart & 0x0FFF);
}

template<class ITEM>
void DataArray<ITEM>::DataArrayDispose()
{
	if (m_block)
	{
		DataArrayFreeAll();

		delete [] (char*)m_block;
		
		m_block = NULL;
		m_maxUsedCount = 0;
		m_maxSize = 0;
		m_freeListHead = 0;
		m_size = 0;
		m_name = NULL;
	}
}

template<class ITEM>
ITEM* DataArray<ITEM>::DataArrayAlloc()
{
	DBG_ASSERT_MSG(m_size < m_maxSize, "Data array full: %s", m_name);
	DBG_ASSERT_MSG(m_freeListHead <= m_maxUsedCount, "DataArrayAlloc error in %s", m_name);

	unsigned int newIndex;

	if (m_freeListHead == m_maxUsedCount)
	{
		// Array is growing. Put new element at end.
		newIndex = m_maxUsedCount;
		m_maxUsedCount++;
		m_freeListHead = m_maxUsedCount;
	}
	else
	{
		// Pop an item of the free list. 
		newIndex = m_freeListHead;
		DataArrayItem *item = m_block + m_freeListHead;
		
		// Note: The next pointer for the free list is stored in the m_iD of the unallocated item.
		m_freeListHead = item->m_iD;
	}

	DataArrayItem *newItem = m_block + newIndex;

	memset(newItem, 0, sizeof(ITEM));

	// Note: The key is the upper DATA_ARRAY_KEY_BITCOUNT bits of the DataID and
	// the index is the lower DATA_ARRAY_INDEX_BITCOUNT bits.
	DataID idNew = (m_nextKey << DATA_ARRAY_KEY_SHIFT) | newIndex;

	newItem->m_iD = idNew;

	m_nextKey++;
	if (m_nextKey == DATA_ARRAY_MAX_SIZE)
	{
		// zero isn't a value key because that is used for DATAID_NULL
		m_nextKey = DATA_ARRAY_KEY_FIRST;
	}

	m_size++;

	// Call constructor
	::new(&newItem->m_item) ITEM;

	return &newItem->m_item;
}

template<class ITEM>
void DataArray<ITEM>::DataArrayFree(ITEM *i_item)
{
	DataArrayItem *item = (DataArrayItem *)i_item;
	DBG_ASSERT_MSG(DataArrayGet(item->m_iD) == i_item, "Failed: DataArrayFree(0x%x) in %s", i_item, m_name);
	
	// Call destructor
	item->m_item.~ITEM();

#ifdef _DEBUG
	// Fill freed memory with garbage
	memset((void*)&item->m_item, 0xFD, sizeof(ITEM));
#endif

	// Put the freed item on the head of the free list
	// Note: The next pointer for the free list is stored in the m_iD of unallocated items.
	// Note: The key is 0 so that a DataID will never match a node in the free list.
	DataID idFreeListNext = m_freeListHead;

	m_freeListHead = item->m_iD & DATA_ARRAY_INDEX_MASK;
	item->m_iD = idFreeListNext;

	m_size--;
}

template<class ITEM>
void DataArray<ITEM>::DataArrayFreeAll()
{
	for (ITEM* item = NULL; IterateNext(item); )
	{
		DataArrayFree(item);
	}

	// Reset the max count and empty the free list
	m_maxUsedCount = 0;
	m_freeListHead = 0;
}

template<class ITEM>
bool DataArray<ITEM>::IterateNext(ITEM *&i_item)
{
	DataArrayItem *item = (DataArrayItem *)i_item;

	if (item == 0)
	{
		item = m_block;
	}
	else
	{
		item++;
	}

	while (item < m_block + m_maxUsedCount)
	{
		// When the m_iD key equals 0 the item is on the free list.
		if ((item->m_iD & DATA_ARRAY_KEY_MASK) != 0)
		{
			i_item = &item->m_item;
			return true;
		}

		item++;
	}

	i_item = (ITEM*)(ptrdiff_t)0xFFFFFFFF;
	return NULL;
}


#endif // __DATAARRAY_H__

