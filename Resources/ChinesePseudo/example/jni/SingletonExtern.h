#ifndef SINGLETONEXTERN_H_
#define SINGLETONEXTERN_H_

#include "Singleton.h"

extern template LazySingleton<TimeMgr>* LazySingleton<TimeMgr>::m_instance;
extern template LazySingleton<PVZDB>* LazySingleton<PVZDB>::m_instance;
extern template LazySingleton<ObjectTypeDirectory<PlantType>>* LazySingleton<ObjectTypeDirectory<PlantType>>::m_instance;
extern template LazySingleton<ObjectTypeDirectory<ZombieType>>* LazySingleton<ObjectTypeDirectory<ZombieType>>::m_instance;

#endif /* SINGLETONEXTERN_H_ */
