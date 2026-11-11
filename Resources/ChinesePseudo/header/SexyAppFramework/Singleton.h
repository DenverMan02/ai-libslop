//
//  Singleton.h
//  From PlantsVersusZombies2
//
//  Created by Joseph Sola on 1/26/12.
//	Adapted from Scott Bilas' article, 'An Automatic Singleton Utility,' from Game Programming Gems Vol. 1
//
//  Singleton Usage:
//
//		- Declaring a Singleton
//
//		class FooClass : public Singleton<FooClass>, public BaseFooClass
//		{
//			int GetFooValue();
//		};
//
//		- Using a Singleton
//
//		FooClass* fooSingleton = FooClass::GetInstance();
//		fooSingleton->GetFooValue();
//
//		- You must manually instantiate the object before the Singleton will work!
//
//	LazySingleton usage:
//	
//		- Same as Singleton, except that an instance will be constructed on the fly
//		the first time that GetInstance or GetInstancePtr is called
//
//		- Slightly slower, does a NULL test on each access
//

#ifndef __PRIME_SINGLETON_H__
#define __PRIME_SINGLETON_H__



namespace Sexy
{
    
template <class T>
class SexySingleton
{
public:
	static T* GetInstancePtr()
	{
		DBG_ASSERT(m_instance);
		return static_cast<T*>(m_instance);
	}
	static T& GetInstance()
	{
		DBG_ASSERT(m_instance);
		return *static_cast<T*>(m_instance);
	}
	
protected:
	SexySingleton()
	{
		// Point the internal instance pointer to this object's offset in our containing object
		DBG_ASSERT(!m_instance);
		m_instance = this;
	}
	virtual ~SexySingleton()
	{
		DBG_ASSERT(m_instance);
        m_instance = NULL;
	}
	
private:
	static SexySingleton<T>* m_instance;
};

template <class T> SexySingleton<T>* SexySingleton<T>::m_instance = NULL;


// LazySingleton
//	- Very similar to Singleton, but instantiating an object prior to use is not necessary
//	- Singleton access is slightly slower and may cause an object allocation!
template <class T>
class LazySingleton
{
public:
	static T* GetInstancePtr()
	{
		if (!m_instance)
		{
			// If we have no instance, construct a new one
			new T();
			// The LazySingleton constructor will properly fill in our instance pointer
			DBG_ASSERT(m_instance);
		}
		return static_cast<T*>(m_instance);
	}
	static T& GetInstance()
	{
		return *GetInstancePtr();
	}
	static bool HasInstance()
	{
		return NULL != m_instance;
	}
	
protected:
	LazySingleton()
	{
		DBG_ASSERT(!m_instance);
		m_instance = this;
	}
	virtual ~LazySingleton()
	{
		DBG_ASSERT(!m_instance);
        m_instance = NULL;
	}
	
	static LazySingleton<T>* m_instance;
};

template <class T> LazySingleton<T>* LazySingleton<T>::m_instance = NULL;

} // namespace Sexy

#endif // __PRIME_SINGLETON_H__
