#pragma once
#include "Sexy/RtWeakPtr.h"
#include "Reflection/RType.h"

namespace Reflection::RCustomType
{
	struct UnkStruct
	{
	public:
		int m_unk1;
		int m_unk2;
		int m_unk3;
		int m_unk4;
		Sexy::RtWeakPtr<void>* m_weakPtrPtr;
	};

	struct VectorManipulatorStruct
	{
	public:
		UnkStruct* m_unkPtr;
		void* m_unkPtr2;
		bool m_unkBool;
	};

	template <typename T>
	class TStdVectorManipulator
	{
	public:
		using GenericVector = std::vector<T>;

		virtual void NullSub() {};

		void DestroyEffect(void* a1)
		{
			operator delete(a1);
		}
		
		// Thanks to RenoJson!
		bool UnkFunc(void* a1, Sexy::RtWeakPtr<void>* a2, int* vecSize)
		{
                //int* v1 = vecSize;
                *vecSize = 0;
                typedef int64_t(*func_2)(UnkStruct*, void*);
                func_2 pFunc2 = (func_2)getActualOffset(0x5B2AA4);

                uint v10 = pFunc2(a1, a2);

                typedef int64_t(*func_3)(UnkStruct*, int64_t);
                func_3 pFunc3 = (func_3)getActualOffset(0x14FEDCC);

                if (v10 && (pFunc3(a1, v10)) != 0) {
                    a1->unkVec.push_back(v10);
                    typedef int64_t(*func_4)(UnkStruct*, int64_t);
                    func_4 pFunc4 = (func_4)getActualOffset(0x14FEE04);
                    int v2 = pFunc4(a1, v10);
                    *vecSize = v2;
                }
                else
                {
                    return false;
                }
                return true;
		}

		virtual bool Edit(GenericVector* vector, VectorManipulatorStruct* manipInfo, Sexy::RtWeakPtr<void>* unkWeakPtr, RType* reflectionType)
		{
			if (manipInfo->m_unkBool)
			{
				int vecSize = 0;

				if (UnkFunc(manipInfo->m_unkPtr, unkWeakPtr, vecSize))
				{
					if (vecSize > 0)
					{
						vector->resize(vecSize);

						for (int i = 0; i < vecSize; i++)
						{
							T* element = &vector->at(i);
							SexyString str;
							reflectionType->Function11(element, manipInfo, str);
						}
					}

					manipInfo->m_unkPtr->m_weakPtrPtr--;
					return true;
				}

				return false;
			}
			else
			{
				int** v19 = *(int***)((int*)manipInfo + 4);
				typedef void (*sub262EC0)(int**, Sexy::RtWeakPtr<void>*, int, char);
				((sub262EC0)GetActualOffset(0x5B2440))(v19, unkWeakPtr, vector->size(), 0xFD);

				if (!vector->empty()) {
					for (int i = 0; i < vector->size(); ++i) {
						T* element = &vector->at(i);
						SexyString str;
						reflectionType->Function11(element, manipInfo, str);
					}
				}

				int* v17 = *v19;
				v19[2] = (int*)((char*)v19[2] - 1);

				uint8_t v21 = 254;
				typedef int (*sub10D2100)(int*, uint8_t*, int);
				((sub10D2100)GetActualOffset(0x14F8794))(v17, &v21, 1);

				return true;
			}
		}

		int GetSize(GenericVector* vector)
		{
			return vector->size();
		}
	};
}