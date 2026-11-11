// TodList.h

#ifndef __TODLIST_H__
#define __TODLIST_H__

struct TodAllocator
{
	inline void Initialize(int i_growCount, int i_itemSize);
	inline void Dispose();
	inline void FreeAll();
	inline void* Alloc(int i_itemSize);
	inline void* Calloc(int i_itemSize);
	inline void Free(void *i_item, int i_itemSize);
	inline void Grow();
	inline bool IsPointerFromAllocator(void *i_item);
	inline bool IsPointerOnFreeList(void *i_item);

	void* m_freeList;
	void* m_blockList;
	int m_growCount;
	int m_totalItems;
	int m_itemSize;
};

TodAllocator* FindGlobalAllocator(int size);

void* TodAllocator::Alloc(int i_itemSize)
{
	m_totalItems++;

	if (m_freeList == NULL)
	{
		Grow();
	}

	// We reuse freed items in a singly-linked list
	void* item = m_freeList;
	void* next = *(void**)m_freeList;
	m_freeList = next;

	memset(item, 0, i_itemSize);

	return item;
}

void TodAllocator::Free(void *i_item, int i_itemSize)
{
	m_totalItems--;

	DBG_ASSERT(IsPointerFromAllocator(i_item));
	DBG_ASSERT(!IsPointerOnFreeList(i_item));

	// We reuse freed items in a singly-linked list
	*(void**)i_item = m_freeList;
	m_freeList = i_item;
}

void TodAllocator::Initialize(int i_growCount, int i_itemSize)
{
	// Since we reuse freed items in a singly-linked list, we need the items large enough to hold the pointer
	DBG_ASSERT(i_itemSize >= sizeof(void*));

	m_freeList = NULL;
	m_blockList = NULL;
	m_totalItems = 0;
	m_itemSize = i_itemSize;
	m_growCount = i_growCount;

	// We grow on initialize because it is more accountable then lazy growing
	Grow();
}

void TodAllocator::Dispose()
{
	FreeAll();
}

void TodAllocator::FreeAll()
{
	void *block = m_blockList;
	while (block)
	{
		void* next = *(void**)block;
		delete [] (char*)block;
		block = next;
	}

	m_blockList = NULL;
	m_freeList = NULL;
	m_totalItems = 0;
}

void TodAllocator::Grow()
{
	DBG_ASSERT(m_growCount > 0);
	DBG_ASSERT(m_itemSize >= sizeof(void*));

	int itemAllocSize = m_itemSize;

	int size = m_growCount * itemAllocSize + sizeof(void*);

	void *block = new char[size];

	// There's a singly linked list pointer on the front of the block
	*(void**)block = m_blockList;
	m_blockList = block;

	void *nextItem = m_freeList;
	for (int i = 0; i < m_growCount; i++)
	{
		void *item = ((char*)block) + sizeof(void*) + (i * itemAllocSize);
		*(void**)item = nextItem;
		nextItem = item;
	}

	m_freeList = nextItem;
}

bool TodAllocator::IsPointerFromAllocator(void *i_item)
{
	int itemAllocSize = m_itemSize;

	int sizeBlock = m_growCount * itemAllocSize;

	void *block = m_blockList;
	while (block)
	{
		void *next = *(void**)block;
		uchar *blockHead = ((uchar*)block) + sizeof(void*);
		block = next;
		
		if (i_item < blockHead || i_item >= blockHead + sizeBlock)
		{
			continue;
		}

		ptrdiff_t ptrOffset = ((ptrdiff_t)i_item - (ptrdiff_t)blockHead) % itemAllocSize;

		if (ptrOffset != 0)
		{
			continue;
		}

		return true;
	}

	return false;
}

bool TodAllocator::IsPointerOnFreeList(void *i_item)
{
	void *block = m_freeList;

	while (block)
	{
		if (i_item == block)
		{
			return true;
		}

		block = *(void**)block;
	}

	return false;
}

template <class VALUE>
struct TodListNode
{
	VALUE m_value;
	TodListNode<VALUE> *m_next;
	TodListNode<VALUE> *m_prev;
};

typedef void *TodListIter;

template <class VALUE>
class TodList
{
public:
	typedef TodListNode<VALUE> NodeType;

	inline TodList();
	inline TodList(TodAllocator *i_allocatorArg);
	inline ~TodList();

