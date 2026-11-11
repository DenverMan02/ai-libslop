#ifndef TARRAY_H_INCLUDED
#define TARRAY_H_INCLUDED
namespace Sexy  { 

typedef int (*QsortCompareProc)(const void* i_a, const void* i_b);

// Use to enable/disable simple statements or params in different modes.
//
#if SEXY_IS_BUILD_DEBUG
#	define PRIME_DEBUG_ONLY(x) x
#	define PRIME_DEBUG_PARAM(x) x
#else
#	define PRIME_DEBUG_ONLY(x)
#	define PRIME_DEBUG_PARAM(x)
#endif
#if SEXY_IS_BUILD_RELEASE
#	define PRIME_RELEASE_ONLY(x) x
#	define PRIME_NOT_RELEASE_ONLY(x)
#else
#	define PRIME_RELEASE_ONLY(x)
#	define PRIME_NOT_RELEASE_ONLY(x) x
#endif


#define M_DATA ((T*)m_rawData)

/*--------------------------------------------------------------------------*/
// Class TArray <T, CAPACITY> declaration.

// Usage:
//
// This collection is ultimately an array of T[CAPACITY] that also tracks how
// many elements are in use. Because it's a constant-sized array, any
// operations to modify the collection will never modify outstanding pointers
// you have to its elements. All memory is allocated up front.
//
// Important: T is treated as a real class, not raw memory like TRawArray does.
// default constructors, copy constructors, dtors, and operator= are all called
// as needed (placement-new is used to avoid allocs/deallocs).
//
// Performance:
//
// This collection should be almost exactly the same speed as if you were to
// use, for example, an int32[1000] yourself, assuming you also track the
// "elements used" with some kind of pointer or counter. Differences:
//
//   * We don't use the mem* operations but instead use for-loops. Depending on
//     compiler optimizations this could be the same or slightly worse.
//
//   * We don't default-construct the entire array. If T is a POD type this
//     will make no difference but if it's a real class with default ctors then
//     TArray's avoidance of default-init over all of T[CAPACITY] will definitely
//     be faster!
//
// $$ Future: (see notes for TRawArray) but also look at duplication of
//    functionality with TRawArray and try to hoist up.
//

//---Removed Asserts, put back in?---
template <typename T, const int32 CAPACITY>
class TArray
{
public:
    typedef T ValueType;
    typedef TArray <T, CAPACITY> ThisType;
    typedef ValueType* Iter;
    typedef const ValueType* CIter;
    
    // Ctor/dtor.
    
    static const int32 Capacity = CAPACITY;
    
    // init to empty collection
    explicit TArray()
    { init(); }
    
    // init with a certain number of preallocated elements, all default-constructed
    explicit TArray(int32 i_initialCount)
    { init(); Resize(i_initialCount); }
    
    // init with a certain number of preallocated elements, all copy-constructed from i_valueToCopy
    TArray(int32 i_initialCount, const T& i_valueToCopy)
    { init(); Resize(i_initialCount, i_valueToCopy); }
    
    // copy the other collection's elements
    TArray(const ThisType& i_other)
    { init(); Assign(i_other); }
    
    // destruct all in use
    ~TArray()
    { Clear(); }
    
    // Operators.
    
    T& operator [] (int32 i_index)
    {  return M_DATA[i_index]; }
    const T& operator [] (int32 i_index) const
    {  return M_DATA[i_index]; }
    
    ThisType& operator = (const ThisType& i_other)
    { Assign(i_other); return *this; }
    
    // Access.
    
    // iterators
    Iter   GetBegin()			{ return M_DATA; }
    CIter  GetBegin() const		{ return M_DATA; }
    Iter   GetEnd()				{ return m_end; }
    CIter  GetEnd() const		{ return m_end; }
    
    // front and back elements
    T& GetFront()
    { return M_DATA[0]; }
    const T& GetFront() const
    {return M_DATA[0]; }
    T& GetBack()
    { return m_end[-1]; }
    const T& GetBack() const
    { return m_end[-1]; }
    
    // Size.
    
    // query how many elements allocated
    int32 GetCount() const
    { return m_end - M_DATA; }
    int32 GetSizeBytes() const
    { return (const uint8*)m_end - m_rawData; }
    bool IsEmpty() const
    { return m_end == M_DATA; }
    bool IsFull() const
    { return GetCount() == GetCapacity(); }
    
