#ifndef MEMPOOLS_H_INCLUDED
#define MEMPOOLS_H_INCLUDED

#include "Debug.h"
#include "Common.h"
#include <list>
#include <set>
#include <map>


namespace Sexy 
{
	class SimpleMemPool
	{
	public:
		SimpleMemPool(uint32 itemSize, uint32 maxItems);
		~SimpleMemPool();
		
		uint8*	GetMemory(uint32 theSize);
		void	ReturnMemory(uint8* );

		int32	GetNumItems() const { return mNumItems; }
		uint32	GetItemSize() const { return mItemSize; }
	private:
		uint8* mItemBuffer;
		uint32 mItemSize;
		uint32 mMaxItems;
		int32  mNumItems;
		uint8* mOccupied;
	};
}



// from SJBrown ... 
// http://www.sjbrown.co.uk/2004/05/01/pooled-allocators-for-the-stl/

//! A standards-compliant pooled allocator.
template<typename T, typename PoolT>
class PooledAllocator
{
public:
	typedef size_t		size_type;			//!< A type that can represent the size of the largest object in the allocation model.
	typedef ptrdiff_t	difference_type;	//!< A type that can represent the difference between any two pointers in the allocation model.
	
	typedef T			value_type;			//!< Identical to T.
	typedef T*			pointer;			//!< Pointer to T;
	typedef T const*	const_pointer;		//!< Pointer to const T.
	typedef T&			reference;			//!< Reference to T.
	typedef T const&	const_reference;	//!< Reference to const T.
	
	//! A struct to construct an allocator for a different type.
	template<typename U> 
	struct rebind { typedef PooledAllocator<U,PoolT> other; };
	
	//! Creates a pooled allocator to the given pool.
	/*! This is non-explicit for ease of use.
	 */
	PooledAllocator( PoolT* pool) : m_pool( pool ) 
	{
		DBG_ASSERT( !m_pool || sizeof( T ) <= m_pool->GetItemSize() );
	}
	
	//! Creates a pooled allocator to the argument's pool.
	/*! If the argument has no pool, then this allocator will allocate off the heap.
	 */
	template<typename U>
	PooledAllocator( PooledAllocator<U,PoolT> const& arg ) : m_pool( arg.m_pool )
	{
		DBG_ASSERT( !m_pool || sizeof( T ) <= m_pool->GetItemSize() );
	}
	
	//! The largest value that can meaningfully passed to allocate.
	size_type max_size() const { return 0xffffffff; }
	
	//! Memory is allocated for \c count objects of type \c T but objects are not constructed.
	/*! This function may raise an appropriate exception. The result is a random access iterator.
	 */
	pointer allocate( size_type count, std::allocator<void>::const_pointer /*hint*/ = 0 ) const
	{
		if( m_pool && (count*sizeof(T))<=m_pool->GetItemSize() )
		{
			return reinterpret_cast<T*>( m_pool->GetMemory(sizeof(T) * (uint32)count) );
		}
		else 
		{
			return reinterpret_cast<T*>( new char[ count*sizeof( T ) ] );
		}
	}
	
	//! Deallocates memory allocated by allocate.
	/*! All \c count objects in the area pointed by \c block must be destroyed prior to this call. 
	 \c count must match the value passed to allocate to obtain this memory. Does not throw exceptions. 
	 \c block must not be null.
	 */
	void deallocate( pointer block, size_type count ) const throw()
	{
#ifdef HOST_ANDROID
// Android's STL implementation will delete NULL when you add to an empty Vector
//  ...honest, should this assert even be here? Handling delete NULL is pretty much de rigueur these days.
		if ( block == NULL )
			return;
#endif

		DBG_ASSERT( block && "null pointer argument" );

		if( m_pool && (count*sizeof(T))<=m_pool->GetItemSize() )
		{
			m_pool->ReturnMemory((uint8*)block );
		}
		else
		{
			delete[] reinterpret_cast<char*>( block );
		}
	}

	//! Constructs an element of \c T at the given pointer.
	/*! Effect: new( element ) T( arg )
	 */
	void construct( pointer element, T const& arg )
	{
		new( element ) T( arg );
	}
	
	//! Destroys an element of \c T at the given pointer.
	/*! Effect: element->~T()
	 */
	void destroy( pointer element )
	{
		element->~T();
		(void)element; // FIXME: genuinely bizarre 'unused parameter' bug with vs2003
	}
	
	//! Returns the address of the given reference.
	pointer address( reference element ) const
	{
		return &element;
	}
	
	//! Returns the address of the given reference.
	const_pointer address( const_reference element ) const
	{
		return &element;
	}
	
	//! The pool for this allocator.
	PoolT* m_pool;
};

//! A specialisation of the pooled allocator for the void type.
template<typename PoolT>
class PooledAllocator<void,PoolT>
{
public:
	typedef size_t		size_type;			//!< A type that can represent the size of the largest object in the allocation model.
	typedef ptrdiff_t	difference_type;	//!< A type that can represent the difference between any two pointers in the allocation model.
	
	typedef void		value_type;			//!< Identical to void.
	typedef void*		pointer;			//!< Pointer to void;
	typedef void const*	const_pointer;		//!< Pointer to const void.
	
	//! A struct to construct an allocator for a different type.
	template<typename U> 
	struct rebind { typedef PooledAllocator<U,PoolT> other; };
	
	//! Creates a pooled allocator with no pool.
	/*! This allocator will allocate off the heap.
	 */
	PooledAllocator() : m_pool( 0 ) {}
	
	//! Creates a pooled allocator to the given pool.
	PooledAllocator( PoolT* pool ) : m_pool( pool ) {}
	
	//! The pool for this allocator.
	PoolT* m_pool;
};

//! Returns true if objects allocated from one pool can be deallocated from the other.
template<typename T, typename U, typename PoolT>
bool operator==( PooledAllocator<T,PoolT> const& left, PooledAllocator<U,PoolT> const& right )
{
	return left.m_pool == right.m_pool;
}

//! Returns true if objects allocated from one pool cannot be deallocated from the other.
template<typename T, typename U, typename PoolT>
bool operator!=( PooledAllocator<T,PoolT> const& left, PooledAllocator<U,PoolT> const& right )
{
	return left.m_pool != right.m_pool;
}

//! Template typedef std::map<..., PooledAllocator> to PooledList<Key, Value>::Type.
template<typename Key, typename Value, class Traits = std::less<Key> >
struct SimplePooledMap 
{ 
	typedef std::map<Key, Value, Traits, PooledAllocator<std::pair<Key, Value>,Sexy::SimpleMemPool > > Type; 
};

//! Template typedef std::set<..., PooledAllocator> to PooledList<Value>::Type.
template<typename Value>
struct SimplePooledVector
{ 
	typedef std::vector<Value, PooledAllocator<Value,Sexy::SimpleMemPool> > Type; 
};


//! Template typedef std::set<..., PooledAllocator> to PooledList<Value>::Type.
template<typename Value>
struct SimplePooledList
{ 
	typedef std::list<Value, PooledAllocator<Value,Sexy::SimpleMemPool> > Type; 
};


//! Template typedef std::set<..., PooledAllocator> to PooledList<Value>::Type.
template<typename Value, typename Traits = std::less<Value> >
struct SimplePooledSet 
{ 
	typedef std::set<Value, Traits, PooledAllocator<Value,Sexy::SimpleMemPool> > Type; 
};



#endif