	inline void SetAllocator(TodAllocator *i_allocatorArg);
	inline TodList& operator=(const TodList& i_rightArg);
	inline int GetSize() const;
	inline bool IsEmpty() const;
	inline VALUE& GetHead() const;
	inline VALUE& GetTail() const;
	inline void AddHead(const VALUE& i_value);
	inline void AddTail(const VALUE& i_value);
	inline VALUE RemoveHead();
	inline VALUE RemoveTail();
	inline TodListIter InsertBefore(TodListIter i_where, const VALUE& i_value);
	inline void InsertList(TodListIter i_where, const TodList<VALUE>& instertedList);
	inline TodListIter RemoveAt(TodListIter i_where);
	inline void RemoveAll();
	inline TodListIter Find(const VALUE& i_value) const;

	inline TodListIter GetHeadIter() const;
	inline TodListIter GetTailIter() const;
	inline VALUE& GetNextIter(TodListIter &i_iter) const;
	inline VALUE& GetPrevIter(TodListIter &i_iter) const;

	NodeType *m_head;
	NodeType *m_tail;
	int m_size;
	TodAllocator *mpAllocator;
};

template<class VALUE>
TodList<VALUE>::TodList()
{
	m_head = NULL;
	m_tail = NULL;
	m_size = 0;
	mpAllocator = NULL;
}

template<class VALUE>
TodList<VALUE>::TodList(TodAllocator *i_allocatorArg)
{
	m_head = NULL;
	m_tail = NULL;
	m_size = 0;
	mpAllocator = i_allocatorArg;
}

template<class VALUE>
TodList<VALUE>::~TodList()
{
	RemoveAll();
}

template<class VALUE>
void TodList<VALUE>::SetAllocator(TodAllocator *i_allocatorArg)
{
	// Can't change allocator when nodes exist
	DBG_ASSERT(m_size == 0);
	mpAllocator = i_allocatorArg;
}

template<class VALUE>
TodList<VALUE>& TodList<VALUE>::operator=(const TodList& i_rightArg)
{
	RemoveAll();

	NodeType *node = i_rightArg.m_head;
	while (node)
	{
		AddTail(node->m_value);
		node = node->m_next;
	}

	return *this;
}

template<class VALUE>
int TodList<VALUE>::GetSize() const
{
	return m_size;
}

template<class VALUE>
bool TodList<VALUE>::IsEmpty() const
{
	return m_size == 0;
}

template<class VALUE>
VALUE& TodList<VALUE>::GetHead() const
{
	DBG_ASSERT(m_head != NULL);
	return m_head->m_value;
}

template<class VALUE>
VALUE& TodList<VALUE>::GetTail() const
{
	DBG_ASSERT(m_tail != NULL);
	return m_tail->m_value;
}

template<class VALUE>
void TodList<VALUE>::AddHead(const VALUE& i_value)
{
	if (mpAllocator == NULL)
	{
		mpAllocator = FindGlobalAllocator(sizeof(NodeType));
	}

	NodeType *node = (NodeType *)mpAllocator->Alloc(sizeof(NodeType));
	
	// Call constructor
	::new(&node->m_value) VALUE(i_value);
	
	node->m_next = m_head;
	node->m_prev = NULL;

	if (m_head)
	{
		m_head->m_prev = node;
	}
	else
	{
		m_tail = node;
	}

	m_size++;
	m_head = node;
}

template<class VALUE>
void TodList<VALUE>::AddTail(const VALUE& i_value)
{
	if (mpAllocator == NULL)
	{
		mpAllocator = FindGlobalAllocator(sizeof(NodeType));
	}

	NodeType *node = (NodeType *)mpAllocator->Alloc(sizeof(NodeType));

	// Call constructor
	::new(&node->m_value) VALUE(i_value);

	node->m_next = NULL;
	node->m_prev = m_tail;

	if (m_tail)
	{
		m_tail->m_next = node;
	}
	else
	{
		m_head = node;
	}

	m_size++;
	m_tail = node;
}

template<class VALUE>
VALUE TodList<VALUE>::RemoveHead()
{
	NodeType *node = m_head;
	m_head = m_head->m_next;
	if (m_head)
	{
		m_head->m_prev = NULL;
	}
	else
	{
		m_tail = NULL;
	}

	VALUE valueCopy = node->m_value;

	m_size--;
	
	// call destructor
	node->m_value.~VALUE();
	mpAllocator->Free(node, sizeof(NodeType));

	return valueCopy;
}