    // total capacity of array (constant count)
    int32 GetCapacity() const
    { return CAPACITY; }
    int32 GetCapacityBytes() const
    { return CAPACITY * sizeof(T); }
    
    // set the size to the given count, destroying/constructing elements in place as needed
    void Resize(int32 i_newCount)
    {
        T* oldEnd = resizeNoConstruct(i_newCount);
        if (oldEnd != NULL)
        {
            for (T* i = oldEnd ; i != m_end ; ++i)
            {
                new(i) T();
            }
        }
    }
    
    // set the size to the given count - if growing, copies the given value to the new elements
    void Resize(int32 i_newCount, const T& i_valueToCopy)
    {
        T* oldEnd = resizeNoConstruct(i_newCount);
        if (oldEnd != NULL)
        {
            for (T* i = oldEnd ; i != m_end ; ++i)
            {
                new(i) T(i_valueToCopy);
            }
        }
    }
    
    // set the size to the capacity
    void ResizeToCapacity()
    { Resize(GetCapacity()); }
    
    // set the size to the capacity, copying in the given value as needed
    void ResizeToCapacity(const T& i_valueToCopy)
    { Resize(GetCapacity(), i_valueToCopy); }
    
    // destroy all elements
    void Clear()
    { Resize(0); }
    
    // fill currently used memory with 0's
    void MemClear()
    { ClearArray(GetBegin(), GetCount()); }
    
    // Assign.
    
    // copy the other collection's elements
    void Assign(const ThisType& i_other)
    {
        Assign(i_other.GetBegin(), i_other.GetEnd());
    }
    
    // clear the array and realloc to the given count, copying the given object into every used slot
    void Assign(int32 i_newCount, const T& i_valueToCopy)
    {
        Clear();
        Resize(i_newCount, i_valueToCopy);
    }
    
    // clear the array, realloc the count to the distance between the two iterators, and copy from begin to end to our array
    template <typename ITER>
    void Assign(ITER i_begin, ITER i_end)
    {
        Clear();
        PushBack(i_begin, i_end);
    }
    
    // Push/pop.
    
    // add a new element to the end (default-initialized)
    void PushBack()
    {
        new(m_end) T();
        PRIME_DEBUG_ONLY(++m_count);
        ++m_end;
    }
    
    // add a new element to the end and return a ref to it (default-initialized)
    T& PushAndGetBack()
    {
        new(m_end) T();
        PRIME_DEBUG_ONLY(++m_count);
        return *m_end++;
    }
    
    // add a new element to the end, copying from the given value
    void PushBack(const T& i_valueToAppend)
    {
        new(m_end) T(i_valueToAppend);
        PRIME_DEBUG_ONLY(++m_count);
        ++m_end;
    }
    
    // add a new element to the end, copying from the given value, and return a ref to it
    T& PushAndGetBack(const T& i_valueToAppend)
    {
        new(m_end) T(i_valueToAppend);
        PRIME_DEBUG_ONLY(++m_count);
        return *m_end++;
    }
    
    // add a set of new elements to the end, copying from begin to end
    template <typename ITER>
    void PushBack(ITER i_begin, ITER i_end)
    {
        if (i_begin != i_end)
        {
            PRIME_DEBUG_ONLY(m_count += i_end - i_begin);
            while (i_begin != i_end)
            {
                new(m_end++) T(*i_begin++);
            }
        }
    }
    
    // remove and destroy the last element
    void PopBack()
    {
        PRIME_DEBUG_ONLY(--m_count);
        --m_end;
        m_end->~T();
    }
    
    // remove and destroy the last i_popCount elements
    void PopBack(int32 i_popCount)
    {
        PRIME_DEBUG_ONLY(m_count -= i_popCount);
        for (; i_popCount > 0; --i_popCount)
        {
            --m_end;
            m_end->~T();
        }
    }
    
    // Packed functions.
    
    // $ these special functions will keep the array "packed" by replacing
    //   removed elements from the middle with elements from the end. this is
    //   very fast because it only replaces the elements *removed*, rather than
    //   needing to memmove the rest of the array past the removed section.
    //
    //   note that this makes the array "unstable" - as you remove elements it
    //   will rearrange itself. this may or may not be acceptable depending on
    //   how you use the array.
    
