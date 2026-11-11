//
//  Singleton.h
//  PlantsVersusZombies2
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

#ifndef __PVZ2_SINGLETON_H__
#define __PVZ2_SINGLETON_H__

#include "Precompile.h"

#include "SexyAppFramework/Singleton.h"

template <typename T> using Singleton = Sexy::SexySingleton<T>;

using Sexy::LazySingleton;



#endif // __PVZ2_SINGLETON_H__