template<class VALUE>
VALUE TodList<VALUE>::RemoveTail()
{
	NodeType *node = m_tail;
	m_tail = m_tail->m_prev;
	if (m_tail)
	{
		m_tail->m_next = NULL;
	}
	else
	{
		m_head = NULL;
	}

	VALUE valueCopy = node->m_value;

	m_size--;

	// call destructor
	node->m_value.~VALUE();
	mpAllocator->Free(node, sizeof(NodeType));

	return valueCopy;
}

template<class VALUE>
TodListIter TodList<VALUE>::InsertBefore(TodListIter i_where, const VALUE& i_value)
{
	if (mpAllocator == NULL)
	{
		mpAllocator = FindGlobalAllocator(sizeof(NodeType));
	}

	NodeType *node = (NodeType *) mpAllocator->Alloc(sizeof(NodeType));

	// Call constructor
	::new(&node->m_value) VALUE(i_value);

	NodeType *nodeWhere = (NodeType *)i_where;

	node->m_next = nodeWhere;

	if (nodeWhere)
	{
		node->m_prev = nodeWhere->m_prev;

		if (nodeWhere->m_prev)
		{
			nodeWhere->m_prev->m_next = node;
		}
		else
		{
			m_head = node;
		}

		nodeWhere->m_prev = node;
	}
	else
	{
		node->m_prev = m_tail;

		if (m_tail)
		{
			m_tail->m_next = node;
		}
		else
		{
			m_head = node;
		}

		m_tail = node;
	}

	m_size++;
	return (TodListIter)node;
}

template<class VALUE>
void TodList<VALUE>::InsertList(TodListIter i_where, const TodList<VALUE>& instertedList)
{
	for (TodListIter iter = instertedList.GetHeadIter(); iter != NULL;)
	{
		const VALUE& value = instertedList.GetNextIter(iter);
		InsertBefore(i_where, value);
	}
}

template<class VALUE>
TodListIter TodList<VALUE>::RemoveAt(TodListIter i_where)
{
	NodeType *nodeWhere = (NodeType *)i_where;

	if (nodeWhere->m_prev)
	{
		nodeWhere->m_prev->m_next = nodeWhere->m_next;
	}
	else
	{
		m_head = nodeWhere->m_next;
	}

	if (nodeWhere->m_next)
	{
		nodeWhere->m_next->m_prev = nodeWhere->m_prev;
	}
	else
	{
		m_tail = nodeWhere->m_prev;
	}

	NodeType *pWhereNext = nodeWhere->m_next;

	m_size--;

	// call destructor
	nodeWhere->m_value.~VALUE();
	mpAllocator->Free(nodeWhere, sizeof(NodeType));

	return (TodListIter)pWhereNext;
}

template<class VALUE>
void TodList<VALUE>::RemoveAll()
{
	NodeType *node = m_head;
	while (node)
	{
		NodeType *pCurrentNode = node;
		node = node->m_next;

		// call destructor
		pCurrentNode->m_value.~VALUE();
		mpAllocator->Free(pCurrentNode, sizeof(NodeType));
	}

	m_size = 0;
	m_head = NULL;
	m_tail = NULL;
}

template<class VALUE>
TodListIter TodList<VALUE>::Find(const VALUE& i_value) const
{
	NodeType *node = m_head;
	while (node)
	{
		if (node->m_value == i_value)
		{
			return (TodListIter)node;
		}

		node = node->m_next;
	}

	return NULL;
}

template<class VALUE>
TodListIter TodList<VALUE>::GetHeadIter() const
{
	return (TodListIter)m_head;
}

template<class VALUE>
TodListIter TodList<VALUE>::GetTailIter() const
{
	return (TodListIter)m_tail;
}

template<class VALUE>
VALUE& TodList<VALUE>::GetNextIter(TodListIter &i_iter) const
{
	DBG_ASSERT(i_iter != NULL);

	NodeType *node = (NodeType *)i_iter;
	i_iter = node->m_next;
	return node->m_value;
}

template<class VALUE>
VALUE& TodList<VALUE>::GetPrevIter(TodListIter &i_iter) const
{
	DBG_ASSERT(i_iter != NULL);

	NodeType *node = (NodeType *)i_iter;
	i_iter = node->m_prev;
	return node->m_value;
}

#endif // __TODLIST_H__