    // remove a single element by copying the back to the removed spot and
    // destroying the back element.
    void RemoveAndPack(Iter i_elementToRemove)
    {
        T* back = m_end - 1;
        if (i_elementToRemove != back)
        {
            *i_elementToRemove = *back;
        }
        PopBack();
    }
    
    // remove a range of elements from begin up to end
    void RemoveAndPack(Iter i_removeBegin, Iter i_removeEnd)
    {
        int32 removeCount = i_removeEnd - i_removeBegin;
        if (removeCount != 0)
        {
            if (i_removeEnd != m_end)
            {
                int32 moveCount = MIN(m_end - i_removeEnd, removeCount);
                T* src = m_end - moveCount;
                while (moveCount-- != 0)
                {
                    *i_removeBegin++ = *src++;
                }
            }
            PopBack(removeCount);
        }
    }
    
    // index-based versions
    void RemoveAndPack(int32 i_indexToRemove)
    { RemoveAndPack(M_DATA + i_indexToRemove); }
    void RemoveAndPack(int32 i_removeBegin, int32 i_removeEnd)
    { RemoveAndPack(M_DATA + i_removeBegin, M_DATA + i_removeEnd); }
    
    // Misc utility functions.
    
    /* uncomment when qsort_s supported
     template <typename CONTEXT>
     void Sort(CONTEXT* i_contextObject, int32 (*i_compareProc)(CONTEXT* i_contextObject, const T* i_a, const T* i_b)) {
     qsort_s(GetBegin(), GetCount(), sizeof(T), (QsortsCompareProc)i_compareProc, i_contextObject); }
     template <typename CONTEXT>
     void Sort(CONTEXT* i_contextObject, int32 (*i_compareProc)(const CONTEXT* i_contextObject, const T* i_a, const T* i_b)) {
     qsort_s(GetBegin(), GetCount(), sizeof(T), (QsortsCompareProc)i_compareProc, i_contextObject); }
     */
    
    // qsort over all used elements
    void Sort(int32 (*i_compareProc)(const T* i_a, const T* i_b)) {
        qsort(GetBegin(), GetCount(), sizeof(T), (QsortCompareProc)i_compareProc); }
    
    // search for an element, returns iter if found, NULL if not found
    T* Find(const T& i_value)
    {
        for (T* ibegin = GetBegin(), * i = ibegin, * iend = GetEnd(); i != iend; ++i)
        {
            if (*i == i_value)
                return i;
        }
        return NULL;
    }
    
    // const version
    const T* Find(const T& i_value) const
    { return const_cast<ThisType*>(this)->Find(i_value); }
    
    // search for an element, returns -1 if not found
    int32 IndexOf(const T& i_value) const
    {
        const T* found = Find(i_value);
        return (found != NULL) ? (found - GetBegin()) : -1;
    }
    
    // check to see if it's there at all
    bool Contains(const T& i_value) const
    { return Find(i_value) != NULL; }
    
private:
    
    void init()
    {
        PRIME_NOT_RELEASE_ONLY(m_data = (DataArray*)m_rawData);
        m_end = M_DATA;
        PRIME_DEBUG_ONLY(m_count = 0);
    }
    
    // helper that does most of the Resize() operation (caller does the construct part)
    T* resizeNoConstruct(int32 i_newCount)
    {
        
        PRIME_DEBUG_ONLY(m_count = i_newCount);
        T* oldEnd = m_end;
        m_end = M_DATA + i_newCount;
        
        if (m_end > oldEnd)
        {
            return oldEnd;
        }
        else if (m_end < oldEnd)
        {
            for (T* i = m_end ; i != oldEnd ; ++i)
            {
                i->~T();
            }
        }
        return NULL;
    }
    
    uint8 m_rawData[CAPACITY * sizeof(T)];
    T*	 m_end;
    
#	if !SEXY_IS_BUILD_RELEASE
    typedef T DataArray[CAPACITY];
    DataArray* m_data;
#	endif
#	if SEXY_IS_BUILD_DEBUG
    int32 m_count;
#	endif
};
#undef M_DATA
}//Namespace Sexy
#endif
